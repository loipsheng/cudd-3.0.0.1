/**
  @file

  @ingroup cudd

  @brief Functions for dynamic variable reordering.

  @author Shipra Panda, Bernard Plessier, Fabio Somenzi

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

/*---------------------------------------------------------------------------*/
/* Stucture declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

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

static int ddUniqueCompare (void const *ptrX, void const *ptrY);
static Move * ddSwapAny (DdManager *table, int x, int y);
static int ddSiftingAux (DdManager *table, int x, int xLow, int xHigh);
static Move * ddSiftingUp (DdManager *table, int y, int xLow);
static Move * ddSiftingDown (DdManager *table, int x, int xHigh);
static int ddSiftingBackward (DdManager *table, int size, Move *moves);
static int ddReorderPreprocess (DdManager *table);
static int ddReorderPostprocess (DdManager *table);
static int ddShuffle (DdManager *table, int *permutation);
static int ddSiftUp (DdManager *table, int x, int xLow);
static void bddFixTree (DdManager *table, MtrNode *treenode);
static int ddUpdateMtrTree (DdManager *table, MtrNode *treenode, int *perm, int *invperm);
static int ddCheckPermuation (DdManager *table, MtrNode *treenode, int *perm, int *invperm);

/** \endcond */


/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/


/**
  @brief Main dynamic reordering routine.主要动态重排序例程。

  @details Calls one of the possible reordering procedures:调用其中一个可能的重新排序程序：
  <ul>
  <li>Swapping
  <li>Sifting
  <li>Symmetric Sifting
  <li>Group Sifting
  <li>Window Permutation
  <li>Simulated Annealing
  <li>Genetic Algorithm
  <li>Dynamic Programming (exact)
  </ul>
  For sifting, symmetric sifting, group sifting, and window
  permutation it is possible to request reordering to convergence.<p>
  The core of all methods is the reordering procedure
  cuddSwapInPlace() which swaps two adjacent variables and is based
  on Rudell's paper. 
  对于筛分、对称筛分、分组筛分和窗口排列，可以要求重新排序以达到收敛。
  所有方法的核心是重新排序过程 cuddSwapInPlace() 是所有方法的核心，它交换了两个相邻的变量,基于 Rudell 的论文。

  @return 1 in case of success; 0 otherwise. In the case of symmetric
  sifting (with and without convergence) returns 1 plus the number of
  symmetric variables, in case of success. 
  成功时为 1，否则为 0。在对称  筛选（收敛或不收敛）成功时，返回 1 加对称变量的个数。

  @sideeffect Changes the variable order for all diagrams and clears
  the cache.

*/
int
Cudd_ReduceHeap(
  DdManager * table /**< %DD manager */,
  Cudd_ReorderingType heuristic /**< method used for reordering */,
  int  minsize /**< bound below which no reordering occurs  在此界限以下不发生重新排序*/)
{
    DdHook *hook;
    int	result;
    unsigned int nextDyn;
#ifdef DD_STATS
    unsigned int initialSize;
    unsigned int finalSize;
#endif
    unsigned long localTime;

	//1.预检查和初始化
    /* Don't reorder if there are too many dead nodes. */
	// table->keys: number of BDD nodes
	// table->dead: total number of dead BDD nodes
    if (table->keys - table->dead < (unsigned) minsize)		// 如果BDD的节点数小于这个值,则不需要重排
	return(1);

    if (heuristic == CUDD_REORDER_SAME) {
	heuristic = table->autoMethod;
    }
    if (heuristic == CUDD_REORDER_NONE) {
	return(1);
    }

    /* This call to Cudd_ReduceHeap does initiate reordering. 
	对 Cudd_ReduceHeap 的调用确实启动了重新排序。
	Therefore** we count it.
    */
    table->reorderings++;

    localTime = util_cpu_time();

	//2.执行预重排钩子函数
    /* Run the hook functions. */
    hook = table->preReorderingHook;		// 在cuddAPI.c的3615行的Cudd_StdPreReordHook()函数
    while (hook != NULL) {
	int res = (hook->f)(table, "BDD", (void *)heuristic);
	if (res == 0) return(0);
	hook = hook->next;
    }

	//3.重排序的预处理
    if (!ddReorderPreprocess(table)) return(0);	/* 重排序之前的预处理 在cuddReorder.c的1784行 主要作用是清除缓存，重排序后之前的缓存没意义*/
    table->ddTotalNumberSwapping = 0;

    if (table->keys > table->peakLiveNodes) {
	table->peakLiveNodes = table->keys;
    }
#ifdef DD_STATS
    initialSize = (int) (table->keys - table->isolated);
    table->totalNISwaps = 0;

    switch(heuristic) {
    case CUDD_REORDER_RANDOM:
    case CUDD_REORDER_RANDOM_PIVOT:
	(void) fprintf(table->out,"#:I_RANDOM  ");
	break;
    case CUDD_REORDER_SIFT:
    case CUDD_REORDER_SIFT_CONVERGE:
    case CUDD_REORDER_SYMM_SIFT:
    case CUDD_REORDER_SYMM_SIFT_CONV:
    case CUDD_REORDER_GROUP_SIFT:
    case CUDD_REORDER_GROUP_SIFT_CONV:
	(void) fprintf(table->out,"#:I_SIFTING ");
	break;
    case CUDD_REORDER_WINDOW2:
    case CUDD_REORDER_WINDOW3:
    case CUDD_REORDER_WINDOW4:
    case CUDD_REORDER_WINDOW2_CONV:
    case CUDD_REORDER_WINDOW3_CONV:
    case CUDD_REORDER_WINDOW4_CONV:
	(void) fprintf(table->out,"#:I_WINDOW  ");
	break;
    case CUDD_REORDER_ANNEALING:
	(void) fprintf(table->out,"#:I_ANNEAL  ");
	break;
    case CUDD_REORDER_GENETIC:
	(void) fprintf(table->out,"#:I_GENETIC ");
	break;
    case CUDD_REORDER_LINEAR:
    case CUDD_REORDER_LINEAR_CONVERGE:
	(void) fprintf(table->out,"#:I_LINSIFT ");
	break;
    case CUDD_REORDER_EXACT:
	(void) fprintf(table->out,"#:I_EXACT   ");
	break;
    default:
	return(0);
    }
    (void) fprintf(table->out,"%8d: initial size",initialSize);
#endif

	//4.重排序的执行过程
    /* See if we should use alternate threshold for maximum growth.
	看看我们是否应该使用另一种最大增长阈值。 */
    if (table->reordCycle && table->reorderings % table->reordCycle == 0) {
	double saveGrowth = table->maxGrowth;
	table->maxGrowth = table->maxGrowthAlt;
	result = cuddTreeSifting(table,heuristic);			//执行重排序操作	在cuddGroup.c的205行 
	table->maxGrowth = saveGrowth;
    } else {
	result = cuddTreeSifting(table,heuristic);
    }

#ifdef DD_STATS
    (void) fprintf(table->out,"\n");
    finalSize = (int) (table->keys - table->isolated);
    (void) fprintf(table->out,"#:F_REORDER %8d: final size\n",finalSize);
    (void) fprintf(table->out,"#:T_REORDER %8g: total time (sec)\n",
		   ((double)(util_cpu_time() - localTime)/1000.0));
    (void) fprintf(table->out,"#:N_REORDER %8d: total swaps\n",
		   table->ddTotalNumberSwapping);
    (void) fprintf(table->out,"#:M_REORDER %8d: NI swaps\n",
                   table->totalNISwaps);
#endif

    if (result == 0)
	return(0);
	
	//5.执行重排序后的钩子函数
    if (!ddReorderPostprocess(table))		//执行后重排序钩子函数  在cuddReorder.c的1784行后面
	return(0);

    if (table->realign) {
	if (!cuddZddAlignToBdd(table))
	    return(0);
    }

	//6.更新下一次阈值
    nextDyn = (table->keys - table->constants.keys + 1) *
	      DD_DYN_RATIO + table->constants.keys;		/* 更新下一次重排序的dd大小阈值 */
    if (table->reorderings < 20 || nextDyn > table->nextDyn)
	table->nextDyn = nextDyn;
    else
	table->nextDyn += 20;
    if (table->randomizeOrder != 0) {
        table->nextDyn += Cudd_Random(table) & table->randomizeOrder;
    }
    table->reordered = 1;

    /* Run hook functions. */
    hook = table->postReorderingHook;
    while (hook != NULL) {
	int res = (hook->f)(table, "BDD", (void *)(ptruint)localTime);
	if (res == 0) return(0);
	hook = hook->next;
    }

    /* Update cumulative reordering time. */
    table->reordTime += util_cpu_time() - localTime;

    return(result);

} /* end of Cudd_ReduceHeap */


