#include <stdio.h>
#include <stdlib.h>
#include "cudd.h"
#include <time.h>

int main() {
    // 初始化 CUDD 管理器
    DdManager *manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    if (manager == NULL) {
        fprintf(stderr, "Error initializing CUDD manager\n");
        return 1;
    }

    // 创建布尔变量 x1, x2, x3
    int var_count = 3;
    DdNode *vars[3];
    for (int i = 0; i < var_count; i++) {
        vars[i] = Cudd_bddIthVar(manager, i);
    }

    // 构建布尔函数 f = (x1 ∧ x2) ∨ x3
    DdNode *and1 = Cudd_bddAnd(manager, vars[0], vars[1]);  // x1 ∧ x2
    Cudd_Ref(and1);
    DdNode *f = Cudd_bddOr(manager, vars[2], and1);    // (x1 ∧ x2) ∨ x3
    Cudd_Ref(f);
    Cudd_RecursiveDeref(manager, and1); // 释放中间节点

    // 输入赋值 (x1, x2, x3)
    int inputs[3] = {1, 0, 1}; // x1 = 1, x2 = 0, x3 = 1

    // =============== 重排序前 ====================
    printf("==================== Before Reordering ====================\n");

    // 输出初始 BDD 的节点数量
    printf("Original BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出原始变量顺序
    printf("Original variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    // 计算布尔函数输出值 (重排序前)
    clock_t start_time = clock();
    DdNode *result_before = Cudd_Eval(manager, f, inputs);
    clock_t end_time = clock();
    double eval_time_before = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // 输出布尔函数求值结果
    int output_before = (result_before == Cudd_ReadOne(manager)) ? 1 : 0;
    printf("f(%d, %d, %d) = %d\n", inputs[0], inputs[1], inputs[2], output_before);
    printf("Evaluation time (before reordering): %.6f seconds\n", eval_time_before);

    // 生成原始 BDD 图
    FILE *originalDot = fopen("original_bdd7.dot", "w");
    if (originalDot) {
        const char *inames[] = {"x1", "x2", "x3"};
        const char *onames[] = {"f"};
        Cudd_DumpDot(manager, 1, &f, inames, onames, originalDot);
        fclose(originalDot);
        system("dot -Tpng original_bdd7.dot -o original_bdd7.png");
        printf("Original BDD image saved as original_bdd7.png\n");
    }

    // =============== 执行重排序 ====================
    printf("==================== Performing Reordering ====================\n");

    // 执行动态 SIFT 排序
    Cudd_ReduceHeap(manager, CUDD_REORDER_SIFT, 0);

    // 输出优化后的 BDD 大小
    printf("Optimized BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出优化后的变量顺序
    printf("Optimized variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    // =============== 重排序后 ====================
    printf("==================== After Reordering ====================\n");

    // 计算布尔函数输出值 (重排序后)
    start_time = clock();
    DdNode *result_after = Cudd_Eval(manager, f, inputs);
    end_time = clock();
    double eval_time_after = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // 输出布尔函数求值结果
    int output_after = (result_after == Cudd_ReadOne(manager)) ? 1 : 0;
    printf("f(%d, %d, %d) = %d\n", inputs[0], inputs[1], inputs[2], output_after);
    printf("Evaluation time (after reordering): %.6f seconds\n", eval_time_after);

    // 生成优化后的 BDD 图
    FILE *optimizedDot = fopen("optimized_bdd7.dot", "w");
    if (optimizedDot) {
        const char *inames[] = {"x1", "x2", "x3"};
        const char *onames[] = {"f"};
        Cudd_DumpDot(manager, 1, &f, inames, onames, optimizedDot);
        fclose(optimizedDot);
        system("dot -Tpng optimized_bdd7.dot -o optimized_bdd7.png");
        printf("Optimized BDD image saved as optimized_bdd7.png\n");
    }

    // =============== 结果对比总结 ====================
    printf("==================== Comparison Summary ====================\n");
    printf("Output before reordering: %d, Time: %.6f seconds\n", output_before, eval_time_before);
    printf("Output after reordering:  %d, Time: %.6f seconds\n", output_after, eval_time_after);

    // 清理资源
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}


