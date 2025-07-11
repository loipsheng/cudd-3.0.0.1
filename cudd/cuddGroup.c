/**
  @file

  @ingroup cudd

  @brief Functions for group sifting.

  @author Shipra Panda, Fabio Somenzi

  @copyright@parblock
  Copyright (c) 1995-2015, Regents of the University of Colorado

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  Neither the name of the University of Colorado nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
  @endparblock

*/

#include "util.h"
#include "mtrInt.h"
#include "cuddInt.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/* Constants for lazy sifting */
#define	DD_NORMAL_SIFT	0
#define	DD_LAZY_SIFT	1

/* Constants for sifting up and down */
#define	DD_SIFT_DOWN	0
#define	DD_SIFT_UP	1

/*---------------------------------------------------------------------------*/
/* Stucture declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

typedef int (*DD_CHKFP)(DdManager *, int, int);

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/** \cond */

/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/

static int ddTreeSiftingAux (DdManager *table, MtrNode *treenode, Cudd_ReorderingType method);
#ifdef DD_STATS
static int ddCountInternalMtrNodes (DdManager *table, MtrNode *treenode);
#endif
static int ddReorderChildren (DdManager *table, MtrNode *treenode, Cudd_ReorderingType method);
static void ddFindNodeHiLo (DdManager *table, MtrNode *treenode, int *lower, int *upper);
static int ddUniqueCompareGroup (void const *ptrX, void const *ptrY);
static int ddGroupSifting (DdManager *table, int lower, int upper, DD_CHKFP checkFunction, int lazyFlag);
static void ddCreateGroup (DdManager *table, int x, int y);
static int ddGroupSiftingAux (DdManager *table, int x, int xLow, int xHigh, DD_CHKFP checkFunction, int lazyFlag);
static int ddGroupSiftingUp (DdManager *table, int y, int xLow, DD_CHKFP checkFunction, Move **moves);
static int ddGroupSiftingDown (DdManager *table, int x, int xHigh, DD_CHKFP checkFunction, Move **moves);
static int ddGroupMove (DdManager *table, int x, int y, Move **moves);
static int ddGroupMoveBackward (DdManager *table, int x, int y);
static int ddGroupSiftingBackward (DdManager *table, Move *moves, int size, int upFlag, int lazyFlag);
static void ddMergeGroups (DdManager *table, MtrNode *treenode, int low, int high);
static void ddDissolveGroup (DdManager *table, int x, int y);
static int ddNoCheck (DdManager *table, int x, int y);
static int ddSecDiffCheck (DdManager *table, int x, int y);
static int ddExtSymmCheck (DdManager *table, int x, int y);
static int ddVarGroupCheck (DdManager * table, int x, int y);
static int ddSetVarHandled (DdManager *dd, int index);
static int ddResetVarHandled (DdManager *dd, int index);
static int ddIsVarHandled (DdManager *dd, int index);

/** \endcond */

/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/


/**
  @brief Creates a new variable group.

  @details The group starts at variable low and contains size
  variables. The parameter low is the index of the first variable. If
  the variable already exists, its current position in the order is
  known to the manager. If the variable does not exist yet, the
  position is assumed to be the same as the index.  The group tree is
  created if it does not exist yet.

  @return a pointer to the group if successful; NULL otherwise.

  @sideeffect The variable tree is changed.

  @see Cudd_MakeZddTreeNode

*/
MtrNode *
Cudd_MakeTreeNode(
  DdManager * dd /**< manager */,
  unsigned int  low /**< index of the first group variable */,
  unsigned int  size /**< number of variables in the group */,
  unsigned int  type /**< MTR_DEFAULT or MTR_FIXED */)
{
    MtrNode *group;
    MtrNode *tree;
    unsigned int level;

    /* If the variable does not exist yet, the position is assumed to be
    ** the same as the index. Therefore, applications that rely on
    ** Cudd_bddNewVarAtLevel or Cudd_addNewVarAtLevel to create new
    ** variables have to create the variables before they group them.
    */
    level = (low < (unsigned int) dd->size) ? (unsigned int) dd->perm[low] : low;

    if (level + size - 1> (int) MTR_MAXHIGH)
	return(NULL);

    /* If the tree does not exist yet, create it. */
    tree = dd->tree;
    if (tree == NULL) {
	dd->tree = tree = Mtr_InitGroupTree(0, dd->size);
	if (tree == NULL)
	    return(NULL);
	tree->index = dd->size == 0 ? 0 : dd->invperm[0];
    }

    /* Extend the upper bound of the tree if necessary. This allows the
    ** application to create groups even before the variables are created.
    */
    tree->size = ddMax(tree->size, ddMax(level + size, (unsigned) dd->size));

    /* Create the group. */
    group = Mtr_MakeGroup(tree, level, size, type);
    if (group == NULL)
	return(NULL);

    /* Initialize the index field to the index of the variable currently
    ** in position low. This field will be updated by the reordering
    ** procedure to provide a handle to the group once it has been moved.
    */
    group->index = (MtrHalfWord) low;

    return(group);

} /* end of Cudd_MakeTreeNode */


/*---------------------------------------------------------------------------*/
/* Definition of internal functions                                          */
/*---------------------------------------------------------------------------*/


/**
  @brief Tree sifting algorithm.树状筛选算法

  @details Assumes that a tree representing a group hierarchy is
  passed as a parameter.  It then reorders each group in postorder
  fashion by calling ddTreeSiftingAux.  Assumes that no dead nodes are
  present.假定参数传递了一棵代表分组层次结构的树。 然后，它通过调用 ddTreeSiftingAux，以后序方式对每个分组重新排序。 假设没有死节点。

  @return 1 if successful; 0 otherwise.

  @sideeffect None

*/
int
cuddTreeSifting(
  DdManager * table /**< %DD table */,
  Cudd_ReorderingType method /**< reordering method for the groups of leaves */)
{
    int i;
    int nvars;
    int result;
    int tempTree;
	
    /* If no tree is provided we create a temporary one in which all
    ** variables are in a single group. After reordering this tree is
    ** destroyed. 如果没有提供树形图，我们会创建一个临时树形图，将所有变量归为一组。重新排序后，这棵树销毁。*/
    //1. 初始化树形结构
    tempTree = table->tree == NULL;			//如果没有提供树，则temptree = 1;
    if (tempTree) {
	table->tree = Mtr_InitGroupTree(0,table->size);
	table->tree->index = table->invperm[0];
    }
    nvars = table->size;

#ifdef DD_DEBUG
    if (table->enableExtraDebug > 0 && !tempTree)
        (void) fprintf(table->out,"cuddTreeSifting:");
    Mtr_PrintGroups(table->tree,table->enableExtraDebug <= 0);
#endif

#ifdef DD_STATS
    table->extsymmcalls = 0;
    table->extsymm = 0;
    table->secdiffcalls = 0;
    table->secdiff = 0;
    table->secdiffmisfire = 0;

    (void) fprintf(table->out,"\n");
    if (!tempTree)
	(void) fprintf(table->out,"#:IM_NODES  %8d: group tree nodes\n",
		       ddCountInternalMtrNodes(table,table->tree));
#endif

    /* Initialize the group of each subtable to itself. Initially
    ** there are no groups. Groups are created according to the tree
    ** structure in postorder fashion.将每个子表的组初始化为自身。最初没有分组。分组是根据树 结构创建分组。
    2.初始化子表的分组*/
    for (i = 0; i < nvars; i++)
	table->subtables[i].next = i;


    /* 3.执行核心筛选过程 	Reorder. */
    result = ddTreeSiftingAux(table, table->tree, method);	//该步骤是 cuddTreeSifting() 的核心，主要算法逻辑在 ddTreeSiftingAux() 中实现

#ifdef DD_STATS		/* print stats */
    if (!tempTree && method == CUDD_REORDER_GROUP_SIFT &&
	(table->groupcheck == CUDD_GROUP_CHECK7 ||
	 table->groupcheck == CUDD_GROUP_CHECK5)) {
	(void) fprintf(table->out,"\nextsymmcalls = %d\n",table->extsymmcalls);
	(void) fprintf(table->out,"extsymm = %d",table->extsymm);
    }
    if (!tempTree && method == CUDD_REORDER_GROUP_SIFT &&
	table->groupcheck == CUDD_GROUP_CHECK7) {
	(void) fprintf(table->out,"\nsecdiffcalls = %d\n",table->secdiffcalls);
	(void) fprintf(table->out,"secdiff = %d\n",table->secdiff);
	(void) fprintf(table->out,"secdiffmisfire = %d",table->secdiffmisfire);
    }
#endif
	//4.清理临时树形结构
    if (tempTree)
	Cudd_FreeTree(table);
    else
      Mtr_ReorderGroups(table->tree, table->perm);		//按照新的顺序重新调整树形分组结构

    return(result);

} /* end of cuddTreeSifting */


