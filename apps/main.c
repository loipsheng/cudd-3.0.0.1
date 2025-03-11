#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cudd.h"

// 计算布尔函数的求值时间
double evaluateBDD(DdManager *manager, DdNode *f, int *inputs) {
    clock_t start_time = clock();
    DdNode *result = Cudd_Eval(manager, f, inputs);
    clock_t end_time = clock();
    double eval_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    int output = (result == Cudd_ReadOne(manager)) ? 1 : 0;
    printf("f(%d, %d, %d, %d, %d, %d) = %d\n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], output);

    return eval_time;
}

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

    // 构造布尔函数 f = (x1 AND x4) OR (x2 AND x5) OR (x3 AND x6)
    DdNode *expr1 = Cudd_bddAnd(manager, vars[0], vars[3]);  // (x1 AND x4)
    Cudd_Ref(expr1);
    DdNode *expr2 = Cudd_bddAnd(manager, vars[1], vars[4]);  // (x2 AND x5)
    Cudd_Ref(expr2);
    DdNode *expr3 = Cudd_bddAnd(manager, vars[2], vars[5]);  // (x3 AND x6)
    Cudd_Ref(expr3);

    DdNode *f = Cudd_bddOr(manager, expr1, expr2);
    Cudd_Ref(f);
    f = Cudd_bddOr(manager, f, expr3);
    Cudd_Ref(f);

    printf("======== Before Reordering ========\n");
    printf("Original BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出原始变量顺序
    printf("Original variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    // 输入值 (例如: x1=1, x2=0, x3=1, x4=0, x5=1, x6=0)
    int inputs[6] = {1, 0, 1, 0, 1, 0};

    // 计算布尔函数求值时间（重排序前）
    double time_before = evaluateBDD(manager, f, inputs);
    printf("Evaluation time before reordering: %.6f seconds\n", time_before);

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

    printf("======== During Reordering ========\n");
    // 启用自动动态重排序 (SIFT 方法)
    Cudd_AutodynEnable(manager, CUDD_REORDER_SIFT);
    Cudd_ReduceHeap(manager, CUDD_REORDER_SIFT, 0); // 立即执行 SIFT 排序

    printf("Optimized BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出优化后的变量顺序
    printf("Optimal variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    printf("======== After Reordering ========\n");
    // 计算布尔函数求值时间（重排序后）
    double time_after = evaluateBDD(manager, f, inputs);
    printf("Evaluation time after reordering: %.6f seconds\n", time_after);

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

    // =============== 结果对比总结 ====================
    printf("==================== Comparison Summary ====================\n");
    printf("Output before reordering: Time: %.6f seconds\n",  time_before);
    printf("Output after reordering:  Time: %.6f seconds\n",  time_after);

    // 清理资源
    Cudd_RecursiveDeref(manager, expr1);
    Cudd_RecursiveDeref(manager, expr2);
    Cudd_RecursiveDeref(manager, expr3);
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}

