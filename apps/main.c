#include "cuddInt.h"
#include <stdio.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "cudd.h"

#define EXIT_SUCCESSFULLY           0
#define EXIT_FAILED                 -1

#define GREEN_START                 "\e[0;32m"
#define BLUE_START                  "\e[0;34m"
#define RED_START                   "\e[0;31m"
#define COLORTAG_END                "\033[0m"
#define BUFLENGTH                   1024 * 8

#ifndef TRUE
#define TRUE                        1
#endif
#ifndef FALSE
#define FALSE                       0
#endif

static char buffer[BUFLENGTH];

#define APPLICATION_DEBUG_ON

#if defined(APPLICATION_DEBUG_ON)

#define DEBUG_WARNING(msg)  do {                \
    printf(                                     \
        "%s[ WARNING ]: %s%s\r\n",              \
        (char*)GREEN_START,(char*)(msg),        \
        (char*)COLORTAG_END                     \
        );                                      \
} while(0)

#define DEBUG_INFORMATION(msg) do {             \
    printf(                                     \
        "%s[ INFO ]: %s%s\r\n",  \
        (char*)BLUE_START,                      \
        (char*)(msg),                           \
        (char*)COLORTAG_END                     \
        );   \
} while(0)

#define DEBUG_ERROR_COND(condition, msg) do {                   \
    if(condition) {                             \
        printf(                                 \
            "%s[ ERROR ]: %s%s\r\n",            \
            (char*)RED_START,                   \
            (char*)(msg), (char*)COLORTAG_END   \
            );    \
    }                       \
}while(0)

#define DEBUG_ERROR(msg) do {                   \
    printf(                                     \
        "%s[ ERROR ]: %s%s\r\n", \
        (char*)RED_START,                       \
        (char*)(msg), (char*)COLORTAG_END       \
    );                                          \
} while(0)

#else

#define DEBUG_WARNING(msg)
#define DEBUG_INFORMATION(msg)
#define DEBUG_ERROR_COND(condition, msg)
#define DEBUG_ERROR(msg)

#endif

#define ALLOCATE(type, size)        \
    ((type*)malloc(size))


#define OPEN_FILE(fp, filename, mode)    do {        \
    if(strcmp((char*)(filename), "-") == 0) {              \
        return mode[0] == 'r' ? stdin : stdout;     \
    }                                               \
    else if(((fp) = fopen((filename), mode)) == NULL) \
    {                                               \
        perror((filename));                           \
        exit(1);                                    \
    }                                               \
} while(0)

// 创建半加器的 BDD
DdNode **createHalfAdderBDD(DdManager *manager) {
    DdNode *x0 = Cudd_bddIthVar(manager, 0); // 输入 x0
    DdNode *x1 = Cudd_bddIthVar(manager, 1); // 输入 x1

    // sum = x0 XOR x1 = (x0 AND NOT x1) OR (NOT x0 AND x1)
    DdNode *and1 = Cudd_bddAnd(manager, x0, Cudd_Not(x1));
    Cudd_Ref(and1);
    DdNode *and2 = Cudd_bddAnd(manager, Cudd_Not(x0), x1);
    Cudd_Ref(and2);
    DdNode *sum = Cudd_bddOr(manager, and1, and2);
    Cudd_Ref(sum);
    Cudd_RecursiveDeref(manager, and1);
    Cudd_RecursiveDeref(manager, and2);

    // carry = x0 AND x1
    DdNode *carry = Cudd_bddAnd(manager, x0, x1);
    Cudd_Ref(carry);

    // 返回 sum 和 carry
    DdNode **outputs = malloc(2 * sizeof(DdNode *));
    outputs[0] = sum;
    outputs[1] = carry;
    return outputs;
}

// 测试限制 BDD
void test(DdManager *manager, DdNode **node) {
    DdNode *x0 = Cudd_bddIthVar(manager, 0);
    DdNode *x1 = Cudd_bddIthVar(manager, 1);

    const int SIZE = 4;
    DdNode *restrictBy[SIZE];
    DdNode *testSum[SIZE];
    DdNode *testCarry[SIZE];
    int i;

    // 定义限制条件
    restrictBy[0] = Cudd_bddAnd(manager, Cudd_Not(x0), Cudd_Not(x1)); // x0=0, x1=0
    restrictBy[1] = Cudd_bddAnd(manager, Cudd_Not(x0), x1);           // x0=0, x1=1
    restrictBy[2] = Cudd_bddAnd(manager, x0, Cudd_Not(x1));           // x0=1, x1=0
    restrictBy[3] = Cudd_bddAnd(manager, x0, x1);                     // x0=1, x1=1

    // 限制 BDD 并验证结果
    for (i = 0; i < SIZE; i++) {
        Cudd_Ref(restrictBy[i]);
        testSum[i] = Cudd_bddRestrict(manager, node[0], restrictBy[i]);
        testCarry[i] = Cudd_bddRestrict(manager, node[1], restrictBy[i]);
        Cudd_RecursiveDeref(manager, restrictBy[i]);
    }

    // 打印输出结果
    for (i = 0; i < SIZE; i++) {
        printf("(x0=%d, x1=%d): sum = %d, carry = %d\n",
               i & 2 ? 1 : 0, i & 1 ? 1 : 0,
               1 - Cudd_IsComplement(testSum[i]),
               1 - Cudd_IsComplement(testCarry[i]));
    }

    // 释放内存
    for (i = 0; i < SIZE; i++) {
        Cudd_RecursiveDeref(manager, testSum[i]);
        Cudd_RecursiveDeref(manager, testCarry[i]);
    }
}

// 导出为 DOT 文件
void toDot(DdManager *manager, DdNode **outputs) {
    const char *inputNames[2] = {"x0", "x1"};
    const char *outputNames[2] = {"sum", "carry"};
    FILE *file = fopen("halfadder.dot", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    Cudd_DumpDot(manager, 2, outputs, inputNames, outputNames, file);
    fclose(file);
}
int main() {
    // 初始化 CUDD 管理器
    DdManager *dd = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    Cudd_AutodynEnable(dd, CUDD_REORDER_SIFT);

    // 创建半加器的 BDD
    DdNode **outputs = createHalfAdderBDD(dd);
    Cudd_ReduceHeap(dd, CUDD_REORDER_SIFT, 1);

    // 导出为 DOT 文件
    toDot(dd, outputs);

    // 测试半加器
     test(dd, outputs);

    // 释放内存
    Cudd_RecursiveDeref(dd, outputs[0]);
    Cudd_RecursiveDeref(dd, outputs[1]);
    free(outputs);

    Cudd_Quit(dd);
    return 0;
}