/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/


/**
  @brief Visits the group tree and reorders each group.访问组树并重新排列每个组的顺序。

  @details Recursively visits the group tree and reorders each
  group in postorder fashion. 递归访问分组树，并以后序方式对每个分组重新排序。

  @return 1 if successful; 0 otherwise.

  @sideeffect None

*/
static int
ddTreeSiftingAux(
  DdManager * table,
  MtrNode * treenode,
  Cudd_ReorderingType method)
{
    MtrNode  *auxnode;
    int res;
    Cudd_AggregationType saveCheck;

#ifdef DD_DEBUG
    Mtr_PrintGroups(treenode,1);
#endif
	//1. 递归访问子节点
    auxnode = treenode;
    while (auxnode != NULL) {
		//2. 递归处理子树
		if (auxnode->child != NULL) {
			if (!ddTreeSiftingAux(table, auxnode->child, method))
			return(0);
		//3. 保存和恢复分组检查状态
			saveCheck = table->groupcheck;
			table->groupcheck = CUDD_NO_CHECK;
		//4. 选择合适的重排序方法
			if (method != CUDD_REORDER_LAZY_SIFT)
			res = ddReorderChildren(table, auxnode, CUDD_REORDER_GROUP_SIFT);
			else
			res = ddReorderChildren(table, auxnode, CUDD_REORDER_LAZY_SIFT);
			table->groupcheck = saveCheck;	
			if (res == 0)
			return(0);
		}
		//5. 处理叶子节点的分组
		else if (auxnode->size > 1) {
			if (!ddReorderChildren(table, auxnode, method))
			return(0);
		}
	//6. 遍历兄弟节点
	auxnode = auxnode->younger;
    }

    return(1);

} /* end of ddTreeSiftingAux */


#ifdef DD_STATS
/**
  @brief Counts the number of internal nodes of the group tree.

  @return the count.

  @sideeffect None

*/
static int
ddCountInternalMtrNodes(
  DdManager * table,
  MtrNode * treenode)
{
    MtrNode *auxnode;
    int     count,nodeCount;


    nodeCount = 0;
    auxnode = treenode;
    while (auxnode != NULL) {
	if (!(MTR_TEST(auxnode,MTR_TERMINAL))) {
	    nodeCount++;
	    count = ddCountInternalMtrNodes(table,auxnode->child);
	    nodeCount += count;
	}
	auxnode = auxnode->younger;
    }

    return(nodeCount);

} /* end of ddCountInternalMtrNodes */
#endif


/**
  @brief Reorders the children of a group tree node according to
  the options.根据选项对组树节点的子节点重新排序。

  @details After reordering puts all the variables in the group and/or
  its descendents in a single group. This allows hierarchical
  reordering.  If the variables in the group do not exist yet, simply
  does nothing.重新排序后，将组中的所有变量和/或其后代变量归入一个组。这样就可以进行分层重新排序。 如果组中的变量还不存在，则什么也不做。

  @return 1 if successful; 0 otherwise.

  @sideeffect None

*/
static int
ddReorderChildren(
  DdManager * table,
  MtrNode * treenode,
  Cudd_ReorderingType method)
{
    int lower;
    int upper = 0;
    int result;
    unsigned int initialSize;
	//1. 确定变量范围
    ddFindNodeHiLo(table,treenode,&lower,&upper);
	//2. 判断是否需要排序
    /* If upper == -1 these variables do not exist yet. */
    if (upper == -1)
	return(1);

    if (treenode->flags == MTR_FIXED) {
	result = 1;
    } else {
#ifdef DD_STATS
	(void) fprintf(table->out," ");
#endif
	//3. 根据不同重排序方法执行排序
	switch (method) {
	case CUDD_REORDER_RANDOM:
	case CUDD_REORDER_RANDOM_PIVOT:
	    result = cuddSwapping(table,lower,upper,method);
	    break;
	case CUDD_REORDER_SIFT:
	    result = cuddSifting(table,lower,upper);
	    break;
	case CUDD_REORDER_SIFT_CONVERGE:
	    do {
		initialSize = table->keys - table->isolated;
		result = cuddSifting(table,lower,upper);
		if (initialSize <= table->keys - table->isolated)
		    break;
#ifdef DD_STATS
		else
		    (void) fprintf(table->out,"\n");
#endif
	    } while (result != 0);
	    break;
	case CUDD_REORDER_SYMM_SIFT:
	    result = cuddSymmSifting(table,lower,upper);
	    break;
	case CUDD_REORDER_SYMM_SIFT_CONV:
	    result = cuddSymmSiftingConv(table,lower,upper);
	    break;
	case CUDD_REORDER_GROUP_SIFT:
	    if (table->groupcheck == CUDD_NO_CHECK) {
		result = ddGroupSifting(table,lower,upper,ddNoCheck,
					DD_NORMAL_SIFT);
	    } else if (table->groupcheck == CUDD_GROUP_CHECK5) {
		result = ddGroupSifting(table,lower,upper,ddExtSymmCheck,
					DD_NORMAL_SIFT);
	    } else if (table->groupcheck == CUDD_GROUP_CHECK7) {
		result = ddGroupSifting(table,lower,upper,ddExtSymmCheck,
					DD_NORMAL_SIFT);
	    } else {
		(void) fprintf(table->err,
			       "Unknown group ckecking method\n");
		result = 0;
	    }
	    break;
	case CUDD_REORDER_GROUP_SIFT_CONV:
	    do {
		initialSize = table->keys - table->isolated;
		if (table->groupcheck == CUDD_NO_CHECK) {
		    (void) ddGroupSifting(table,lower,upper,ddNoCheck,
                                          DD_NORMAL_SIFT);
		} else if (table->groupcheck == CUDD_GROUP_CHECK5) {
		    (void) ddGroupSifting(table,lower,upper,ddExtSymmCheck,
                                          DD_NORMAL_SIFT);
		} else if (table->groupcheck == CUDD_GROUP_CHECK7) {
		    (void) ddGroupSifting(table,lower,upper,ddExtSymmCheck,
                                          DD_NORMAL_SIFT);
		} else {
		    (void) fprintf(table->err,
				   "Unknown group ckecking method\n");
		}
#ifdef DD_STATS
		(void) fprintf(table->out,"\n");
#endif
		result = cuddWindowReorder(table,lower,upper,
					   CUDD_REORDER_WINDOW4);
		if (initialSize <= table->keys - table->isolated)
		    break;
#ifdef DD_STATS
		else
		    (void) fprintf(table->out,"\n");
#endif
	    } while (result != 0);
	    break;
	case CUDD_REORDER_WINDOW2:
	case CUDD_REORDER_WINDOW3:
	case CUDD_REORDER_WINDOW4:
	case CUDD_REORDER_WINDOW2_CONV:
	case CUDD_REORDER_WINDOW3_CONV:
	case CUDD_REORDER_WINDOW4_CONV:
	    result = cuddWindowReorder(table,lower,upper,method);
	    break;
	case CUDD_REORDER_ANNEALING:
	    result = cuddAnnealing(table,lower,upper);
	    break;
	case CUDD_REORDER_GENETIC:
	    result = cuddGa(table,lower,upper);
	    break;
	case CUDD_REORDER_LINEAR:
	    result = cuddLinearAndSifting(table,lower,upper);
	    break;
	case CUDD_REORDER_LINEAR_CONVERGE:
	    do {
		initialSize = table->keys - table->isolated;
		result = cuddLinearAndSifting(table,lower,upper);
		if (initialSize <= table->keys - table->isolated)
		    break;
#ifdef DD_STATS
		else
		    (void) fprintf(table->out,"\n");
#endif
	    } while (result != 0);
	    break;
	case CUDD_REORDER_EXACT:
	    result = cuddExact(table,lower,upper);
	    break;
	case CUDD_REORDER_LAZY_SIFT:
	    result = ddGroupSifting(table,lower,upper,ddVarGroupCheck,
				    DD_LAZY_SIFT);
	    break;
	default:
	    return(0);
	}
    }

    /* Create a single group for all the variables that were sifted,
    ** so that they will be treated as a single block by successive
    ** invocations of ddGroupSifting. 为所有筛选过的变量创建一个组，以便在连续调用 ddGroupSifting 时将它们视为一个单独的块。
    */
	//4. 合并节点组
    ddMergeGroups(table,treenode,lower,upper);

#ifdef DD_DEBUG
    if (table->enableExtraDebug > 0)
        (void) fprintf(table->out,"ddReorderChildren:");
#endif

    return(result);

} /* end of ddReorderChildren */