/**
  @brief Reorders variables according to given permutation.
  根据给定的排列方式重新排列变量。

  @details The i-th entry of the permutation array contains the index
  of the variable that should be brought to the i-th level.  The size
  of the array should be equal or greater to the number of variables
  currently in use.
  置换数组的第 i 个条目包含应被置换到第 i 层的变量的索引。
  数组的大小应等于或大于当前使用的变量数。

  @return 1 in case of success; 0 otherwise.

  @sideeffect Changes the variable order for all diagrams and clears
  the cache.

  @see Cudd_ReduceHeap

*/
int
Cudd_ShuffleHeap(
  DdManager * table /**< %DD manager */,
  int * permutation /**< required variable permutation */)
{

    int	result;
    int i;
    int identity = 1;
    int *perm;

    /* Don't waste time in case of identity permutation. */
    for (i = 0; i < table->size; i++) {
	if (permutation[i] != table->invperm[i]) {
	    identity = 0;
	    break;
	}
    }
    if (identity == 1) {
	return(1);
    }
    if (!ddReorderPreprocess(table)) return(0);
    if (table->keys > table->peakLiveNodes) {
	table->peakLiveNodes = table->keys;
    }

    perm = ALLOC(int, table->size);
    for (i = 0; i < table->size; i++)
	perm[permutation[i]] = i;
    if (!ddCheckPermuation(table,table->tree,perm,permutation)) {
	FREE(perm);
	return(0);
    }
    if (!ddUpdateMtrTree(table,table->tree,perm,permutation)) {
	FREE(perm);
	return(0);
    }
    FREE(perm);

    result = ddShuffle(table,permutation);

    if (!ddReorderPostprocess(table)) return(0);

    return(result);

} /* end of Cudd_ShuffleHeap */


/*---------------------------------------------------------------------------*/
/* Definition of internal functions                                          */
/*---------------------------------------------------------------------------*/


/**
  @brief Dynamically allocates a Node.

  @details This procedure is similar to cuddAllocNode in Cudd_Table.c,
  but it does not attempt garbage collection, because during
  reordering there are no dead nodes.

  @return a pointer to a new node if successful; NULL is memory is
  full.

  @sideeffect None

  @see cuddAllocNode

*/
DdNode *
cuddDynamicAllocNode(
  DdManager * table)
{
    int     i;
    DdNodePtr *mem;
    DdNode *list, *node;
    extern DD_OOMFP MMoutOfMemory;
    DD_OOMFP saveHandler;

    if (table->nextFree == NULL) {        /* free list is empty */
	/* Try to allocate a new block. */
	saveHandler = MMoutOfMemory;
	MMoutOfMemory = table->outOfMemCallback;
	mem = (DdNodePtr *) ALLOC(DdNode, DD_MEM_CHUNK + 1);
	MMoutOfMemory = saveHandler;
	if (mem == NULL && table->stash != NULL) {
	    FREE(table->stash);
	    table->stash = NULL;
	    /* Inhibit resizing of tables. */
	    table->maxCacheHard = table->cacheSlots - 1;
	    table->cacheSlack = - (int) (table->cacheSlots + 1);
	    for (i = 0; i < table->size; i++) {
		table->subtables[i].maxKeys <<= 2;
	    }
	    mem = (DdNodePtr *) ALLOC(DdNode,DD_MEM_CHUNK + 1);
	}
	if (mem == NULL) {
	    /* Out of luck. Call the default handler to do
	    ** whatever it specifies for a failed malloc.  If this
	    ** handler returns, then set error code, print
	    ** warning, and return. */
	    (*MMoutOfMemory)(sizeof(DdNode)*(DD_MEM_CHUNK + 1));
	    table->errorCode = CUDD_MEMORY_OUT;
#ifdef DD_VERBOSE
	    (void) fprintf(table->err,
			   "cuddDynamicAllocNode: out of memory");
	    (void) fprintf(table->err,"Memory in use = %lu\n",
			   table->memused);
#endif
	    return(NULL);
	} else {	/* successful allocation; slice memory */
	    size_t offset;
	    table->memused += (DD_MEM_CHUNK + 1) * sizeof(DdNode);
	    mem[0] = (DdNode *) table->memoryList;
	    table->memoryList = mem;

	    /* Here we rely on the fact that the size of a DdNode is a
	    ** power of 2 and a multiple of the size of a pointer.
	    ** If we align one node, all the others will be aligned
	    ** as well. */
	    offset = (size_t) mem & (sizeof(DdNode) - 1);
	    mem += (sizeof(DdNode) - offset) / sizeof(DdNodePtr);
#ifdef DD_DEBUG
	    assert(((size_t) mem & (sizeof(DdNode) - 1)) == 0);
#endif
	    list = (DdNode *) mem;

	    i = 1;
	    do {
		list[i - 1].ref = 0;
		list[i - 1].next = &list[i];
	    } while (++i < DD_MEM_CHUNK);

	    list[DD_MEM_CHUNK-1].ref = 0;
	    list[DD_MEM_CHUNK - 1].next = NULL;

	    table->nextFree = &list[0];
	}
    } /* if free list empty */

    node = table->nextFree;
    table->nextFree = node->next;
    return (node);

} /* end of cuddDynamicAllocNode */


/**
  @brief Implementation of Rudell's sifting algorithm.鲁德尔筛选算法的实现。

  @details Assumes that no dead nodes are present.
    <ol>
    <li> Order all the variables according to the number of entries
    in each unique table. 			根据每个唯一表格中的条目数给所有变量排序。
    <li> Sift the variable up and down, remembering each time the
    total size of the %DD heap.		上下筛选变量，每次都要记住 %DD 堆的总大小。
    <li> Select the best permutation. 选择最佳排序
    <li> Repeat 3 and 4 for all variables.
    </ol>

  @return 1 if successful; 0 otherwise.

  @sideeffect None

*/
int
cuddSifting(
  DdManager * table,
  int  lower,
  int  upper)
{
    int	i;
    IndexKey *var;
    int	size;
    int	x;
    int	result;
#ifdef DD_STATS
    int	previousSize;
#endif
	//1.  初始化
    size = table->size;			//唯一子表数
    /* Find order in which to sift variables. 查找筛选变量的顺序。*/
    var = ALLOC(IndexKey,size);
    if (var == NULL) {
	table->errorCode = CUDD_MEMORY_OUT;
	goto cuddSiftingOutOfMem;
    }

	//2. 记录变量的索引和节点数
    for (i = 0; i < size; i++) {
	x = table->perm[i];			//输入索引得到层级
	var[i].index = i;
	var[i].keys = table->subtables[x].keys;				//第几层就是第几个变量对应的唯一子表
    }
	//3. 排序变量
    util_qsort(var,size,sizeof(IndexKey),ddUniqueCompare);		//按节点数对 var 数组从大到小排序，优先处理节点多的变量。

    /*4. 主筛选循环 Now sift. */
    for (i = 0; i < ddMin(table->siftMaxVar,size); i++) {
		if (table->ddTotalNumberSwapping >= table->siftMaxSwap)
			break;//交换次数超过 siftMaxSwap，停止筛选。
			if (util_cpu_time() - table->startTime + table->reordTime
				> table->timeLimit) {
				table->autoDyn = 0; /* prevent further reordering */
				break;
			}//运行时间超过 timeLimit，禁用自动重排序
			if (table->terminationCallback != NULL &&
				table->terminationCallback(table->tcbArg)) {
				table->autoDyn = 0; /* prevent further reordering */
				break;
			}//自定义终止回调函数触发，停止筛选
		x = table->perm[var[i].index];			//一层一层的进行sifting筛选；输入索引返回层级；x是第一层慢慢往下循环
		//跳过无法筛选的变量
		if (x < lower || x > upper || table->subtables[x].bindVar == 1)
			continue;
#ifdef DD_STATS
	previousSize = (int) (table->keys - table->isolated);
#endif
		result = ddSiftingAux(table, x, lower, upper);
		if (!result) goto cuddSiftingOutOfMem;
#ifdef DD_STATS
	if (table->keys < (unsigned) previousSize + table->isolated) {
	    (void) fprintf(table->out,"-");
	} else if (table->keys > (unsigned) previousSize + table->isolated) {
	    (void) fprintf(table->out,"+");	/* should never happen */
	    (void) fprintf(table->err,"\nSize increased from %d to %u while sifting variable %d\n", previousSize, table->keys - table->isolated, var[i].index);
	} else {
	    (void) fprintf(table->out,"=");
	}
	fflush(table->out);
#endif
    }

    FREE(var);

    return(1);

cuddSiftingOutOfMem:

    if (var != NULL) FREE(var);

    return(0);

} /* end of cuddSifting */


