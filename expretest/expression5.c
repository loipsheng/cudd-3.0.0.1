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

    // 创建布尔变量 x1 和 x2
    DdNode *x1 = Cudd_bddIthVar(manager, 0);
    DdNode *x2 = Cudd_bddIthVar(manager, 1);

    // 创建表达式 (x1 + x2)
    DdNode *or1 = Cudd_bddOr(manager, x1, x2);  // x1 OR x2
    Cudd_Ref(or1);

    // 创建表达式 (¬x1 + ¬x2)
    DdNode *not_x1 = Cudd_Not(x1);  // ¬x1
    Cudd_Ref(not_x1);
    DdNode *not_x2 = Cudd_Not(x2);  // ¬x2
    Cudd_Ref(not_x2);
    DdNode *or2 = Cudd_bddOr(manager, not_x1, not_x2);  // ¬x1 OR ¬x2
    Cudd_Ref(or2);

    // 最终的表达式: (x1 + x2) * (¬x1 + ¬x2)
    DdNode *f = Cudd_bddAnd(manager, or1, or2);  // (x1 + x2) AND (¬x1 + ¬x2)
    Cudd_Ref(f);

    // 打印表达式的 BDD 节点数量
    printf("Number of nodes in f: %d\n", Cudd_DagSize(f));

    // 生成 DOT 文件
    FILE *dotFile = fopen("bdd5.dot", "w");
    if (dotFile == NULL) {
        fprintf(stderr, "Error opening DOT file for writing\n");
        Cudd_RecursiveDeref(manager, or1);
        Cudd_RecursiveDeref(manager, or2);
        Cudd_RecursiveDeref(manager, not_x1);
        Cudd_RecursiveDeref(manager, not_x2);
        Cudd_RecursiveDeref(manager, f);
        Cudd_Quit(manager);
        return 1;
    }

    // 为输入和输出变量命名，可以传递 NULL 作为占位符
    const char *inames[] = { "x1", "x2" };  // 输入变量名称
    const char *onames[] = { "f" };        // 输出变量名称
    Cudd_DumpDot(manager, 1, &f, inames, onames, dotFile);

    fclose(dotFile);

    // 使用 Graphviz 将 DOT 文件转换为 PNG 格式
    // 请确保您已安装 Graphviz，并确保该命令在系统路径中
    int result = system("dot -Tpng bdd5.dot -o bdd5.png");
    if (result != 0) {
        fprintf(stderr, "Error converting DOT to PNG\n");
    } else {
        printf("BDD image saved as bdd5.png\n");
    }

    // 清理内存
    Cudd_RecursiveDeref(manager, or1);
    Cudd_RecursiveDeref(manager, or2);
    Cudd_RecursiveDeref(manager, not_x1);
    Cudd_RecursiveDeref(manager, not_x2);
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}