/**
  @brief Finds the lower and upper bounds of the group represented
  by treenode.查找由 treenode 表示的组的下限和上限。

  @details From the index and size fields we need to derive the
  current positions, and find maximum and minimum.我们需要根据索引和大小字段推导出当前位置，并找出最大值和最小值。

  @sideeffect The bounds are returned as side effects.

*/
static void
ddFindNodeHiLo(
  DdManager * table,
  MtrNode * treenode,
  int * lower,
  int * upper)
{
    int low;
    int high;

    /* Check whether no variables in this group already exist. 检查该组中是否已不存在变量。
    ** If so, return immediately. The calling procedure will know from	如果是，则立即返回。
    ** the values of upper that no reordering is needed.	调用存储过程将从 upper 的值中得知无需重新排序。
    */
    if ((int) treenode->low >= table->size) {
	*lower = table->size;
	*upper = -1;
	return;
    }

    *lower = low = (unsigned int) table->perm[treenode->index];
    high = (int) (low + treenode->size - 1);

    if (high >= table->size) {
	/* This is the case of a partially existing group. The aim is to	这是一个部分存在的组的情况。
	** reorder as many variables as safely possible.  If the tree		我们的目的是尽可能安全地对变量重新排序。
	** node is terminal, we just reorder the subset of the group		如果树节点是终端，我们只需对当前存在的分组子集重新排序。 
	** that is currently in existence.  If the group has				如果分组有子分组，那么我们只对完全实例化的子分组重新排序。
	** subgroups, then we only reorder those subgroups that are			这样，我们就能避免将一个组打散。
	** fully instantiated.  This way we avoid breaking up a group.
	*/
	MtrNode *auxnode = treenode->child;
	if (auxnode == NULL) {
	    *upper = (unsigned int) table->size - 1;
	} else {
	    /* Search the subgroup that strands the table->size line.
	    ** If the first group starts at 0 and goes past table->size
	    ** upper will get -1, thus correctly signaling that no reordering
	    ** should take place.如果第一组从 0 开始，经过 table->size upper 将得到-1，从而正确地表明不应重新排序。
	    */
	    while (auxnode != NULL) {
		int thisLower = table->perm[auxnode->low];
		int thisUpper = thisLower + auxnode->size - 1;
		if (thisUpper >= table->size && thisLower < table->size)
		    *upper = (unsigned int) thisLower - 1;
		auxnode = auxnode->younger;
	    }
	}
    } else {
	/* Normal case: All the variables of the group exist. */
	*upper = (unsigned int) high;
    }

#ifdef DD_DEBUG
    /* Make sure that all variables in group are contiguous. */
    assert(treenode->size >= (MtrHalfWord) (*upper - *lower + 1));
#endif

    return;

} /* end of ddFindNodeHiLo */


/**
  @brief Comparison function used by qsort.

  @details Comparison function used by qsort to order the variables
  according to the number of keys in the subtables.

  @return the difference in number of keys between the two variables
  being compared.

  @sideeffect None

*/
static int
ddUniqueCompareGroup(
  void const * ptrX,
  void const * ptrY)
{
    IndexKey const * pX = (IndexKey const *) ptrX;
    IndexKey const * pY = (IndexKey const *) ptrY;
#if 0
    if (pY->keys == pX->keys) {
	return(pX->index - pY->index);
    }
#endif
    return(pY->keys - pX->keys);

} /* end of ddUniqueCompareGroup */


