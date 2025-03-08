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
    DdNode *x1 = Cudd_bddIthVar(manager, 0);
    DdNode *x2 = Cudd_bddIthVar(manager, 1);
    DdNode *x3 = Cudd_bddIthVar(manager, 2);

    // 计算表达式 f = x1 + x2 * x3，即 f = (x1 OR (x2 AND x3))
    DdNode *and1 = Cudd_bddAnd(manager, x2, x3);  // x2 * x3
    Cudd_Ref(and1);
    DdNode *f = Cudd_bddOr(manager, x1, and1);    // x1 + (x2 * x3)
    Cudd_Ref(f);

    // 释放中间节点 and1
    Cudd_RecursiveDeref(manager, and1);

    // 打印 BDD 的节点数量
    printf("Number of nodes in f: %d\n", Cudd_DagSize(f));

    // 生成 DOT 文件
    FILE *dotFile = fopen("bdd6.dot", "w");
    if (dotFile == NULL) {
        fprintf(stderr, "Error opening DOT file for writing\n");
        Cudd_RecursiveDeref(manager, f);
        Cudd_Quit(manager);
        return 1;
    }

    // 定义变量名称
    const char *inames[] = { "x1", "x2", "x3" };
    const char *onames[] = { "f" };

    // 生成 DOT 文件
    Cudd_DumpDot(manager, 1, &f, inames, onames, dotFile);
    fclose(dotFile);

    // 使用 Graphviz 生成 PNG 图片
    int result = system("dot -Tpng bdd6.dot -o bdd6.png");
    if (result != 0) {
        fprintf(stderr, "Error converting DOT to PNG\n");
    } else {
        printf("BDD image saved as bdd6.png\n");
    }

    // 清理内存
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}