/**
  @brief Reorders variables by a sequence of (non-adjacent) swaps.

  @details Implementation of Plessier's algorithm that reorders
  variables by a sequence of (non-adjacent) swaps.
    <ol>
    <li> Select two variables (RANDOM or HEURISTIC).
    <li> Permute these variables.
    <li> If the nodes have decreased accept the permutation.
    <li> Otherwise reconstruct the original heap.
    <li> Loop.
    </ol>

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
int
cuddSwapping(
  DdManager * table,
  int lower,
  int upper,
  Cudd_ReorderingType heuristic)
{
    int	i, j;
    int	max, keys;
    int	nvars;
    int	x, y;
    int	iterate;
    int previousSize;
    Move *moves, *move;
    int	pivot = 0;
    int	modulo;
    int result;

#ifdef DD_DEBUG
    /* Sanity check */
    assert(lower >= 0 && upper < table->size && lower <= upper);
#endif

    nvars = upper - lower + 1;
    iterate = nvars;

    for (i = 0; i < iterate; i++) {
	if (table->ddTotalNumberSwapping >= table->siftMaxSwap)
	    break;
	if (heuristic == CUDD_REORDER_RANDOM_PIVOT) {
	    max = -1;
	    for (j = lower; j <= upper; j++) {
		if ((keys = table->subtables[j].keys) > max) {
		    max = keys;
		    pivot = j;
		}
	    }

	    modulo = upper - pivot;
	    if (modulo == 0) {
		y = pivot;
	    } else{
		y = pivot + 1 + ((int) Cudd_Random(table) % modulo);
	    }

	    modulo = pivot - lower - 1;
	    if (modulo < 1) {
		x = lower;
	    } else{
		do {
		    x = (int) Cudd_Random(table) % modulo;
		} while (x == y);
	    }
	} else {
	    x = ((int) Cudd_Random(table) % nvars) + lower;
	    do {
		y = ((int) Cudd_Random(table) % nvars) + lower;
	    } while (x == y);
	}
	previousSize = (int) (table->keys - table->isolated);
	moves = ddSwapAny(table,x,y);
	if (moves == NULL) goto cuddSwappingOutOfMem;
	result = ddSiftingBackward(table,previousSize,moves);
	if (!result) goto cuddSwappingOutOfMem;
	while (moves != NULL) {
	    move = moves->next;
	    cuddDeallocMove(table, moves);
	    moves = move;
	}
#ifdef DD_STATS
	if (table->keys < (unsigned) previousSize + table->isolated) {
	    (void) fprintf(table->out,"-");
	} else if (table->keys > (unsigned) previousSize + table->isolated) {
	    (void) fprintf(table->out,"+");	/* should never happen */
	} else {
	    (void) fprintf(table->out,"=");
	}
	fflush(table->out);
#endif
#if 0
	(void) fprintf(table->out,"#:t_SWAPPING %8d: tmp size\n",
		       table->keys - table->isolated);
#endif
    }

    return(1);

cuddSwappingOutOfMem:
    while (moves != NULL) {
	move = moves->next;
	cuddDeallocMove(table, moves);
	moves = move;
    }

    return(0);

} /* end of cuddSwapping */


/**
  @brief Finds the next subtable with a larger index.

  @return the index.

  @sideeffect None

  @see cuddNextLow

*/
int
cuddNextHigh(
  DdManager * table,
  int  x)
{
    (void) table; /* avoid warning */
    return(x+1);

} /* end of cuddNextHigh */


/**
  @brief Finds the next subtable with a smaller index.

  @return the index.

  @sideeffect None

  @see cuddNextHigh

*/
int
cuddNextLow(
  DdManager * table,
  int  x)
{
    (void) table; /* avoid warning */
    return(x-1);

} /* end of cuddNextLow */