/**
  @brief Sifts from treenode->low to treenode->high.

  @details If croupcheck == CUDD_GROUP_CHECK7, it checks for group
  creation at the end of the initial sifting. If a group is created,
  it is then sifted again. After sifting one variable, the group that
  contains it is dissolved.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddGroupSifting(
  DdManager * table,
  int  lower,
  int  upper,
  DD_CHKFP checkFunction,
  int lazyFlag)
{
    IndexKey	*var;
    int		i,j,x,xInit;
    int		nvars;
    int		classes;
    int		result;
    int		*sifted;
    int		merged;
    int		dissolve;
#ifdef DD_STATS
    unsigned	previousSize;
#endif
    int		xindex;

    nvars = table->size;

    /* Order variables to sift. */
    sifted = NULL;
    var = ALLOC(IndexKey,nvars);
    if (var == NULL) {
	table->errorCode = CUDD_MEMORY_OUT;
	goto ddGroupSiftingOutOfMem;
    }
    sifted = ALLOC(int,nvars);
    if (sifted == NULL) {
	table->errorCode = CUDD_MEMORY_OUT;
	goto ddGroupSiftingOutOfMem;
    }

    /* Here we consider only one representative for each group. */
    for (i = 0, classes = 0; i < nvars; i++) {
	sifted[i] = 0;
	x = table->perm[i];
	if ((unsigned) x >= table->subtables[x].next) {
	    var[classes].index = i;
	    var[classes].keys = table->subtables[x].keys;
	    classes++;
	}
    }

    util_qsort(var, classes, sizeof(IndexKey), ddUniqueCompareGroup);

    if (lazyFlag) {
	for (i = 0; i < nvars; i ++) {
	    ddResetVarHandled(table, i);
	}
    }

    /* Now sift. */
    for (i = 0; i < ddMin(table->siftMaxVar,classes); i++) {
	if (table->ddTotalNumberSwapping >= table->siftMaxSwap)
	    break;
        if (util_cpu_time() - table->startTime + table->reordTime
            > table->timeLimit) {
            table->autoDyn = 0; /* prevent further reordering */
            break;
        }
        if (table->terminationCallback != NULL &&
            table->terminationCallback(table->tcbArg)) {
            table->autoDyn = 0; /* prevent further reordering */
            break;
        }
	xindex = var[i].index;
	if (sifted[xindex] == 1) /* variable already sifted as part of group */
	    continue;
	x = table->perm[xindex]; /* find current level of this variable */

	if (x < lower || x > upper || table->subtables[x].bindVar == 1)
	    continue;
#ifdef DD_STATS
	previousSize = table->keys - table->isolated;
#endif
#ifdef DD_DEBUG
	/* x is bottom of group */
	assert((unsigned) x >= table->subtables[x].next);
#endif
	if ((unsigned) x == table->subtables[x].next) {
	    dissolve = 1;
	    result = ddGroupSiftingAux(table,x,lower,upper,checkFunction,
					lazyFlag);
	} else {
	    dissolve = 0;
	    result = ddGroupSiftingAux(table,x,lower,upper,ddNoCheck,lazyFlag);
	}
	if (!result) goto ddGroupSiftingOutOfMem;

	/* check for aggregation */
	merged = 0;
	if (lazyFlag == 0 && table->groupcheck == CUDD_GROUP_CHECK7) {
	    x = table->perm[xindex]; /* find current level */
	    if ((unsigned) x == table->subtables[x].next) { /* not part of a group */
		if (x != upper && sifted[table->invperm[x+1]] == 0 &&
		(unsigned) x+1 == table->subtables[x+1].next) {
		    if (ddSecDiffCheck(table,x,x+1)) {
			merged =1;
			ddCreateGroup(table,x,x+1);
		    }
		}
		if (x != lower && sifted[table->invperm[x-1]] == 0 &&
		(unsigned) x-1 == table->subtables[x-1].next) {
		    if (ddSecDiffCheck(table,x-1,x)) {
			merged =1;
			ddCreateGroup(table,x-1,x);
		    }
		}
	    }
	}

	if (merged) { /* a group was created */
	    /* move x to bottom of group */
	    while ((unsigned) x < table->subtables[x].next)
		x = table->subtables[x].next;
	    /* sift */
	    result = ddGroupSiftingAux(table,x,lower,upper,ddNoCheck,lazyFlag);
	    if (!result) goto ddGroupSiftingOutOfMem;
#ifdef DD_STATS
	    if (table->keys < previousSize + table->isolated) {
		(void) fprintf(table->out,"_");
	    } else if (table->keys > previousSize + table->isolated) {
		(void) fprintf(table->out,"^");
	    } else {
		(void) fprintf(table->out,"*");
	    }
	    fflush(table->out);
	} else {
	    if (table->keys < previousSize + table->isolated) {
		(void) fprintf(table->out,"-");
	    } else if (table->keys > previousSize + table->isolated) {
		(void) fprintf(table->out,"+");
	    } else {
		(void) fprintf(table->out,"=");
	    }
	    fflush(table->out);
#endif
	}

	/* Mark variables in the group just sifted. */
	x = table->perm[xindex];
	if ((unsigned) x != table->subtables[x].next) {
	    xInit = x;
	    do {
		j = table->invperm[x];
		sifted[j] = 1;
		x = table->subtables[x].next;
	    } while (x != xInit);

	    /* Dissolve the group if it was created. */
	    if (lazyFlag == 0 && dissolve) {
		do {
		    j = table->subtables[x].next;
		    table->subtables[x].next = x;
		    x = j;
		} while (x != xInit);
	    }
	}

#ifdef DD_DEBUG
	if (table->enableExtraDebug > 0)
            (void) fprintf(table->out,"ddGroupSifting:");
#endif

        if (lazyFlag) ddSetVarHandled(table, xindex);
    } /* for */

    FREE(sifted);
    FREE(var);

    return(1);

ddGroupSiftingOutOfMem:
    if (var != NULL)	FREE(var);
    if (sifted != NULL)	FREE(sifted);

    return(0);

} /* end of ddGroupSifting */


/**
  @brief Creates a group encompassing variables from x to y in the
  %DD table.

  @details In the current implementation it must be y == x+1.

  @sideeffect None

*/
static void
ddCreateGroup(
  DdManager * table,
  int  x,
  int  y)
{
    int  gybot;

#ifdef DD_DEBUG
    assert(y == x+1);
#endif

    /* Find bottom of second group. */
    gybot = y;
    while ((unsigned) gybot < table->subtables[gybot].next)
	gybot = table->subtables[gybot].next;

    /* Link groups. */
    table->subtables[x].next = y;
    table->subtables[gybot].next = x;

    return;

} /* ddCreateGroup */


/**
  @brief Sifts one variable up and down until it has taken all
  positions. Checks for aggregation.

  @details There may be at most two sweeps, even if the group grows.
  Assumes that x is either an isolated variable, or it is the bottom
  of a group. All groups may not have been found. The variable being
  moved is returned to the best position seen during sifting.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddGroupSiftingAux(
  DdManager * table,
  int  x,
  int  xLow,
  int  xHigh,
  DD_CHKFP checkFunction,
  int lazyFlag)
{
    Move *move;
    Move *moves;	/* list of moves */
    int  initialSize;
    int  result;
    int  y;
    int  topbot;

#ifdef DD_DEBUG
    if (table->enableExtraDebug > 0)
        (void) fprintf(table->out,
                       "ddGroupSiftingAux from %d to %d\n",xLow,xHigh);
    assert((unsigned) x >= table->subtables[x].next); /* x is bottom of group */
#endif

    table->originalSize = (table->keys - table->isolated);
    initialSize = (int) table->originalSize;
    moves = NULL;

    /* If we have a singleton, we check for aggregation in both
    ** directions before we sift.
    */
    if ((unsigned) x == table->subtables[x].next) {
	/* Will go down first, unless x == xHigh:
	** Look for aggregation above x.
	*/
	for (y = x; y > xLow; y--) {
	    if (!checkFunction(table,y-1,y))
		break;
	    topbot = table->subtables[y-1].next; /* find top of y-1's group */
	    table->subtables[y-1].next = y;
	    table->subtables[x].next = topbot; /* x is bottom of group so its */
					       /* next is top of y-1's group */
	    y = topbot + 1; /* add 1 for y--; new y is top of group */
	}
	/* Will go up first unless x == xlow:
	** Look for aggregation below x.
	*/
	for (y = x; y < xHigh; y++) {
	    if (!checkFunction(table,y,y+1))
		break;
	    /* find bottom of y+1's group */
	    topbot = y + 1;
	    while ((unsigned) topbot < table->subtables[topbot].next) {
		topbot = table->subtables[topbot].next;
	    }
	    table->subtables[topbot].next = table->subtables[y].next;
	    table->subtables[y].next = y + 1;
	    y = topbot - 1; /* subtract 1 for y++; new y is bottom of group */
	}
    }

    /* Now x may be in the middle of a group.
    ** Find bottom of x's group.
    */
    while ((unsigned) x < table->subtables[x].next)
	x = table->subtables[x].next;

    if (x == xLow) { /* Sift down */
#ifdef DD_DEBUG
	/* x must be a singleton */
	assert((unsigned) x == table->subtables[x].next);
#endif
	if (x == xHigh) return(1);	/* just one variable */

	if (!ddGroupSiftingDown(table,x,xHigh,checkFunction,&moves))
	    goto ddGroupSiftingAuxOutOfMem;
	/* at this point x == xHigh, unless early term */

	/* move backward and stop at best position */
	result = ddGroupSiftingBackward(table,moves,initialSize,
					DD_SIFT_DOWN,lazyFlag);
#ifdef DD_DEBUG
	assert(table->keys - table->isolated <= (unsigned) initialSize);
#endif
	if (!result) goto ddGroupSiftingAuxOutOfMem;

    } else if (cuddNextHigh(table,x) > xHigh) { /* Sift up */
#ifdef DD_DEBUG
	/* x is bottom of group */
	assert((unsigned) x >= table->subtables[x].next);
#endif
	/* Find top of x's group */
	x = table->subtables[x].next;

	if (!ddGroupSiftingUp(table,x,xLow,checkFunction,&moves))
	    goto ddGroupSiftingAuxOutOfMem;
	/* at this point x == xLow, unless early term */

	/* move backward and stop at best position */
	result = ddGroupSiftingBackward(table,moves,initialSize,
					DD_SIFT_UP,lazyFlag);
#ifdef DD_DEBUG
	assert(table->keys - table->isolated <= (unsigned) initialSize);
#endif
	if (!result) goto ddGroupSiftingAuxOutOfMem;

    } else if (x - xLow > xHigh - x) { /* must go down first: shorter */
	if (!ddGroupSiftingDown(table,x,xHigh,checkFunction,&moves))
	    goto ddGroupSiftingAuxOutOfMem;
	/* at this point x == xHigh, unless early term */

	/* Find top of group */
	if (moves) {
	    x = moves->y;
	}
	while ((unsigned) x < table->subtables[x].next)
	    x = table->subtables[x].next;
	x = table->subtables[x].next;
#ifdef DD_DEBUG
	/* x should be the top of a group */
	assert((unsigned) x <= table->subtables[x].next);
#endif

	if (!ddGroupSiftingUp(table,x,xLow,checkFunction,&moves))
	    goto ddGroupSiftingAuxOutOfMem;

	/* move backward and stop at best position */
	result = ddGroupSiftingBackward(table,moves,initialSize,
					DD_SIFT_UP,lazyFlag);
#ifdef DD_DEBUG
	assert(table->keys - table->isolated <= (unsigned) initialSize);
#endif
	if (!result) goto ddGroupSiftingAuxOutOfMem;

    } else { /* moving up first: shorter */
	/* Find top of x's group */
	x = table->subtables[x].next;

	if (!ddGroupSiftingUp(table,x,xLow,checkFunction,&moves))
	    goto ddGroupSiftingAuxOutOfMem;
	/* at this point x == xHigh, unless early term */

	if (moves) {
	    x = moves->x;
	}
	while ((unsigned) x < table->subtables[x].next)
	    x = table->subtables[x].next;
#ifdef DD_DEBUG
	/* x is bottom of a group */
	assert((unsigned) x >= table->subtables[x].next);
#endif

	if (!ddGroupSiftingDown(table,x,xHigh,checkFunction,&moves))
	    goto ddGroupSiftingAuxOutOfMem;

	/* move backward and stop at best position */
	result = ddGroupSiftingBackward(table,moves,initialSize,
					DD_SIFT_DOWN,lazyFlag);
#ifdef DD_DEBUG
	assert(table->keys - table->isolated <= (unsigned) initialSize);
#endif
	if (!result) goto ddGroupSiftingAuxOutOfMem;
    }

    while (moves != NULL) {
	move = moves->next;
	cuddDeallocMove(table, moves);
	moves = move;
    }

    return(1);

