#include <stdio.h>
#include <stddef.h>  // for size_t
#include <stdlib.h>  // for system()
#include "cudd.h"

int main() {
    // 初始化 CUDD 管理器
    DdManager *manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    if (manager == NULL) {
        fprintf(stderr, "Error initializing CUDD manager\n");
        return 1;
    }

    // 创建布尔变量 x1, x2, x3
    DdNode *x1 = Cudd_bddIthVar(manager, 0);
    DdNode *x2 = Cudd_bddIthVar(manager, 1);
    DdNode *x3 = Cudd_bddIthVar(manager, 2);

    // 创建表达式 f = ¬(x1 AND x3) OR (x2 AND x3)
    DdNode *and1 = Cudd_bddAnd(manager, x1, x3);  // x1 AND x3
    Cudd_Ref(and1);

    DdNode *not_and1 = Cudd_Not(and1);  // ¬(x1 AND x3)
    Cudd_Ref(not_and1);

    DdNode *and2 = Cudd_bddAnd(manager, x2, x3);  // x2 AND x3
    Cudd_Ref(and2);

    DdNode *f = Cudd_bddOr(manager, not_and1, and2);   // ¬(x1 AND x3) OR (x2 AND x3)
    Cudd_Ref(f);

    // 打印表达式的 BDD 节点数量
    printf("Number of nodes in f: %d\n", Cudd_DagSize(f));

    // 生成 DOT 文件
    FILE *dotFile = fopen("bdd3.dot", "w");
    if (dotFile == NULL) {
        fprintf(stderr, "Error opening DOT file for writing\n");
        Cudd_RecursiveDeref(manager, and1);
        Cudd_RecursiveDeref(manager, not_and1);
        Cudd_RecursiveDeref(manager, and2);
        Cudd_RecursiveDeref(manager, f);
        Cudd_Quit(manager);
        return 1;
    }

    // 为输入和输出变量命名，可以传递 NULL 作为占位符
    const char *inames[] = { "x1", "x2", "x3" };  // 输入变量名称
    const char *onames[] = { "f" };               // 输出变量名称
    Cudd_DumpDot(manager, 1, &f, inames, onames, dotFile);

    fclose(dotFile);

    // 使用 Graphviz 将 DOT 文件转换为 PNG 格式
    int result = system("dot -Tpng bdd3.dot -o bdd3.png");
    if (result != 0) {
        fprintf(stderr, "Error converting DOT to PNG\n");
    } else {
        printf("BDD image saved as bdd3.png\n");
    }

    // 清理内存
    Cudd_RecursiveDeref(manager, and1);
    Cudd_RecursiveDeref(manager, not_and1);
    Cudd_RecursiveDeref(manager, and2);
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}