/**
  @brief Swaps two adjacent variables.

  @details It assumes that no dead nodes are present on entry to this
  procedure.  The procedure then guarantees that no dead nodes will be
  present when it terminates.  cuddSwapInPlace assumes that x &lt; y. 它假定进入此存储过程时没有死节点。 

  @return the number of keys in the table if successful; 0 otherwise.

  @sideeffect None

*/
int
cuddSwapInPlace(
  DdManager * table,
  int  x,
  int  y)
{
    DdNodePtr *xlist, *ylist;
    int    xindex, yindex;
    int    xslots, yslots;
    int    xshift, yshift;
    int    oldxkeys, oldykeys;
    int    newxkeys, newykeys;
    int    comple, newcomplement;
    int    i;
    Cudd_VariableType varType;
    Cudd_LazyGroupType groupType;
    int    posn;
    int    isolated;
    DdNode *f,*f0,*f1,*f01,*f00,*f11,*f10,*newf1,*newf0;
    DdNode *g,*next;
    DdNodePtr *previousP;
    DdNode *tmp;
    DdNode *sentinel = &(table->sentinel);
    extern DD_OOMFP MMoutOfMemory;
    DD_OOMFP saveHandler;

#ifdef DD_DEBUG
    int    count,idcheck;
#endif

#ifdef DD_DEBUG
    assert(x < y);
    assert(cuddNextHigh(table,x) == y);
    assert(table->subtables[x].keys != 0);
    assert(table->subtables[y].keys != 0);
    assert(table->subtables[x].dead == 0);
    assert(table->subtables[y].dead == 0);
#endif

    table->ddTotalNumberSwapping++;

    /* Get parameters of x subtable. 		获取x唯一子表参数*/
    xindex = table->invperm[x];
    xlist = table->subtables[x].nodelist;
    oldxkeys = table->subtables[x].keys;
    xslots = table->subtables[x].slots;
    xshift = table->subtables[x].shift;

    /* Get parameters of y subtable.		获取y唯一子表参数 */
    yindex = table->invperm[y];
    ylist = table->subtables[y].nodelist;
    oldykeys = table->subtables[y].keys;
    yslots = table->subtables[y].slots;
    yshift = table->subtables[y].shift;

    if (!cuddTestInteract(table,xindex,yindex)) {		//检查 x 和 y 是否有交互
#ifdef DD_STATS
	table->totalNISwaps++;
#endif
	newxkeys = oldxkeys;
	newykeys = oldykeys;
    } else {
	newxkeys = 0;
	newykeys = oldykeys;

	/* Check whether the two projection functions involved in this	 	检查参与交换的两个投影函数是否是孤立的。
	** swap are isolated. At the end, we'll be able to tell how many	最后，我们只需再次检查这两个函数，就能知道有多少个孤立的投影函数。
	** isolated projection functions are there by checking only these	这样做是为了从节点计数中剔除孤立的投影函数。
	** two functions again. This is done to eliminate the isolated
	** projection functions from the node count.
	*/
	isolated = - ((table->vars[xindex]->ref == 1) +
		     (table->vars[yindex]->ref == 1));

	/* The nodes in the x layer that do not depend on
	** y will stay there; the others are put in a chain.	x 层中不依赖于 y 的节点将保留在 x 层；其他节点将放入一个链中。
	** The chain is handled as a LIFO; g points to the beginning.	链的处理方式是后进先出；g 指向起点。
	
	代码的核心逻辑是调整 x 层哈希表，将依赖 y 的节点迁移，并根据节点密度决定是否调整 x 层的哈希表大小;
	迁移的节点存入 g 链表，若需要调整x层哈希表，则属于 x 层的节点存入 h 链表，再重新插入新分配的哈希表*/

	//1. 遍历 x 层的哈希表，将部分节点移到 y 层
	g = NULL;				//初始化链表g
	if ((oldxkeys >= xslots || (unsigned) xslots == table->initSlots) &&
	    oldxkeys <= DD_MAX_SUBTABLE_DENSITY * xslots) {
	    for (i = 0; i < xslots; i++) {		// 遍历 x 层的所有哈希槽
			previousP = &(xlist[i]);
			f = *previousP;						// 取出该槽的第一个节点
			while (f != sentinel) {				// 遍历槽内所有节点
				next = f->next;
				f1 = cuddT(f); f0 = cuddE(f);
				if (f1->index != (DdHalfWord) yindex &&
				Cudd_Regular(f0)->index != (DdHalfWord) yindex) {		
				/* stays  如果 T 和 E 分支都不依赖于 y，则该节点仍然属于 x 层  这里要注意是左右子树都都都依赖于y层*/
				newxkeys++;
				*previousP = f;
				previousP = &(f->next);
				} else {						// 否则，x层节点和y层节点有依赖关系，x层节点属于 y 层
				f->index = yindex;
				f->next = g;					//  头插法，加入链表 g（后进先出）只有 f 本身的 T 分支 f1 或 E 分支 f0 依赖 y，才会把 f 放入 g 并改成 yindex
				g = f;							//但 f1 或 f0 本身可能并不在 g 里，它们的 index 可能还是 x（原始 x 变量）
				}
				f = next;						// 开始就将xlist里面下一个节点存到next里面，以便后续移动到下一个节点
			} /* while there are elements in the collision chain 当该变量在冲突链中*/
			*previousP = sentinel;
	    } /* for each slot of the x subtable for循环遍历 x 子表格的每个插槽——也就是该层里面所有存在的节点*/
	} 

	//2. 需要调整 x 层哈希表大小
	else {		/* resize xlist 		如果 x 层的哈希表不适合当前的节点数量，需要重新分配哈希表。*/
	    DdNode *h = NULL;
	    DdNodePtr *newxlist;
	    unsigned int newxslots;
	    int newxshift;
	    /* Empty current xlist. Nodes that stay go to list h;遍历 x 层，把需要保留的节点放入 h 链表，需要移动的放入 g
	    ** nodes that move go to list g. */
	    for (i = 0; i < xslots; i++) {
		f = xlist[i];
		while (f != sentinel) {
		    next = f->next;
		    f1 = cuddT(f); f0 = cuddE(f);
		    if (f1->index != (DdHalfWord) yindex &&
			Cudd_Regular(f0)->index != (DdHalfWord) yindex) {
			/* stays 						 保留的节点加入 h 链表*/
			f->next = h;		
			h = f;
			newxkeys++;
		    } else {
			f->index = yindex;
			f->next = g;					// 迁移到 g链表
			g = f;
		    }
		    f = next;
		} /* while there are elements in the collision chain */
	    } /* for each slot of the x subtable */

	    /* 3. 计算新的哈希表大小  Decide size of new subtable. 决定新子表格的大小。*/
	    newxshift = xshift;
	    newxslots = xslots;
	    while ((unsigned) oldxkeys > DD_MAX_SUBTABLE_DENSITY * newxslots) {//如果 oldxkeys 超过最大密度，则 扩大 哈希表（newxslots <<= 1）
		newxshift--;
		newxslots <<= 1;
	    }
	    while ((unsigned) oldxkeys < newxslots &&
		   newxslots > table->initSlots) {//如果 oldxkeys 太小，则 缩小 哈希表（newxslots >>= 1）
		newxshift++;
		newxslots >>= 1;
	    }

	    /* 4. 重新分配新的哈希表 Try to allocate new table. Be ready to back off. 尝试分配新表。随时准备回溯。*/
	    saveHandler = MMoutOfMemory;
	    MMoutOfMemory = table->outOfMemCallback;
	    newxlist = ALLOC(DdNodePtr, newxslots);
	    MMoutOfMemory = saveHandler;
	    if (newxlist == NULL) {
		(void) fprintf(table->err, "Unable to resize subtable %d for lack of memory\n", i);
	    } else {
		table->slots += ((int) newxslots - xslots);
		table->minDead = (unsigned)
		    (table->gcFrac * (double) table->slots);
		table->cacheSlack = (int)
		    ddMin(table->maxCacheHard, DD_MAX_CACHE_TO_SLOTS_RATIO
			  * table->slots) - 2 * (int) table->cacheSlots;
		table->memused +=
		    ((int) newxslots - xslots) * sizeof(DdNodePtr);
		FREE(xlist);
		xslots =  newxslots;
		xshift = newxshift;
		xlist = newxlist;
	    }

	    /*5.重新插入 h 链表中的节点 Initialize new subtable.*/
	    for (i = 0; i < xslots; i++) {
		xlist[i] = sentinel;
	    }
	    /* Move nodes that were parked in list h to their new home. 将停放在列表 h 中的节点移动到新的位置。*/
	    f = h;
	    while (f != NULL) {
		next = f->next;
		f1 = cuddT(f);
		f0 = cuddE(f);
		/* Check xlist for pair (f11,f01). 检查 x 列表中的配对 (f11,f01)*/
		posn = ddHash(f1, f0, xshift);
		/* For each element tmp in collision list xlist[posn]. 对于碰撞列表 xlist[posn] 中的每个元素 tmp。*/
		previousP = &(xlist[posn]);
		tmp = *previousP;
		while (f1 < cuddT(tmp)) {
		    previousP = &(tmp->next);
		    tmp = *previousP;
		}
		while (f1 == cuddT(tmp) && f0 < cuddE(tmp)) {
		    previousP = &(tmp->next);
		    tmp = *previousP;
		}
		f->next = *previousP;
		*previousP = f;
		f = next;
	    }
	}

#ifdef DD_COUNT
	table->swapSteps += oldxkeys - newxkeys;
#endif
	/* Take care of the x nodes that must be re-expressed.			处理必须重新表达的 x 节点。
	** They form a linked list pointed by g. Their index has been	它们构成了一个由 g 指向的链表。已经改为 yindex。
	** already changed to yindex.
	*/
	f = g;
	while (f != NULL) {
	    next = f->next;
	    /* Find f1, f0, f11, f10, f01, f00. */
	    f1 = cuddT(f);
#ifdef DD_DEBUG
	    assert(!(Cudd_IsComplement(f1)));
#endif
	    if ((int) f1->index == yindex) {	//f1->index == yindex：说明 f1 已经被处理过，属于 y 变量相关的部分
		f11 = cuddT(f1); f10 = cuddE(f1);	
	    } else {
		f11 = f10 = f1;						//这里的目的是什么——f1 还未被转换成 yindex，那么它的 T 和 E 分支（即 f11 和 f10）应该保持不变
	    }
#ifdef DD_DEBUG
	    assert(!(Cudd_IsComplement(f11)));
#endif
	    f0 = cuddE(f);
	    comple = Cudd_IsComplement(f0);
	    f0 = Cudd_Regular(f0);
	    if ((int) f0->index == yindex) {
		f01 = cuddT(f0); f00 = cuddE(f0);
	    } else {
		f01 = f00 = f0;
	    }
	    if (comple) {
		f01 = Cudd_Not(f01);				
		f00 = Cudd_Not(f00);
	    }
	    /* Decrease ref count of f1. */
	    cuddSatDec(f1->ref);
	    /* Create the new T child. */
	    if (f11 == f01) {					
		newf1 = f11;						//说明 T 分支和 E 分支相同，那就不需要创建新的 BDD 节点，直接复用 f11
		cuddSatInc(newf1->ref);
	    } else {
		/* Check xlist for triple (xindex,f11,f01). */
		posn = ddHash(f11, f01, xshift);	//posn是x层唯一子表的哈希槽位置
		/* For each element newf1 in collision list xlist[posn]. */
		previousP = &(xlist[posn]);			//previousP是指向该哈希槽冲突链的地址
		newf1 = *previousP;
		while (f11 < cuddT(newf1)) {
		    previousP = &(newf1->next);
		    newf1 = *previousP;
		}
		while (f11 == cuddT(newf1) && f01 < cuddE(newf1)) {
		    previousP = &(newf1->next);
		    newf1 = *previousP;
		}
		if (cuddT(newf1) == f11 && cuddE(newf1) == f01) {
		    cuddSatInc(newf1->ref);
		} else { /* no match */
		    newf1 = cuddDynamicAllocNode(table);
		    if (newf1 == NULL)
			goto cuddSwapOutOfMem;
		    newf1->index = xindex; newf1->ref = 1;
		    cuddT(newf1) = f11;
		    cuddE(newf1) = f01;
		    /* Insert newf1 in the collision list xlist[posn];
		    ** increase the ref counts of f11 and f01.
		    */
		    newxkeys++;
		    newf1->next = *previousP;
		    *previousP = newf1;
		    cuddSatInc(f11->ref);
		    tmp = Cudd_Regular(f01);
		    cuddSatInc(tmp->ref);
		}
	    }
	    cuddT(f) = newf1;
#ifdef DD_DEBUG
	    assert(!(Cudd_IsComplement(newf1)));
#endif

	    /* Do the same for f0, keeping complement dots into account. */
	    /* Decrease ref count of f0. */
	    tmp = Cudd_Regular(f0);
	    cuddSatDec(tmp->ref);
	    /* Create the new E child. */
	    if (f10 == f00) {
		newf0 = f00;
		tmp = Cudd_Regular(newf0);
		cuddSatInc(tmp->ref);
	    } else {
		/* make sure f10 is regular */
		newcomplement = Cudd_IsComplement(f10);
		if (newcomplement) {
		    f10 = Cudd_Not(f10);
		    f00 = Cudd_Not(f00);
		}
		/* Check xlist for triple (xindex,f10,f00). */
		posn = ddHash(f10, f00, xshift);
		/* For each element newf0 in collision list xlist[posn]. */
		previousP = &(xlist[posn]);
		newf0 = *previousP;
		while (f10 < cuddT(newf0)) {
		    previousP = &(newf0->next);
		    newf0 = *previousP;
		}
		while (f10 == cuddT(newf0) && f00 < cuddE(newf0)) {
		    previousP = &(newf0->next);
		    newf0 = *previousP;
		}
		if (cuddT(newf0) == f10 && cuddE(newf0) == f00) {
		    cuddSatInc(newf0->ref);
		} else { /* no match */
		    newf0 = cuddDynamicAllocNode(table);
		    if (newf0 == NULL)
			goto cuddSwapOutOfMem;
		    newf0->index = xindex; newf0->ref = 1;
		    cuddT(newf0) = f10;
		    cuddE(newf0) = f00;
		    /* Insert newf0 in the collision list xlist[posn];
		    ** increase the ref counts of f10 and f00.
		    */
		    newxkeys++;
		    newf0->next = *previousP;
		    *previousP = newf0;
		    cuddSatInc(f10->ref);
		    tmp = Cudd_Regular(f00);
		    cuddSatInc(tmp->ref);
		}
		if (newcomplement) {
		    newf0 = Cudd_Not(newf0);
		}
	    }
	    cuddE(f) = newf0;

	    /* Insert the modified f in ylist.						将修改后的 f 插入 ylist。
	    ** The modified f does not already exists in ylist.		修改后的 f 不存在于 ylist 中。
	    ** (Because of the uniqueness of the cofactors.)		因为辅因子是唯一的
	    */
	    posn = ddHash(newf1, newf0, yshift);
	    newykeys++;
	    previousP = &(ylist[posn]);
	    tmp = *previousP;
	    while (newf1 < cuddT(tmp)) {
		previousP = &(tmp->next);
		tmp = *previousP;
	    }
	    while (newf1 == cuddT(tmp) && newf0 < cuddE(tmp)) {
		previousP = &(tmp->next);
		tmp = *previousP;
	    }
	    f->next = *previousP;
	    *previousP = f;
	    f = next;
	} /* while f != NULL */

	/* GC the y layer. */

	/* For each node f in ylist. */
	for (i = 0; i < yslots; i++) {
	    previousP = &(ylist[i]);
	    f = *previousP;
	    while (f != sentinel) {
		next = f->next;
		if (f->ref == 0) {
		    tmp = cuddT(f);
		    cuddSatDec(tmp->ref);
		    tmp = Cudd_Regular(cuddE(f));
		    cuddSatDec(tmp->ref);
		    cuddDeallocNode(table,f);
		    newykeys--;
		} else {
		    *previousP = f;
		    previousP = &(f->next);
		}
		f = next;
	    } /* while f */
	    *previousP = sentinel;
	} /* for i */

#ifdef DD_DEBUG
#if 0
	(void) fprintf(table->out,"Swapping %d and %d\n",x,y);
#endif
	count = 0;
	idcheck = 0;
	for (i = 0; i < yslots; i++) {
	    f = ylist[i];
	    while (f != sentinel) {
		count++;
		if (f->index != (DdHalfWord) yindex)
		    idcheck++;
		f = f->next;
	    }
	}
	if (count != newykeys) {
	    (void) fprintf(table->out,
			   "Error in finding newykeys\toldykeys = %d\tnewykeys = %d\tactual = %d\n",
			   oldykeys,newykeys,count);
	}
	if (idcheck != 0)
	    (void) fprintf(table->out,
			   "Error in id's of ylist\twrong id's = %d\n",
			   idcheck);
	count = 0;
	idcheck = 0;
	for (i = 0; i < xslots; i++) {
	    f = xlist[i];
	    while (f != sentinel) {
		count++;
		if (f->index != (DdHalfWord) xindex)
		    idcheck++;
		f = f->next;
	    }
	}
	if (count != newxkeys) {
	    (void) fprintf(table->out,
			   "Error in finding newxkeys\toldxkeys = %d \tnewxkeys = %d \tactual = %d\n",
			   oldxkeys,newxkeys,count);
	}
	if (idcheck != 0)
	    (void) fprintf(table->out,
			   "Error in id's of xlist\twrong id's = %d\n",
			   idcheck);
#endif

	isolated += (table->vars[xindex]->ref == 1) +
		    (table->vars[yindex]->ref == 1);
	table->isolated += (unsigned int) isolated;
    }

    /* Set the appropriate fields in table. 在表格中设置相应字段*/
    table->subtables[x].nodelist = ylist;
    table->subtables[x].slots = yslots;
    table->subtables[x].shift = yshift;
    table->subtables[x].keys = newykeys;
    table->subtables[x].maxKeys = yslots * DD_MAX_SUBTABLE_DENSITY;
    i = table->subtables[x].bindVar;
    table->subtables[x].bindVar = table->subtables[y].bindVar;
    table->subtables[y].bindVar = i;
    /* Adjust fields for lazy sifting. */
    varType = table->subtables[x].varType;
    table->subtables[x].varType = table->subtables[y].varType;
    table->subtables[y].varType = varType;
    i = table->subtables[x].pairIndex;
    table->subtables[x].pairIndex = table->subtables[y].pairIndex;
    table->subtables[y].pairIndex = i;
    i = table->subtables[x].varHandled;
    table->subtables[x].varHandled = table->subtables[y].varHandled;
    table->subtables[y].varHandled = i;
    groupType = table->subtables[x].varToBeGrouped;
    table->subtables[x].varToBeGrouped = table->subtables[y].varToBeGrouped;
    table->subtables[y].varToBeGrouped = groupType;

    table->subtables[y].nodelist = xlist;
    table->subtables[y].slots = xslots;
    table->subtables[y].shift = xshift;
    table->subtables[y].keys = newxkeys;
    table->subtables[y].maxKeys = xslots * DD_MAX_SUBTABLE_DENSITY;

    table->perm[xindex] = y; table->perm[yindex] = x;
    table->invperm[x] = yindex; table->invperm[y] = xindex;

    table->keys += newxkeys + newykeys - oldxkeys - oldykeys;

    return((int)(table->keys - table->isolated));

cuddSwapOutOfMem:
    (void) fprintf(table->err,"Error: cuddSwapInPlace out of memory\n");

    return (0);

} /* end of cuddSwapInPlace */