ddGroupSiftingAuxOutOfMem:
    while (moves != NULL) {
	move = moves->next;
	cuddDeallocMove(table, moves);
	moves = move;
    }

    return(0);

} /* end of ddGroupSiftingAux */


/**
  @brief Sifts up a variable until either it reaches position xLow
  or the size of the %DD heap increases too much.

  @details Assumes that y is the top of a group (or a singleton).
  Checks y for aggregation to the adjacent variables. Records all the
  moves that are appended to the list of moves received as input and
  returned as a side effect.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddGroupSiftingUp(
  DdManager * table,
  int  y,
  int  xLow,
  DD_CHKFP checkFunction,
  Move ** moves)
{
    Move *move;
    int  x;
    int  size;
    int  i;
    int  gxtop,gybot;
    int  limitSize;
    int  xindex, yindex;
    int  zindex;
    int  z;
    unsigned int isolated;
    int  L;	/* lower bound on DD size */
#ifdef DD_DEBUG
    int  checkL;
#endif

    yindex = table->invperm[y];

    /* Initialize the lower bound.
    ** The part of the DD below the bottom of y's group will not change.
    ** The part of the DD above y that does not interact with any
    ** variable of y's group will not change.
    ** The rest may vanish in the best case, except for
    ** the nodes at level xLow, which will not vanish, regardless.
    ** What we use here is not really a lower bound, because we ignore
    ** the interactions with all variables except y.
    */
    limitSize = L = (int) (table->keys - table->isolated);
    gybot = y;
    while ((unsigned) gybot < table->subtables[gybot].next)
	gybot = table->subtables[gybot].next;
    for (z = xLow + 1; z <= gybot; z++) {
	zindex = table->invperm[z];
	if (zindex == yindex || cuddTestInteract(table,zindex,yindex)) {
	    isolated = table->vars[zindex]->ref == 1;
	    L -= table->subtables[z].keys - isolated;
	}
    }

    x = cuddNextLow(table,y);
    while (x >= xLow && L <= limitSize) {
#ifdef DD_DEBUG
	gybot = y;
	while ((unsigned) gybot < table->subtables[gybot].next)
	    gybot = table->subtables[gybot].next;
	checkL = table->keys - table->isolated;
	for (z = xLow + 1; z <= gybot; z++) {
	    zindex = table->invperm[z];
	    if (zindex == yindex || cuddTestInteract(table,zindex,yindex)) {
		isolated = table->vars[zindex]->ref == 1;
		checkL -= table->subtables[z].keys - isolated;
	    }
	}
	if (table->enableExtraDebug > 0 && L != checkL) {
	    (void) fprintf(table->out,
			   "Inaccurate lower bound: L = %d checkL = %d\n",
			   L, checkL);
	}
#endif
	gxtop = table->subtables[x].next;
	if (checkFunction(table,x,y)) {
	    /* Group found, attach groups */
	    table->subtables[x].next = y;
	    i = table->subtables[y].next;
	    while (table->subtables[i].next != (unsigned) y)
		i = table->subtables[i].next;
	    table->subtables[i].next = gxtop;
	    move = (Move *)cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddGroupSiftingUpOutOfMem;
	    move->x = x;
	    move->y = y;
	    move->flags = MTR_NEWNODE;
	    move->size = (int) (table->keys - table->isolated);
	    move->next = *moves;
	    *moves = move;
	} else if (table->subtables[x].next == (unsigned) x &&
		   table->subtables[y].next == (unsigned) y) {
	    /* x and y are self groups */
	    xindex = table->invperm[x];
	    size = cuddSwapInPlace(table,x,y);
#ifdef DD_DEBUG
	    assert(table->subtables[x].next == (unsigned) x);
	    assert(table->subtables[y].next == (unsigned) y);
#endif
	    if (size == 0) goto ddGroupSiftingUpOutOfMem;
	    /* Update the lower bound. */
	    if (cuddTestInteract(table,xindex,yindex)) {
		isolated = table->vars[xindex]->ref == 1;
		L += table->subtables[y].keys - isolated;
	    }
	    move = (Move *)cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddGroupSiftingUpOutOfMem;
	    move->x = x;
	    move->y = y;
	    move->flags = MTR_DEFAULT;
	    move->size = size;
	    move->next = *moves;
	    *moves = move;

#ifdef DD_DEBUG
	    if (table->enableExtraDebug > 0)
                (void) fprintf(table->out,
                               "ddGroupSiftingUp (2 single groups):\n");
#endif
	    if ((double) size > (double) limitSize * table->maxGrowth)
		return(1);
	    if (size < limitSize) limitSize = size;
	} else { /* Group move */
	    size = ddGroupMove(table,x,y,moves);
	    if (size == 0) goto ddGroupSiftingUpOutOfMem;
	    /* Update the lower bound. */
	    z = (*moves)->y;
	    do {
		zindex = table->invperm[z];
		if (cuddTestInteract(table,zindex,yindex)) {
		    isolated = table->vars[zindex]->ref == 1;
		    L += table->subtables[z].keys - isolated;
		}
		z = table->subtables[z].next;
	    } while (z != (int) (*moves)->y);
	    if ((double) size > (double) limitSize * table->maxGrowth)
		return(1);
	    if (size < limitSize) limitSize = size;
	}
	y = gxtop;
	x = cuddNextLow(table,y);
    }

    return(1);

ddGroupSiftingUpOutOfMem:
    while (*moves != NULL) {
	move = (*moves)->next;
	cuddDeallocMove(table, *moves);
	*moves = move;
    }
    return(0);

} /* end of ddGroupSiftingUp */


