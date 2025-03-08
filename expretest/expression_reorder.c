#include <stdio.h>
#include <stdlib.h>
#include "cudd.h"

// 自动变量排序示例
int main() {
    // 初始化 CUDD 管理器
    DdManager *manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    if (manager == NULL) {
        fprintf(stderr, "Error initializing CUDD manager\n");
        return 1;
    }

    // 创建 6 个布尔变量
    int var_count = 6;
    DdNode *vars[6];
    for (int i = 0; i < var_count; i++) {
        vars[i] = Cudd_bddIthVar(manager, i);
    }

    // 构造布尔函数示例：(x1 AND x4) OR (x2 AND x5) OR (x3 AND x6)
    DdNode *expr1 = Cudd_bddAnd(manager, vars[0], vars[3]);  // (x1 AND x4)
    Cudd_Ref(expr1);
    DdNode *expr2 = Cudd_bddAnd(manager, vars[1], vars[4]);  // (x2 AND x5)
    Cudd_Ref(expr2);
    DdNode *expr3 = Cudd_bddAnd(manager, vars[2], vars[5]);  // (x3 AND x6)
    Cudd_Ref(expr3);

    // 构建目标布尔函数 f = expr1 OR expr2 OR expr3
    DdNode *f = Cudd_bddOr(manager, expr1, expr2);
    Cudd_Ref(f);
    f = Cudd_bddOr(manager, f, expr3);
    Cudd_Ref(f);

    printf("Original BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出 CUDD 初始化后的原始变量顺序
    printf("Original variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    // 生成原始 BDD 图
    FILE *originalDot = fopen("original_bdd.dot", "w");
    if (originalDot) {
        const char *inames[] = {"x1", "x2", "x3", "x4", "x5", "x6"};
        const char *onames[] = {"f"};
        Cudd_DumpDot(manager, 1, &f, inames, onames, originalDot);
        fclose(originalDot);
        system("dot -Tpng original_bdd.dot -o original_bdd.png");
        printf("Original BDD image saved as original_bdd.png\n");
    }

    // 自动重排序 (选择最佳变量排列)
    Cudd_AutodynEnable(manager, CUDD_REORDER_SIFT);  // 启用动态 SIFT 排序
    Cudd_ReduceHeap(manager, CUDD_REORDER_SIFT, 0);  // 立即执行 SIFT 排序;enable后函数里面自己调用了reduceheap，不需要自己再执行一次

    printf("Optimized BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出最优变量顺序
    printf("Optimal variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    // 生成优化后的 BDD 图
    FILE *optimizedDot = fopen("optimized_bdd.dot", "w");
    if (optimizedDot) {
        const char *inames[] = {"x1", "x2", "x3", "x4", "x5", "x6"};
        const char *onames[] = {"f"};
        Cudd_DumpDot(manager, 1, &f, inames, onames, optimizedDot);
        fclose(optimizedDot);
        system("dot -Tpng optimized_bdd.dot -o optimized_bdd.png");
        printf("Optimized BDD image saved as optimized_bdd.png\n");
    }

    // 释放资源
    Cudd_RecursiveDeref(manager, expr1);
    Cudd_RecursiveDeref(manager, expr2);
    Cudd_RecursiveDeref(manager, expr3);
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}