/**
  @brief Reorders %BDD variables according to the order of the %ZDD
  variables.

  @details This function can be called at the end of %ZDD
  reordering to insure that the order of the %BDD variables is
  consistent with the order of the %ZDD variables. The number of %ZDD
  variables must be a multiple of the number of %BDD variables. Let
  <code>M</code> be the ratio of the two numbers. cuddBddAlignToZdd
  then considers the %ZDD variables from <code>M*i</code> to
  <code>(M+1)*i-1</code> as corresponding to %BDD variable
  <code>i</code>.  This function should be normally called from
  Cudd_zddReduceHeap, which clears the cache.

  @return 1 in case of success; 0 otherwise.

  @sideeffect Changes the %BDD variable order for all diagrams and performs
  garbage collection of the %BDD unique table.

  @see Cudd_ShuffleHeap Cudd_zddReduceHeap

*/
int
cuddBddAlignToZdd(
  DdManager * table /**< %DD manager */)
{
    int *invperm;		/* permutation array */
    int M;			/* ratio of ZDD variables to BDD variables */
    int i;			/* loop index */
    int result;			/* return value */

    /* We assume that a ratio of 0 is OK. */
    if (table->size == 0)
	return(1);

    M = table->sizeZ / table->size;
    /* Check whether the number of ZDD variables is a multiple of the
    ** number of BDD variables.
    */
    if (M * table->size != table->sizeZ)
	return(0);
    /* Create and initialize the inverse permutation array. */
    invperm = ALLOC(int,table->size);
    if (invperm == NULL) {
	table->errorCode = CUDD_MEMORY_OUT;
	return(0);
    }
    for (i = 0; i < table->sizeZ; i += M) {
	int indexZ = table->invpermZ[i];
	int index  = indexZ / M;
	invperm[i / M] = index;
    }
    /* Eliminate dead nodes. Do not scan the cache again, because we
    ** assume that Cudd_zddReduceHeap has already cleared it.
    */
    cuddGarbageCollect(table,0);

    /* Initialize number of isolated projection functions. */
    table->isolated = 0;
    for (i = 0; i < table->size; i++) {
	if (table->vars[i]->ref == 1) table->isolated++;
    }

    /* Initialize the interaction matrix. */
    result = cuddInitInteract(table);
    if (result == 0) return(0);

    result = ddShuffle(table, invperm);
    FREE(invperm);
    /* Free interaction matrix. */
    FREE(table->interact);
    /* Fix the BDD variable group tree. */
    bddFixTree(table,table->tree);
    return(result);

} /* end of cuddBddAlignToZdd */

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/