/**
  @brief Sifts down a variable until it reaches position xHigh.

  @details Assumes that x is the bottom of a group (or a singleton).
  Records all the moves.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddGroupSiftingDown(
  DdManager * table,
  int  x,
  int  xHigh,
  DD_CHKFP checkFunction,
  Move ** moves)
{
    Move *move;
    int  y;
    int  size;
    int  limitSize;
    int  gxtop,gybot;
    int  R;	/* upper bound on node decrease */
    int  xindex, yindex;
    unsigned isolated;
    int  allVars;
    int  z;
    int  zindex;
#ifdef DD_DEBUG
    int  checkR;
#endif

    /* If the group consists of simple variables, there is no point in
    ** sifting it down. This check is redundant if the projection functions
    ** do not have external references, because the computation of the
    ** lower bound takes care of the problem.  It is necessary otherwise to
    ** prevent the sifting down of simple variables. */
    y = x;
    allVars = 1;
    do {
	if (table->subtables[y].keys != 1) {
	    allVars = 0;
	    break;
	}
	y = table->subtables[y].next;
    } while (table->subtables[y].next != (unsigned) x);
    if (allVars)
	return(1);

    /* Initialize R. */
    xindex = table->invperm[x];
    gxtop = table->subtables[x].next;
    limitSize = size = (int) (table->keys - table->isolated);
    R = 0;
    for (z = xHigh; z > gxtop; z--) {
	zindex = table->invperm[z];
	if (zindex == xindex || cuddTestInteract(table,xindex,zindex)) {
	    isolated = table->vars[zindex]->ref == 1;
	    R += table->subtables[z].keys - isolated;
	}
    }

    y = cuddNextHigh(table,x);
    while (y <= xHigh && size - R < limitSize) {
#ifdef DD_DEBUG
	gxtop = table->subtables[x].next;
	checkR = 0;
	for (z = xHigh; z > gxtop; z--) {
	    zindex = table->invperm[z];
	    if (zindex == xindex || cuddTestInteract(table,xindex,zindex)) {
		isolated = table->vars[zindex]->ref == 1;
		checkR += table->subtables[z].keys - isolated;
	    }
	}
	assert(R >= checkR);
#endif
	/* Find bottom of y group. */
	gybot = table->subtables[y].next;
	while (table->subtables[gybot].next != (unsigned) y)
	    gybot = table->subtables[gybot].next;

	if (checkFunction(table,x,y)) {
	    /* Group found: attach groups and record move. */
	    gxtop = table->subtables[x].next;
	    table->subtables[x].next = y;
	    table->subtables[gybot].next = gxtop;
	    move = (Move *)cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddGroupSiftingDownOutOfMem;
	    move->x = x;
	    move->y = y;
	    move->flags = MTR_NEWNODE;
	    move->size = (int) (table->keys - table->isolated);
	    move->next = *moves;
	    *moves = move;
	} else if (table->subtables[x].next == (unsigned) x &&
		   table->subtables[y].next == (unsigned) y) {
	    /* x and y are self groups */
	    /* Update upper bound on node decrease. */
	    yindex = table->invperm[y];
	    if (cuddTestInteract(table,xindex,yindex)) {
		isolated = table->vars[yindex]->ref == 1;
		R -= table->subtables[y].keys - isolated;
	    }
	    size = cuddSwapInPlace(table,x,y);
#ifdef DD_DEBUG
	    assert(table->subtables[x].next == (unsigned) x);
	    assert(table->subtables[y].next == (unsigned) y);
#endif
	    if (size == 0) goto ddGroupSiftingDownOutOfMem;

	    /* Record move. */
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddGroupSiftingDownOutOfMem;
	    move->x = x;
	    move->y = y;
	    move->flags = MTR_DEFAULT;
	    move->size = size;
	    move->next = *moves;
	    *moves = move;

#ifdef DD_DEBUG
	    if (table->enableExtraDebug > 0)
                (void) fprintf(table->out,
                               "ddGroupSiftingDown (2 single groups):\n");
#endif
	    if ((double) size > (double) limitSize * table->maxGrowth)
		return(1);
	    if (size < limitSize) limitSize = size;

	} else { /* Group move */
	    /* Update upper bound on node decrease: first phase. */
	    gxtop = table->subtables[x].next;
	    z = gxtop + 1;
	    do {
		zindex = table->invperm[z];
		if (zindex == xindex || cuddTestInteract(table,xindex,zindex)) {
		    isolated = table->vars[zindex]->ref == 1;
		    R -= table->subtables[z].keys - isolated;
		}
		z++;
	    } while (z <= gybot);
	    size = ddGroupMove(table,x,y,moves);
	    if (size == 0) goto ddGroupSiftingDownOutOfMem;
	    if ((double) size > (double) limitSize * table->maxGrowth)
		return(1);
	    if (size < limitSize) limitSize = size;

	    /* Update upper bound on node decrease: second phase. */
	    gxtop = table->subtables[gybot].next;
	    for (z = gxtop + 1; z <= gybot; z++) {
		zindex = table->invperm[z];
		if (zindex == xindex || cuddTestInteract(table,xindex,zindex)) {
		    isolated = table->vars[zindex]->ref == 1;
		    R += table->subtables[z].keys - isolated;
		}
	    }
	}
	x = gybot;
	y = cuddNextHigh(table,x);
    }

    return(1);

ddGroupSiftingDownOutOfMem:
    while (*moves != NULL) {
	move = (*moves)->next;
	cuddDeallocMove(table, *moves);
	*moves = move;
    }

    return(0);

} /* end of ddGroupSiftingDown */


/**
  @brief Swaps two groups and records the move.

  @return the number of keys in the %DD table in case of success; 0
  otherwise.

  @sideeffect None

*/
static int
ddGroupMove(
  DdManager * table,
  int  x,
  int  y,
  Move ** moves)
{
    Move *move;
    int  size;
    int  i,j,xtop,xbot,xsize,ytop,ybot,ysize,newxtop;
    int  swapx = 0, swapy = 0;
#if defined(DD_DEBUG) && defined(DD_VERBOSE)
    int  initialSize,bestSize;
#endif

#ifdef DD_DEBUG
    /* We assume that x < y */
    assert(x < y);
#endif
    /* Find top, bottom, and size for the two groups. */
    xbot = x;
    xtop = table->subtables[x].next;
    xsize = xbot - xtop + 1;
    ybot = y;
    while ((unsigned) ybot < table->subtables[ybot].next)
	ybot = table->subtables[ybot].next;
    ytop = y;
    ysize = ybot - ytop + 1;

#if defined(DD_DEBUG) && defined(DD_VERBOSE)
    initialSize = bestSize = table->keys - table->isolated;
#endif
    /* Sift the variables of the second group up through the first group */
    for (i = 1; i <= ysize; i++) {
	for (j = 1; j <= xsize; j++) {
	    size = cuddSwapInPlace(table,x,y);
	    if (size == 0) goto ddGroupMoveOutOfMem;
#if defined(DD_DEBUG) && defined(DD_VERBOSE)
	    if (size < bestSize)
		bestSize = size;
#endif
	    swapx = x; swapy = y;
	    y = x;
	    x = cuddNextLow(table,y);
	}
	y = ytop + i;
	x = cuddNextLow(table,y);
    }
#if defined(DD_DEBUG) && defined(DD_VERBOSE)
    if ((bestSize < initialSize) && (bestSize < size))
	(void) fprintf(table->out,"Missed local minimum: initialSize:%d  bestSize:%d  finalSize:%d\n",initialSize,bestSize,size);
#endif

    /* fix groups */
    y = xtop; /* ytop is now where xtop used to be */
    for (i = 0; i < ysize - 1; i++) {
	table->subtables[y].next = cuddNextHigh(table,y);
	y = cuddNextHigh(table,y);
    }
    table->subtables[y].next = xtop; /* y is bottom of its group, join */
				    /* it to top of its group */
    x = cuddNextHigh(table,y);
    newxtop = x;
    for (i = 0; i < xsize - 1; i++) {
	table->subtables[x].next = cuddNextHigh(table,x);
	x = cuddNextHigh(table,x);
    }
    table->subtables[x].next = newxtop; /* x is bottom of its group, join */
				    /* it to top of its group */
#ifdef DD_DEBUG
    if (table->enableExtraDebug > 0)
        (void) fprintf(table->out,"ddGroupMove:\n");
#endif

    /* Store group move */
    move = (Move *) cuddDynamicAllocNode(table);
    if (move == NULL) goto ddGroupMoveOutOfMem;
    move->x = swapx;
    move->y = swapy;
    move->flags = MTR_DEFAULT;
    move->size = (int) (table->keys - table->isolated);
    move->next = *moves;
    *moves = move;

    return((int)(table->keys - table->isolated));

ddGroupMoveOutOfMem:
    while (*moves != NULL) {
	move = (*moves)->next;
	cuddDeallocMove(table, *moves);
	*moves = move;
    }
    return(0);

} /* end of ddGroupMove */


