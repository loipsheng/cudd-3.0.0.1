#include <stdio.h>
#include <stdlib.h>
#include "cudd.h"

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
    
    // 计算表达式 f = x1 + x2 * x3，即 f = (x1 OR (x2 AND x3))
    DdNode *and1 = Cudd_bddIte(manager, vars[1], vars[2],  Cudd_ReadLogicZero(manager));  // x2 * x3
    Cudd_Ref(and1);
    DdNode *f = Cudd_bddOr(manager, vars[0], and1);    // x1 + (x2 * x3)
    Cudd_Ref(f);
    
    // 释放中间节点 and1
    Cudd_RecursiveDeref(manager, and1);

    // 打印 BDD 的节点数量
    printf("Number of nodes in f: %d\n", Cudd_DagSize(f));

    // 输出 CUDD 初始化后的原始变量顺序
    printf("Original variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");

    // // 生成 DOT 文件
    // FILE *dotFile = fopen("bdd6.dot", "w");
    // if (dotFile == NULL) {
    //     fprintf(stderr, "Error opening DOT file for writing\n");
    //     Cudd_RecursiveDeref(manager, f);
    //     Cudd_Quit(manager);
    //     return 1;
    // }

    // 生成原始 BDD 图
    FILE *originalDot = fopen("original_bdd6.dot", "w");
    if (originalDot) {
        const char *inames[] = {"x1", "x2", "x3"};
        const char *onames[] = {"f"};
        Cudd_DumpDot(manager, 1, &f, inames, onames, originalDot);
        fclose(originalDot);
        system("dot -Tpng original_bdd6.dot -o original_bdd6.png");
        printf("Original BDD image saved as original_bdd6.png\n");
    }

    // 自动重排序 (选择最佳变量排列)
    Cudd_AutodynEnable(manager, CUDD_REORDER_SIFT);  // 启用动态 SIFT 排序
    Cudd_ReduceHeap(manager, CUDD_REORDER_SIFT, 0);  // 立即执行 SIFT 排序;enable后函数里面自己调用了reduceheap，不需要自己再执行一次?
    printf("Optimized BDD size: %d nodes\n", Cudd_DagSize(f));

    // 输出最优变量顺序
    printf("Optimal variable order: ");
    for (int i = 0; i < var_count; i++) {
        printf("x%d ", Cudd_ReadInvPerm(manager, i) + 1);
    }
    printf("\n");


    // 生成优化后的 BDD 图
    FILE *optimizedDot = fopen("optimized_bdd6.dot", "w");
    if (optimizedDot) {
        const char *inames[] = {"x1", "x2", "x3"};
        const char *onames[] = {"f"};
        Cudd_DumpDot(manager, 1, &f, inames, onames, optimizedDot);
        fclose(optimizedDot);
        system("dot -Tpng optimized_bdd6.dot -o optimized_bdd6.png");
        printf("Optimized BDD image saved as optimized_bdd6.png\n");
    }

    // // 定义变量名称
    // const char *inames[] = { "x1", "x2", "x3" };
    // const char *onames[] = { "f" };

    // // 生成 DOT 文件
    // Cudd_DumpDot(manager, 1, &f, inames, onames, dotFile);
    // fclose(dotFile);

    // // 使用 Graphviz 生成 PNG 图片
    // int result = system("dot -Tpng bdd6.dot -o bdd6.png");
    // if (result != 0) {
    //     fprintf(stderr, "Error converting DOT to PNG\n");
    // } else {
    //     printf("BDD image saved as bdd6.png\n");
    // }

    // 清理内存
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}