/**
  @brief Comparison function used by qsort.

  @details Used to order the variables according to the number of keys
  in the subtables.

  @return the difference in number of keys between the two variables
  being compared.

  @sideeffect None

*/
static int
ddUniqueCompare(
  void const * ptrX,
  void const * ptrY)
{
    IndexKey const * pX = (IndexKey const *) ptrX;
    IndexKey const * pY = (IndexKey const *) ptrY;
#if 0
    /* This would make the order stable, which would be good because of
     * it would platform-independent, but instability often produces
     * smaller BDDs.
     */
    if (pY->keys == pX->keys) {
	return(pX->index - pY->index);
    }
#endif
    return(pY->keys - pX->keys);

} /* end of ddUniqueCompare */


/**
  @brief Swaps any two variables.

  @return the set of moves.

  @sideeffect None

*/
static Move *
ddSwapAny(
  DdManager * table,
  int  x,
  int  y)
{
    Move	*move, *moves;
    int		xRef,yRef;
    int		xNext,yNext;
    int		size;
    int		limitSize;
    int		tmp;

    if (x >y) {
	tmp = x; x = y; y = tmp;
    }

    xRef = x; yRef = y;

    xNext = cuddNextHigh(table,x);
    yNext = cuddNextLow(table,y);
    moves = NULL;
    limitSize = (int) (table->keys - table->isolated);

    for (;;) {
	if ( xNext == yNext) {
	    size = cuddSwapInPlace(table,x,xNext);
	    if (size == 0) goto ddSwapAnyOutOfMem;
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddSwapAnyOutOfMem;
	    move->x = x;
	    move->y = xNext;
	    move->size = size;
	    move->next = moves;
	    moves = move;

	    size = cuddSwapInPlace(table,yNext,y);
	    if (size == 0) goto ddSwapAnyOutOfMem;
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddSwapAnyOutOfMem;
	    move->x = yNext;
	    move->y = y;
	    move->size = size;
	    move->next = moves;
	    moves = move;

	    size = cuddSwapInPlace(table,x,xNext);
	    if (size == 0) goto ddSwapAnyOutOfMem;
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddSwapAnyOutOfMem;
	    move->x = x;
	    move->y = xNext;
	    move->size = size;
	    move->next = moves;
	    moves = move;

	    tmp = x; x = y; y = tmp;

	} else if (x == yNext) {

	    size = cuddSwapInPlace(table,x,xNext);
	    if (size == 0) goto ddSwapAnyOutOfMem;
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddSwapAnyOutOfMem;
	    move->x = x;
	    move->y = xNext;
	    move->size = size;
	    move->next = moves;
	    moves = move;

	    tmp = x; x = y; y = tmp;

	} else {
	    size = cuddSwapInPlace(table,x,xNext);
	    if (size == 0) goto ddSwapAnyOutOfMem;
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddSwapAnyOutOfMem;
	    move->x = x;
	    move->y = xNext;
	    move->size = size;
	    move->next = moves;
	    moves = move;

	    size = cuddSwapInPlace(table,yNext,y);
	    if (size == 0) goto ddSwapAnyOutOfMem;
	    move = (Move *) cuddDynamicAllocNode(table);
	    if (move == NULL) goto ddSwapAnyOutOfMem;
	    move->x = yNext;
	    move->y = y;
	    move->size = size;
	    move->next = moves;
	    moves = move;

	    x = xNext;
	    y = yNext;
	}

	xNext = cuddNextHigh(table,x);
	yNext = cuddNextLow(table,y);
	if (xNext > yRef) break;

	if ((double) size > table->maxGrowth * (double) limitSize) break;
	if (size < limitSize) limitSize = size;
    }
    if (yNext>=xRef) {
	size = cuddSwapInPlace(table,yNext,y);
	if (size == 0) goto ddSwapAnyOutOfMem;
	move = (Move *) cuddDynamicAllocNode(table);
	if (move == NULL) goto ddSwapAnyOutOfMem;
	move->x = yNext;
	move->y = y;
	move->size = size;
	move->next = moves;
	moves = move;
    }

    return(moves);

ddSwapAnyOutOfMem:
    while (moves != NULL) {
	move = moves->next;
	cuddDeallocMove(table, moves);
	moves = move;
    }
    return(NULL);

} /* end of ddSwapAny */


/**
  @brief Given xLow <= x <= xHigh moves x up and down between the
  boundaries.

  @details Finds the best position and does the required changes.

  @return 1 if successful; 0 otherwise.

  @sideeffect None

*/
static int
ddSiftingAux(
  DdManager * table,
  int  x,
  int  xLow,
  int  xHigh)
{

    Move	*move;
    Move	*moveUp;		/* list of up moves */
    Move	*moveDown;		/* list of down moves */
    int		initialSize;
    int		result;
	//1. 初始化阶段
    initialSize = (int) (table->keys - table->isolated);

    moveDown = NULL;
    moveUp = NULL;
	//2. 判断变量初始位置，决定先向上还是向下移动,然后回溯操作，找到最优状态

		//第一种情况
    if (x == xLow) {
	moveDown = ddSiftingDown(table,x,xHigh);						//ddSiftingDown 或 ddSiftingUp 只是把变量往某个方向移动，并记录变化过程
	/* At this point x --> xHigh unless bounding occurred. */
	if (moveDown == (Move *) CUDD_OUT_OF_MEM) goto ddSiftingAuxOutOfMem;
	/* Move backward and stop at best position. */
	result = ddSiftingBackward(table,initialSize,moveDown);			//回溯操作，找到移动过程中决策图最小的状态，并停留在那里
	if (!result) goto ddSiftingAuxOutOfMem;
	
		//第二种情况
    } else if (x == xHigh) {
	moveUp = ddSiftingUp(table,x,xLow);
	/* At this point x --> xLow unless bounding occurred. */
	if (moveUp == (Move *) CUDD_OUT_OF_MEM) goto ddSiftingAuxOutOfMem;
	/* Move backward and stop at best position. */
	result = ddSiftingBackward(table,initialSize,moveUp);
	if (!result) goto ddSiftingAuxOutOfMem;

		//第三种情况
    } else if ((x - xLow) > (xHigh - x)) { /* must go down first: shorter */
	moveDown = ddSiftingDown(table,x,xHigh);
	/* At this point x --> xHigh unless bounding occurred. */
	if (moveDown == (Move *) CUDD_OUT_OF_MEM) goto ddSiftingAuxOutOfMem;
	if (moveDown != NULL) {
	    x = moveDown->y;			//将变量 x 更新为最新位置。
	}
	moveUp = ddSiftingUp(table,x,xLow);
	if (moveUp == (Move *) CUDD_OUT_OF_MEM) goto ddSiftingAuxOutOfMem;
	/* Move backward and stop at best position */
	result = ddSiftingBackward(table,initialSize,moveUp);
	if (!result) goto ddSiftingAuxOutOfMem;

		//第四种情况
    } else { /* must go up first: shorter */
	moveUp = ddSiftingUp(table,x,xLow);
	/* At this point x --> xLow unless bounding occurred. */
	if (moveUp == (Move *) CUDD_OUT_OF_MEM) goto ddSiftingAuxOutOfMem;
	if (moveUp != NULL) {
	    x = moveUp->x;
	}
	moveDown = ddSiftingDown(table,x,xHigh);
	if (moveDown == (Move *) CUDD_OUT_OF_MEM) goto ddSiftingAuxOutOfMem;
	/* Move backward and stop at best position. */
	result = ddSiftingBackward(table,initialSize,moveDown);
	if (!result) goto ddSiftingAuxOutOfMem;
    }

	//3. 释放内存	
    while (moveDown != NULL) {
	move = moveDown->next;
	cuddDeallocMove(table, moveDown);
	moveDown = move;
    }
    while (moveUp != NULL) {
	move = moveUp->next;
	cuddDeallocMove(table, moveUp);
	moveUp = move;
    }

    return(1);
	//4. 异常处理
ddSiftingAuxOutOfMem:
    if (moveDown != (Move *) CUDD_OUT_OF_MEM) {
	while (moveDown != NULL) {
	    move = moveDown->next;
	    cuddDeallocMove(table, moveDown);
	    moveDown = move;
	}
    }
    if (moveUp != (Move *) CUDD_OUT_OF_MEM) {
	while (moveUp != NULL) {
	    move = moveUp->next;
	    cuddDeallocMove(table, moveUp);
	    moveUp = move;
	}
    }

    return(0);

} /* end of ddSiftingAux */