/**
  @brief Undoes the swap two groups.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddGroupMoveBackward(
  DdManager * table,
  int  x,
  int  y)
{
    int size;
    int i,j,xtop,xbot,xsize,ytop,ybot,ysize,newxtop;


#ifdef DD_DEBUG
    /* We assume that x < y */
    assert(x < y);
#endif

    /* Find top, bottom, and size for the two groups. */
    xbot = x;
    xtop = table->subtables[x].next;
    xsize = xbot - xtop + 1;
    ybot = y;
    while ((unsigned) ybot < table->subtables[ybot].next)
	ybot = table->subtables[ybot].next;
    ytop = y;
    ysize = ybot - ytop + 1;

    /* Sift the variables of the second group up through the first group */
    for (i = 1; i <= ysize; i++) {
	for (j = 1; j <= xsize; j++) {
	    size = cuddSwapInPlace(table,x,y);
	    if (size == 0)
		return(0);
	    y = x;
	    x = cuddNextLow(table,y);
	}
	y = ytop + i;
	x = cuddNextLow(table,y);
    }

    /* fix groups */
    y = xtop;
    for (i = 0; i < ysize - 1; i++) {
	table->subtables[y].next = cuddNextHigh(table,y);
	y = cuddNextHigh(table,y);
    }
    table->subtables[y].next = xtop; /* y is bottom of its group, join */
				    /* to its top */
    x = cuddNextHigh(table,y);
    newxtop = x;
    for (i = 0; i < xsize - 1; i++) {
	table->subtables[x].next = cuddNextHigh(table,x);
	x = cuddNextHigh(table,x);
    }
    table->subtables[x].next = newxtop; /* x is bottom of its group, join */
				    /* to its top */
#ifdef DD_DEBUG
    if (table->enableExtraDebug > 0)
        (void) fprintf(table->out,"ddGroupMoveBackward:\n");
#endif

    return(1);

} /* end of ddGroupMoveBackward */


/**
  @brief Determines the best position for a variables and returns
  it there.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddGroupSiftingBackward(
  DdManager * table,
  Move * moves,
  int  size,
  int  upFlag,
  int  lazyFlag)
{
    Move *move;
    int  res;
    Move *end_move = NULL;
    int diff, tmp_diff;
    int index;
    unsigned int pairlev;

    if (lazyFlag) {
	end_move = NULL;

	/* Find the minimum size, and the earliest position at which it
	** was achieved. */
	for (move = moves; move != NULL; move = move->next) {
	    if (move->size < size) {
		size = move->size;
		end_move = move;
	    } else if (move->size == size) {
		if (end_move == NULL) end_move = move;
	    }
	}

	/* Find among the moves that give minimum size the one that
	** minimizes the distance from the corresponding variable. */
	if (moves != NULL) {
	    diff = Cudd_ReadSize(table) + 1;
	    index = (upFlag == 1) ?
		    table->invperm[moves->x] : table->invperm[moves->y];
	    pairlev =
		(unsigned) table->perm[Cudd_bddReadPairIndex(table, index)];

	    for (move = moves; move != NULL; move = move->next) {
		if (move->size == size) {
		    if (upFlag == 1) {
			tmp_diff = (move->x > pairlev) ?
				    move->x - pairlev : pairlev - move->x;
		    } else {
			tmp_diff = (move->y > pairlev) ?
				    move->y - pairlev : pairlev - move->y;
		    }
		    if (tmp_diff < diff) {
			diff = tmp_diff;
			end_move = move;
		    }
		}
	    }
	}
    } else {
	/* Find the minimum size. */
	for (move = moves; move != NULL; move = move->next) {
	    if (move->size < size) {
		size = move->size;
	    }
	}
    }

    /* In case of lazy sifting, end_move identifies the position at
    ** which we want to stop.  Otherwise, we stop as soon as we meet
    ** the minimum size. */
    for (move = moves; move != NULL; move = move->next) {
	if (lazyFlag) {
	    if (move == end_move) return(1);
	} else {
	    if (move->size == size) return(1);
	}
	if ((table->subtables[move->x].next == move->x) &&
	(table->subtables[move->y].next == move->y)) {
	    res = cuddSwapInPlace(table,(int)move->x,(int)move->y);
	    if (!res) return(0);
#ifdef DD_DEBUG
	    if (table->enableExtraDebug > 0)
                (void) fprintf(table->out,"ddGroupSiftingBackward:\n");
	    assert(table->subtables[move->x].next == move->x);
	    assert(table->subtables[move->y].next == move->y);
#endif
	} else { /* Group move necessary */
	    if (move->flags == MTR_NEWNODE) {
		ddDissolveGroup(table,(int)move->x,(int)move->y);
	    } else {
		res = ddGroupMoveBackward(table,(int)move->x,(int)move->y);
		if (!res) return(0);
	    }
	}

    }

    return(1);

} /* end of ddGroupSiftingBackward */


/**
  @brief Merges groups in the %DD table.

  @details Creates a single group from low to high and adjusts the
  index field of the tree node.

  @sideeffect None

*/
static void
ddMergeGroups(
  DdManager * table,
  MtrNode * treenode,
  int  low,
  int  high)
{
    int i;
    MtrNode *auxnode;
    int saveindex;
    int newindex;

    /* Merge all variables from low to high in one group, unless
    ** this is the topmost group. In such a case we do not merge lest
    ** we lose the symmetry information. */
    if (treenode != table->tree) {
	for (i = low; i < high; i++)
	    table->subtables[i].next = i+1;
	table->subtables[high].next = low;
    }

    /* Adjust the index fields of the tree nodes. If a node is the
    ** first child of its parent, then the parent may also need adjustment. */
    saveindex = treenode->index;
    newindex = table->invperm[low];
    auxnode = treenode;
    do {
	auxnode->index = newindex;
	if (auxnode->parent == NULL ||
		(int) auxnode->parent->index != saveindex)
	    break;
	auxnode = auxnode->parent;
    } while (1);
    return;

} /* end of ddMergeGroups */


/**
  @brief Dissolves a group in the %DD table.

  @details x and y are variables in a group to be cut in two. The cut
  is to pass between x and y.

  @sideeffect None

*/
static void
ddDissolveGroup(
  DdManager * table,
  int  x,
  int  y)
{
    int topx;
    int boty;

    /* find top and bottom of the two groups */
    boty = y;
    while ((unsigned) boty < table->subtables[boty].next)
	boty = table->subtables[boty].next;

    topx = table->subtables[boty].next;

    table->subtables[boty].next = y;
    table->subtables[x].next = topx;

    return;

} /* end of ddDissolveGroup */


/**
  @brief Pretends to check two variables for aggregation.

  @return always 0.

  @sideeffect None

*/
static int
ddNoCheck(
  DdManager * table,
  int  x,
  int  y)
{
    (void) table; /* avoid warning */
    (void) x;     /* avoid warning */
    (void) y;     /* avoid warning */
    return(0);

} /* end of ddNoCheck */


