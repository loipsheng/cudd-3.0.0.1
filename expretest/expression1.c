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

    int var_count = 4;
    // 创建布尔变量 x1, x2, x3, x4
    DdNode *x1 = Cudd_bddIthVar(manager, 0);
    DdNode *x2 = Cudd_bddIthVar(manager, 1);
    DdNode *x3 = Cudd_bddIthVar(manager, 2);
    DdNode *x4 = Cudd_bddIthVar(manager, 3);

    // 创建表达式 f = (x1 AND x2) OR (x3 AND x4)
    DdNode *and1 = Cudd_bddAnd(manager, x1, x2);  // x1 AND x2
    Cudd_Ref(and1);
    DdNode *and2 = Cudd_bddAnd(manager, x3, x4);  // x3 AND x4
    Cudd_Ref(and2);
    DdNode *f = Cudd_bddOr(manager, and1, and2);   // (x1 AND x2) OR (x3 AND x4)
    Cudd_Ref(f);

    // 打印表达式的 BDD 重排序之前的节点数量
    printf("Original BDD size: %d nodes\n", Cudd_DagSize(f));

    // 自动重排序 (选择最佳变量排列)
    Cudd_AutodynEnable(manager, CUDD_REORDER_SIFT);  // 启用动态 SIFT 排序
    Cudd_ReduceHeap(manager, CUDD_REORDER_SIFT, 0);  // 立即执行 SIFT 排序

    printf("Optimized BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出最优变量顺序
    printf("Optimal variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");


    // 生成 DOT 文件
    FILE *dotFile = fopen("bdd1.dot", "w");
    if (dotFile == NULL) {
        fprintf(stderr, "Error opening DOT file for writing\n");
        Cudd_RecursiveDeref(manager, and1);
        Cudd_RecursiveDeref(manager, and2);
        Cudd_RecursiveDeref(manager, f);
        Cudd_Quit(manager);
        return 1;
    }

    // 为输入和输出变量命名，可以传递 NULL 作为占位符
    const char *inames[] = { "x1", "x2", "x3", "x4" };  // 输入变量名称
    const char *onames[] = { "f" };                      // 输出变量名称
    Cudd_DumpDot(manager, 1, &f, inames, onames, dotFile);

    fclose(dotFile);

    // 使用 Graphviz 将 DOT 文件转换为 PNG 格式
    // 请确保您已安装 Graphviz，并确保该命令在系统路径中
    int result = system("dot -Tpng bdd1.dot -o bdd1.png");
    if (result != 0) {
        fprintf(stderr, "Error converting DOT to PNG\n");
    } else {
        printf("BDD image saved as bdd1.png\n");
    }

    // 清理内存
    Cudd_RecursiveDeref(manager, and1);
    Cudd_RecursiveDeref(manager, and2);
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}
