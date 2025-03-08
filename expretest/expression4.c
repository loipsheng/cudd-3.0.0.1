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

    // 创建布尔变量 x1, x2, x3, x4, x5, x6
    DdNode *x1 = Cudd_bddIthVar(manager, 0);
    DdNode *x2 = Cudd_bddIthVar(manager, 1);
    DdNode *x3 = Cudd_bddIthVar(manager, 2);
    DdNode *x4 = Cudd_bddIthVar(manager, 3);
    DdNode *x5 = Cudd_bddIthVar(manager, 4);
    DdNode *x6 = Cudd_bddIthVar(manager, 5);

    // 创建表达式 f = (x1 AND x4) OR (x2 AND x5) OR (x3 AND x6)
    DdNode *and1 = Cudd_bddAnd(manager, x1, x4);  // x1 AND x4
    Cudd_Ref(and1);
    DdNode *and2 = Cudd_bddAnd(manager, x2, x5);  // x2 AND x5
    Cudd_Ref(and2);
    DdNode *and3 = Cudd_bddAnd(manager, x3, x6);  // x3 AND x6
    Cudd_Ref(and3);
    DdNode *f = Cudd_bddOr(manager, and1, and2);   // (x1 AND x4) OR (x2 AND x5)
    Cudd_Ref(f);
    f = Cudd_bddOr(manager, f, and3);              // (x1 AND x4) OR (x2 AND x5) OR (x3 AND x6)
    Cudd_Ref(f);

    // 打印表达式的 BDD 节点数量
    printf("Number of nodes in f: %d\n", Cudd_DagSize(f));

    // 生成 DOT 文件
    FILE *dotFile = fopen("bdd4.dot", "w");
    if (dotFile == NULL) {
        fprintf(stderr, "Error opening DOT file for writing\n");
        Cudd_RecursiveDeref(manager, and1);
        Cudd_RecursiveDeref(manager, and2);
        Cudd_RecursiveDeref(manager, and3);
        Cudd_RecursiveDeref(manager, f);
        Cudd_Quit(manager);
        return 1;
    }

    // 为输入和输出变量命名，可以传递 NULL 作为占位符
    const char *inames[] = { "x1", "x2", "x3", "x4", "x5", "x6" };  // 输入变量名称
    const char *onames[] = { "f" };                                  // 输出变量名称
    Cudd_DumpDot(manager, 1, &f, inames, onames, dotFile);

    fclose(dotFile);

    // 使用 Graphviz 将 DOT 文件转换为 PNG 格式
    // 请确保您已安装 Graphviz，并确保该命令在系统路径中
    int result = system("dot -Tpng bdd4.dot -o bdd4.png");
    if (result != 0) {
        fprintf(stderr, "Error converting DOT to PNG\n");
    } else {
        printf("BDD image saved as bdd4.png\n");
    }

    // 清理内存
    Cudd_RecursiveDeref(manager, and1);
    Cudd_RecursiveDeref(manager, and2);
    Cudd_RecursiveDeref(manager, and3);
    Cudd_RecursiveDeref(manager, f);
    Cudd_Quit(manager);

    return 0;
}