/**
  @brief Sifts a variable up.

  @details Moves y up until either it reaches the bound (xLow) or the
  size of the %DD heap increases too much.将 y 向上移动，直到达到限值 (xLow) 或 %DD 堆的大小增加太多。

  @return the set of moves in case of success; NULL if memory is full.

  @sideeffect None

*/
static Move *
ddSiftingUp(
  DdManager * table,
  int  y,
  int  xLow)
{
    Move	*moves;
    Move	*move;
    int		x;
    int		size;
    int		limitSize;
    int		xindex, yindex;
    int		isolated;
    int		L;	/* lower bound on DD size */
#ifdef DD_DEBUG
    int checkL;
    int z;
    int zindex;
#endif
	//1. 初始化操作
    moves = NULL;
    yindex = table->invperm[y];			//输入层级，可以得到索引;

    /* Initialize the lower bound. 初始化下限。
    ** The part of the DD below y will not change. DD 在 y  				以下的部分不会改变。
    ** The part of the DD above y that does not interact with y will not  	以上的 DD 中与 y 无关的部分不会改变。
    ** change. The rest may vanish in the best case, except for
    ** the nodes at level xLow, which will not vanish, regardless.y 在最佳情况下，其余部分可能会消失，除了 位于 xLow 层的节点不会消失。
    */
	//2.  遍历检测交互，更新 L ;计算初始lower界限 (L)
    limitSize = L = (int) (table->keys - table->isolated);
    for (x = xLow + 1; x < y; x++) {	//遍历 xLow + 1 到 y 之间的所有变量，检查每个变量与 y 是否存在交互。
		xindex = table->invperm[x];
		if (cuddTestInteract(table,xindex,yindex)) {
			isolated = table->vars[xindex]->ref == 1;
			L -= table->subtables[x].keys - isolated;//如果变量 xindex 与 yindex 存在交互，说明交换可能会改变 BDD 结构，需要减去当前层的节点数，更新下界 L
		}
    }
    isolated = table->vars[yindex]->ref == 1;
    L -= (int) table->subtables[y].keys - isolated;
	//3. 开始变量上移过程
    x = cuddNextLow(table,y);				// 获取 y 上方（靠近根节点）的变量
    while (x >= xLow && L <= limitSize) {	// 没到达xlow且节点数未显著增长
			xindex = table->invperm[x];
#ifdef DD_DEBUG
	checkL = (int) (table->keys - table->isolated);
	for (z = xLow + 1; z < y; z++) {
	    zindex = table->invperm[z];
	    if (cuddTestInteract(table,zindex,yindex)) {
		isolated = table->vars[zindex]->ref == 1;
		checkL -= (int) table->subtables[z].keys - isolated;
	    }
	}
	isolated = table->vars[yindex]->ref == 1;
	checkL -= (int) table->subtables[y].keys - isolated;
	assert(L == checkL);
#endif
		//4. 交换变量
			size = cuddSwapInPlace(table,x,y);				//成功的话返回节点数目
			if (size == 0) goto ddSiftingUpOutOfMem;
		/*5. 更新lower界限 (L) Update the lower bound. */
			if (cuddTestInteract(table,xindex,yindex)) {
				isolated = table->vars[xindex]->ref == 1;
				L += (int) table->subtables[y].keys - isolated;
			}
		//6. 记录本次移动
			move = (Move *) cuddDynamicAllocNode(table);
			if (move == NULL) goto ddSiftingUpOutOfMem;
			move->x = x;
			move->y = y;
			move->size = size;
			move->next = moves;					// 插入到移动链表;	使用链表将所有的移动记录串联起来，方便回溯和撤销
			moves = move;
		//7. 检查终止条件
			if ((double) size > (double) limitSize * table->maxGrowth) break;	// 增长太多则停止
			if (size < limitSize) limitSize = size;								// 更新最小 BDD 大小
			y = x;
			x = cuddNextLow(table,y);
    }
    return(moves);
	//8. 结束处理
ddSiftingUpOutOfMem:
    while (moves != NULL) {
	move = moves->next;
	cuddDeallocMove(table, moves);
	moves = move;
    }
    return((Move *) CUDD_OUT_OF_MEM);

} /* end of ddSiftingUp */


/**
  @brief Sifts a variable down.

  @details Moves x down until either it reaches the bound (xHigh) or
  the size of the %DD heap increases too much.

  @return the set of moves in case of success; NULL if memory is full.

  @sideeffect None

*/
static Move *
ddSiftingDown(
  DdManager * table,
  int  x,
  int  xHigh)
{
    Move	*moves;
    Move	*move;
    int		y;
    int		size;
    int		R;	/* upper bound on node decrease */
    int		limitSize;
    int		xindex, yindex;
    int		isolated;
#ifdef DD_DEBUG
    int		checkR;
    int		z;
    int		zindex;
#endif

    moves = NULL;
    /* Initialize R */
    xindex = table->invperm[x];				//输入层级返回索引
    limitSize = size = (int) (table->keys - table->isolated);
    R = 0;
    for (y = xHigh; y > x; y--) {			//遍历 xHigh 到 x 之间的变量
	yindex = table->invperm[y];
	if (cuddTestInteract(table,xindex,yindex)) {
	    isolated = table->vars[yindex]->ref == 1;
	    R += (int) table->subtables[y].keys - isolated;
	}
    }

    y = cuddNextHigh(table,x);			// 取 x 下面的变量 y
    while (y <= xHigh && size - R < limitSize) {
#ifdef DD_DEBUG
	checkR = 0;
	for (z = xHigh; z > x; z--) {
	    zindex = table->invperm[z];
	    if (cuddTestInteract(table,xindex,zindex)) {
		isolated = table->vars[zindex]->ref == 1;
		checkR += (int) table->subtables[z].keys - isolated;
	    }
	}
	assert(R == checkR);
#endif
		/* Update upper bound on node decrease. */
		yindex = table->invperm[y];
		if (cuddTestInteract(table,xindex,yindex)) {
			isolated = table->vars[yindex]->ref == 1;
			R -= (int) table->subtables[y].keys - isolated;
		}
		size = cuddSwapInPlace(table,x,y);		//相邻变量交换核心算法，返回节点数目
		if (size == 0) goto ddSiftingDownOutOfMem;
		move = (Move *) cuddDynamicAllocNode(table);
		if (move == NULL) goto ddSiftingDownOutOfMem;
		move->x = x;		//记录本次交换数据
		move->y = y;
		move->size = size;
		move->next = moves;//将 move 加入 moves 链表
		moves = move;
		if ((double) size > (double) limitSize * table->maxGrowth) break;
		if (size < limitSize) limitSize = size;
		x = y;				//将x移到y,开始下一次移动
		y = cuddNextHigh(table,x);
    }
    return(moves);

ddSiftingDownOutOfMem:
    while (moves != NULL) {
	move = moves->next;
	cuddDeallocMove(table, moves);
	moves = move;
    }
    return((Move *) CUDD_OUT_OF_MEM);

} /* end of ddSiftingDown */