/**
  @brief Checks two variables for aggregation.

  @details The check is based on the second difference of the number
  of nodes as a function of the layer. If the second difference is
  lower than a given threshold (typically negative) then the two
  variables should be aggregated.

  @return 1 if the two variables pass the test; 0 otherwise.

  @sideeffect None

*/
static int
ddSecDiffCheck(
  DdManager * table,
  int  x,
  int  y)
{
    double Nx,Nx_1;
    double Sx;
    double threshold;
    int    xindex,yindex;

    if (x==0) return(0);

#ifdef DD_STATS
    table->secdiffcalls++;
#endif
    Nx = (double) table->subtables[x].keys;
    Nx_1 = (double) table->subtables[x-1].keys;
    Sx = (table->subtables[y].keys/Nx) - (Nx/Nx_1);

    threshold = table->recomb / 100.0;
    if (Sx < threshold) {
	xindex = table->invperm[x];
	yindex = table->invperm[y];
	if (cuddTestInteract(table,xindex,yindex)) {
#if defined(DD_DEBUG) && defined(DD_VERBOSE)
	    (void) fprintf(table->out,
			   "Second difference for %d = %g Pos(%d)\n",
			   table->invperm[x],Sx,x);
#endif
#ifdef DD_STATS
	    table->secdiff++;
#endif
	    return(1);
	} else {
#ifdef DD_STATS
	    table->secdiffmisfire++;
#endif
	    return(0);
	}

    }
    return(0);

} /* end of ddSecDiffCheck */


/**
  @brief Checks for extended symmetry of x and y.

  @return 1 in case of extended symmetry; 0 otherwise.

  @sideeffect None

*/
static int
ddExtSymmCheck(
  DdManager * table,
  int  x,
  int  y)
{
    DdNode *f,*f0,*f1,*f01,*f00,*f11,*f10;
    DdNode *one;
    int comple;		/* f0 is complemented */
    int notproj;	/* f is not a projection function */
    int arccount;	/* number of arcs from layer x to layer y */
    int TotalRefCount;	/* total reference count of layer y minus 1 */
    int counter;	/* number of nodes of layer x that are allowed */
			/* to violate extended symmetry conditions */
    int arccounter;	/* number of arcs into layer y that are allowed */
			/* to come from layers other than x */
    int i;
    int xindex;
    int yindex;
    int res;
    int slots;
    DdNodePtr *list;
    DdNode *sentinel = &(table->sentinel);

    xindex = table->invperm[x];
    yindex = table->invperm[y];

    /* If the two variables do not interact, we do not want to merge them. */
    if (!cuddTestInteract(table,xindex,yindex))
	return(0);

#ifdef DD_DEBUG
    /* Checks that x and y do not contain just the projection functions.
    ** With the test on interaction, these test become redundant,
    ** because an isolated projection function does not interact with
    ** any other variable.
    */
    if (table->subtables[x].keys == 1) {
	assert(table->vars[xindex]->ref != 1);
    }
    if (table->subtables[y].keys == 1) {
	assert(table->vars[yindex]->ref != 1);
    }
#endif

#ifdef DD_STATS
    table->extsymmcalls++;
#endif

    arccount = 0;
    counter = (int) (table->subtables[x].keys *
	      (table->symmviolation/100.0) + 0.5);
    one = DD_ONE(table);

    slots = table->subtables[x].slots;
    list = table->subtables[x].nodelist;
    for (i = 0; i < slots; i++) {
	f = list[i];
	while (f != sentinel) {
	    /* Find f1, f0, f11, f10, f01, f00. */
	    f1 = cuddT(f);
	    f0 = Cudd_Regular(cuddE(f));
	    comple = Cudd_IsComplement(cuddE(f));
	    notproj = f1 != one || f0 != one || f->ref != (DdHalfWord) 1;
	    if (f1->index == (unsigned) yindex) {
		arccount++;
		f11 = cuddT(f1); f10 = cuddE(f1);
	    } else {
		if ((int) f0->index != yindex) {
		    /* If f is an isolated projection function it is
		    ** allowed to bypass layer y.
		    */
		    if (notproj) {
			if (counter == 0)
			    return(0);
			counter--; /* f bypasses layer y */
		    }
		}
		f11 = f10 = f1;
	    }
	    if ((int) f0->index == yindex) {
		arccount++;
		f01 = cuddT(f0); f00 = cuddE(f0);
	    } else {
		f01 = f00 = f0;
	    }
	    if (comple) {
		f01 = Cudd_Not(f01);
		f00 = Cudd_Not(f00);
	    }

	    /* Unless we are looking at a projection function
	    ** without external references except the one from the
	    ** table, we insist that f01 == f10 or f11 == f00
	    */
	    if (notproj) {
		if (f01 != f10 && f11 != f00) {
		    if (counter == 0)
			return(0);
		    counter--;
		}
	    }

	    f = f->next;
	} /* while */
    } /* for */

    /* Calculate the total reference counts of y */
    TotalRefCount = -1;	/* -1 for projection function */
    slots = table->subtables[y].slots;
    list = table->subtables[y].nodelist;
    for (i = 0; i < slots; i++) {
	f = list[i];
	while (f != sentinel) {
	    TotalRefCount += f->ref;
	    f = f->next;
	}
    }

    arccounter = (int) (table->subtables[y].keys *
		 (table->arcviolation/100.0) + 0.5);
    res = arccount >= TotalRefCount - arccounter;

#if defined(DD_DEBUG) && defined(DD_VERBOSE)
    if (res) {
	(void) fprintf(table->out,
		       "Found extended symmetry! x = %d\ty = %d\tPos(%d,%d)\n",
		       xindex,yindex,x,y);
    }
#endif

#ifdef DD_STATS
    if (res)
	table->extsymm++;
#endif
    return(res);

} /* end ddExtSymmCheck */


/**
  @brief Checks for grouping of x and y.

  @details This function is used for lazy sifting.

  @return 1 in case of grouping; 0 otherwise.

  @sideeffect None

*/
static int
ddVarGroupCheck(
  DdManager * table,
  int x,
  int y)
{
    int xindex = table->invperm[x];
    int yindex = table->invperm[y];

    if (Cudd_bddIsVarToBeUngrouped(table, xindex)) return(0);

    if (Cudd_bddReadPairIndex(table, xindex) == yindex) {
	if (ddIsVarHandled(table, xindex) ||
	    ddIsVarHandled(table, yindex)) {
	    if (Cudd_bddIsVarToBeGrouped(table, xindex) ||
		Cudd_bddIsVarToBeGrouped(table, yindex) ) {
		if (table->keys - table->isolated <= table->originalSize) {
		    return(1);
		}
	    }
	}
    }

    return(0);

} /* end of ddVarGroupCheck */


/**
  @brief Sets a variable to already handled.

  @details This function is used for lazy sifting.

  @sideeffect none

*/
static int
ddSetVarHandled(
  DdManager *dd,
  int index)
{
    if (index >= dd->size || index < 0) return(0);
    dd->subtables[dd->perm[index]].varHandled = 1;
    return(1);

} /* end of ddSetVarHandled */


/**
  @brief Resets a variable to be processed.

  @details This function is used for lazy sifting.

  @sideeffect none

*/
static int
ddResetVarHandled(
  DdManager *dd,
  int index)
{
    if (index >= dd->size || index < 0) return(0);
    dd->subtables[dd->perm[index]].varHandled = 0;
    return(1);

} /* end of ddResetVarHandled */


/**
  @brief Checks whether a variables is already handled.

  @details This function is used for lazy sifting.

  @sideeffect none

*/
static int
ddIsVarHandled(
  DdManager *dd,
  int index)
{
    if (index >= dd->size || index < 0) return(-1);
    return dd->subtables[dd->perm[index]].varHandled;

} /* end of ddIsVarHandled */