/**
  @brief Given a set of moves, returns the %DD heap to the position
  giving the minimum size.给定一组移动，将 %DD 堆返回到最小尺寸的位置。

  @details In case of ties, returns to the closest position giving the
  minimum size.

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddSiftingBackward(
  DdManager * table,
  int  size,
  Move * moves)
{
    Move *move;
    int	res;

    for (move = moves; move != NULL; move = move->next) {
	if (move->size < size) {
	    size = move->size;
	}
    }

    for (move = moves; move != NULL; move = move->next) {
		if (move->size == size) return(1);
		res = cuddSwapInPlace(table,(int)move->x,(int)move->y);
		if (!res) return(0);
    }

    return(1);

} /* end of ddSiftingBackward */


/**
  @brief Prepares the %DD heap for dynamic reordering.为动态重排序准备 %DD 堆。

  @details Does garbage collection, to guarantee that there are no
  dead nodes; clears the cache, which is invalidated by dynamic
  reordering; initializes the number of isolated projection functions;
  and initializes the interaction matrix.
  进行垃圾回收，以确保没有死节点；清除缓存，缓存会因动态重排序而失效；
  初始化孤立投影函数的数量；以及初始化交互矩阵。

  @return 1 in case of success; 0 otherwise.

  @sideeffect None

*/
static int
ddReorderPreprocess(
  DdManager * table)
{
    int i;
    int res;

    /* 1.清楚全局和局部缓存	Clear the cache. */
    cuddCacheFlush(table);
    cuddLocalCacheClearAll(table);

    /* 2.垃圾回收，回收所有死节点	Eliminate dead nodes. Do not scan the cache again. */
    cuddGarbageCollect(table,0);

    /* 3.统计孤立投影函数的数量	Initialize number of isolated projection functions. */
    table->isolated = 0;
    for (i = 0; i < table->size; i++) {
	if (table->vars[i]->ref == 1) table->isolated++;	//孤立节点通常不会与其他变量交互，减少对它们的处理可以提高性能。
    }

    /* 5. 初始化交互矩阵	Initialize the interaction matrix. */
    res = cuddInitInteract(table);
    if (res == 0) return(0);

    return(1);

} /* end of ddReorderPreprocess */


/**
  @brief Cleans up at the end of reordering.在重新排序结束时进行清理。

  @sideeffect None

*/
static int
ddReorderPostprocess(
  DdManager * table)
{

#ifdef DD_VERBOSE
    (void) fflush(table->out);
#endif

    /* Free interaction matrix. */
    FREE(table->interact);

    return(1);

} /* end of ddReorderPostprocess */


/**
  @brief Reorders variables according to a given permutation.

  @details The i-th permutation array contains the index of the
  variable that should be brought to the i-th level. ddShuffle assumes
  that no dead nodes are present and that the interaction matrix is
  properly initialized.  The reordering is achieved by a series of
  upward sifts.

  @return 1 if successful; 0 otherwise.

  @sideeffect None

*/
static int
ddShuffle(
  DdManager * table,
  int * permutation)
{
    int		index;
    int		level;
    int		position;
    int		numvars;
    int		result;
#ifdef DD_STATS
    unsigned long localTime;
    int		initialSize;
    int		finalSize;
    int		previousSize;
#endif

    table->ddTotalNumberSwapping = 0;
#ifdef DD_STATS
    localTime = util_cpu_time();
    initialSize = table->keys - table->isolated;
    (void) fprintf(table->out,"#:I_SHUFFLE %8d: initial size\n",
		   initialSize);
    table->totalNISwaps = 0;
#endif

    numvars = table->size;

    for (level = 0; level < numvars; level++) {
	index = permutation[level];
	position = table->perm[index];
#ifdef DD_STATS
	previousSize = table->keys - table->isolated;
#endif
	result = ddSiftUp(table,position,level);
	if (!result) return(0);
#ifdef DD_STATS
	if (table->keys < (unsigned) previousSize + table->isolated) {
	    (void) fprintf(table->out,"-");
	} else if (table->keys > (unsigned) previousSize + table->isolated) {
	    (void) fprintf(table->out,"+");	/* should never happen */
	} else {
	    (void) fprintf(table->out,"=");
	}
	fflush(table->out);
#endif
    }

#ifdef DD_STATS
    (void) fprintf(table->out,"\n");
    finalSize = table->keys - table->isolated;
    (void) fprintf(table->out,"#:F_SHUFFLE %8d: final size\n",finalSize);
    (void) fprintf(table->out,"#:T_SHUFFLE %8g: total time (sec)\n",
	((double)(util_cpu_time() - localTime)/1000.0));
    (void) fprintf(table->out,"#:N_SHUFFLE %8d: total swaps\n",
		   table->ddTotalNumberSwapping);
    (void) fprintf(table->out,"#:M_SHUFFLE %8d: NI swaps\n",
                   table->totalNISwaps);
#endif

    return(1);

} /* end of ddShuffle */


/**
  @brief Moves one variable up.

  @details Takes a variable from position x and sifts it up to
  position xLow;  xLow should be less than or equal to x.

  @return 1 if successful; 0 otherwise

  @sideeffect None

*/
static int
ddSiftUp(
  DdManager * table,
  int  x,
  int  xLow)
{
    int        y;
    int        size;

    y = cuddNextLow(table,x);
    while (y >= xLow) {
	size = cuddSwapInPlace(table,y,x);
	if (size == 0) {
	    return(0);
	}
	x = y;
	y = cuddNextLow(table,x);
    }
    return(1);

} /* end of ddSiftUp */


/**
  @brief Fixes the %BDD variable group tree after a shuffle.

  @details Assumes that the order of the variables in a terminal node
  has not been changed.

  @sideeffect Changes the %BDD variable group tree.

*/
static void
bddFixTree(
  DdManager * table,
  MtrNode * treenode)
{
    if (treenode == NULL) return;
    treenode->low = ((int) treenode->index < table->size) ?
	(MtrHalfWord) table->perm[treenode->index] : treenode->index;
    if (treenode->child != NULL) {
	bddFixTree(table, treenode->child);
    }
    if (treenode->younger != NULL)
	bddFixTree(table, treenode->younger);
    if (treenode->parent != NULL && treenode->low < treenode->parent->low) {
	treenode->parent->low = treenode->low;
	treenode->parent->index = treenode->index;
    }
    return;

} /* end of bddFixTree */


/**
  @brief Updates the %BDD variable group tree before a shuffle.

  @return 1 if successful; 0 otherwise.

  @sideeffect Changes the %BDD variable group tree.

*/
static int
ddUpdateMtrTree(
  DdManager * table,
  MtrNode * treenode,
  int * perm,
  int * invperm)
{
    unsigned int i, size;
    int index, level, minLevel, maxLevel, minIndex;

    if (treenode == NULL) return(1);

    minLevel = CUDD_MAXINDEX;
    maxLevel = 0;
    minIndex = -1;
    /* i : level */
    for (i = treenode->low; i < treenode->low + treenode->size; i++) {
	index = table->invperm[i];
	level = perm[index];
	if (level < minLevel) {
	    minLevel = level;
	    minIndex = index;
	}
	if (level > maxLevel)
	    maxLevel = level;
    }
    size = maxLevel - minLevel + 1;
    if (minIndex == -1) return(0);
    if (size == treenode->size) {
	treenode->low = minLevel;
	treenode->index = minIndex;
    } else {
	return(0);
    }

    if (treenode->child != NULL) {
	if (!ddUpdateMtrTree(table, treenode->child, perm, invperm))
	    return(0);
    }
    if (treenode->younger != NULL) {
	if (!ddUpdateMtrTree(table, treenode->younger, perm, invperm))
	    return(0);
    }
    return(1);
}


/**
  @brief Checks the %BDD variable group tree before a shuffle.

  @return 1 if successful; 0 otherwise.

  @sideeffect Changes the %BDD variable group tree.

*/
static int
ddCheckPermuation(
  DdManager * table,
  MtrNode * treenode,
  int * perm,
  int * invperm)
{
    unsigned int i, size;
    int index, level, minLevel, maxLevel;

    if (treenode == NULL) return(1);

    minLevel = table->size;
    maxLevel = 0;
    /* i : level */
    for (i = treenode->low; i < treenode->low + treenode->size; i++) {
	index = table->invperm[i];
	level = perm[index];
	if (level < minLevel)
	    minLevel = level;
	if (level > maxLevel)
	    maxLevel = level;
    }
    size = maxLevel - minLevel + 1;
    if (size != treenode->size)
	return(0);

    if (treenode->child != NULL) {
	if (!ddCheckPermuation(table, treenode->child, perm, invperm))
	    return(0);
    }
    if (treenode->younger != NULL) {
	if (!ddCheckPermuation(table, treenode->younger, perm, invperm))
	    return(0);
    }
    return(1);
}
