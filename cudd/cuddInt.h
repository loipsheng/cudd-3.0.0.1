/**
  @file

  @ingroup cudd

  @brief Internal data structures of the CUDD package.

  @author Fabio Somenzi

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

#ifndef CUDD_INT_H_
#define CUDD_INT_H_


/*---------------------------------------------------------------------------*/
/* Nested includes                                                           */
/*---------------------------------------------------------------------------*/

#include <math.h>
#include "config.h"
#include "st.h"
#include "mtr.h"
#include "epd.h"
#include "cudd.h"

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

#define CUDD_VERSION		PACKAGE_VERSION

#define DD_MAXREF		((DdHalfWord) ~0)

#define DD_DEFAULT_RESIZE	10	/* how many extra variables */
					/* should be added when resizing */
#define DD_MEM_CHUNK		1022

/* These definitions work for CUDD_VALUE_TYPE == double */
#define DD_ONE_VAL		(1.0)
#define DD_ZERO_VAL		(0.0)
#define DD_EPSILON		(1.0e-12)

/* The definitions of +/- infinity in terms of HUGE_VAL work on
** the DECstations and on many other combinations of OS/compiler.
*/
#ifdef HAVE_IEEE_754
#  define DD_PLUS_INF_VAL	(HUGE_VAL)
#else
#  define DD_PLUS_INF_VAL	(10e301)
#  define DD_CRI_HI_MARK	(10e150)
#  define DD_CRI_LO_MARK	(-(DD_CRI_HI_MARK))
#endif
#define DD_MINUS_INF_VAL	(-(DD_PLUS_INF_VAL))

#define DD_NON_CONSTANT		((DdNode *) 1)	/* for Cudd_bddIteConstant */

/* Unique table and cache management constants. */
#define DD_MAX_SUBTABLE_DENSITY 4	/* tells when to resize a subtable */
/* gc when this percent are dead (measured w.r.t. slots, not keys)
** The first limit (LO) applies normally. The second limit applies when
** the package believes more space for the unique table (i.e., more dead
** nodes) would improve performance, and the unique table is not already
** too large. The third limit applies when memory is low.
*/
#define DD_GC_FRAC_LO		DD_MAX_SUBTABLE_DENSITY * 0.25
#define DD_GC_FRAC_HI		DD_MAX_SUBTABLE_DENSITY * 1.0
#define DD_GC_FRAC_MIN		0.2
#define DD_MIN_HIT		30	/* resize cache when hit ratio
					   above this percentage (default) */
#define DD_MAX_LOOSE_FRACTION	5 /* 1 / (max fraction of memory used for
				     unique table in fast growth mode) */
#define DD_MAX_CACHE_FRACTION	3 /* 1 / (max fraction of memory used for
				     computed table if resizing enabled) */
#define DD_STASH_FRACTION	64 /* 1 / (fraction of memory set
				      aside for emergencies) */
#define DD_MAX_CACHE_TO_SLOTS_RATIO 4 /* used to limit the cache size */

/* Variable ordering default parameter values. */
#define DD_SIFT_MAX_VAR		1000
#define DD_SIFT_MAX_SWAPS	2000000
#define DD_DEFAULT_RECOMB	0
#define DD_MAX_REORDER_GROWTH	1.2
#define DD_FIRST_REORDER	4004	/* 4 for the constants */
#define DD_DYN_RATIO		2	/* when to dynamically reorder */

/* Primes for cache hash functions. */
#define DD_P1			12582917
#define DD_P2			4256249
#define DD_P3			741457
#define DD_P4			1618033999

/* Cache tags for 3-operand operators.  These tags are stored in the
** least significant bits of the cache operand pointers according to
** the following scheme.  The tag consists of two hex digits.  Both digits
** must be even, so that they do not interfere with complementation bits.
** The least significant one is stored in Bits 3:1 of the f operand in the
** cache entry.  Bit 1 is always 1, so that we can differentiate
** three-operand operations from one- and two-operand operations.
** Therefore, the least significant digit is one of {2,6,a,e}.  The most
** significant digit occupies Bits 3:1 of the g operand in the cache
** entry.  It can by any even digit between 0 and e.  This gives a total
** of 5 bits for the tag proper, which means a maximum of 32 three-operand
** operations. */
#define DD_ADD_ITE_TAG				0x02
#define DD_BDD_AND_ABSTRACT_TAG			0x06
#define DD_BDD_XOR_EXIST_ABSTRACT_TAG		0x0a
#define DD_BDD_ITE_TAG				0x0e
#define DD_ADD_BDD_DO_INTERVAL_TAG		0x22
#define DD_BDD_CLIPPING_AND_ABSTRACT_UP_TAG	0x26
#define DD_BDD_CLIPPING_AND_ABSTRACT_DOWN_TAG	0x2a
#define DD_BDD_COMPOSE_RECUR_TAG		0x2e
#define DD_ADD_COMPOSE_RECUR_TAG		0x42
#define DD_ADD_NON_SIM_COMPOSE_TAG		0x46
#define DD_EQUIV_DC_TAG				0x4a
#define DD_ZDD_ITE_TAG				0x4e
#define DD_ADD_ITE_CONSTANT_TAG			0x62
#define DD_ADD_EVAL_CONST_TAG			0x66
#define DD_BDD_ITE_CONSTANT_TAG			0x6a
#define DD_ADD_OUT_SUM_TAG			0x6e
#define DD_BDD_LEQ_UNLESS_TAG			0x82
#define DD_ADD_TRIANGLE_TAG			0x86
#define DD_BDD_MAX_EXP_TAG			0x8a
#define DD_VARS_SYMM_BEFORE_TAG			0x8e
#define DD_VARS_SYMM_BETWEEN_TAG		0xa2

/* Generator constants. */
#define CUDD_GEN_CUBES 0
#define CUDD_GEN_PRIMES 1
#define CUDD_GEN_NODES 2
#define CUDD_GEN_ZDD_PATHS 3
#define CUDD_GEN_EMPTY 0
#define CUDD_GEN_NONEMPTY 1

/**
 ** @brief Maximum variable index.
 **
 ** @details CUDD_MAXINDEX is defined in such a way that on 32-bit and
 ** 64-bit machines one can cast an index to (int) without generating
 ** a negative number.
 */
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
#define CUDD_MAXINDEX		(((DdHalfWord) ~0) >> 1)
#else
#define CUDD_MAXINDEX		((DdHalfWord) ~0)
#endif

/**
 ** @brief The index of constant nodes.
 **
 ** @details This is a synonim for CUDD_MAXINDEX.
 */
#define CUDD_CONST_INDEX	CUDD_MAXINDEX

/**
 ** @brief Size of the random number generator shuffle table.
 */
#define STAB_SIZE 64

/**
 ** @brief Mask for periodic check of termination and timeout.
 **
 ** @see checkWhetherToGiveUp
 */
#define CUDD_CHECK_MASK 0x7ff

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/**
   @brief Type that is half the size of a pointer.
*/
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
typedef uint32_t DdHalfWord;
#else
typedef uint16_t DdHalfWord;
#endif

/**
 * @brief Signed integer that is the size of a pointer.
 *
 * @details The only platforms on which CUDD has been tested define
 * intptr_t and uintptr_t in inttypes.h and satisfy the condition
 *
 *     sizeof(intptr_t) == sizeof(uintptr_t) == sizeof(void *)
 *
 * Neither of these is guaranteed by the C standard.
 */
typedef intptr_t ptrint;

/**
 * @brief Unsigned integer that is the size of a pointer.
 *
 * @see ptrint
 */
typedef uintptr_t ptruint;

typedef struct DdChildren DdChildren;
typedef struct DdHook DdHook;
typedef struct DdSubtable DdSubtable;
typedef struct DdCache DdCache;
typedef struct DdLocalCacheItem DdLocalCacheItem;
typedef struct DdLocalCache DdLocalCache;
typedef struct DdHashItem DdHashItem;
typedef struct DdHashTable DdHashTable;
typedef struct Move Move;
typedef struct IndexKey IndexKey;
typedef struct DdQueueItem DdQueueItem;
typedef struct DdLevelQueue DdLevelQueue;

/*---------------------------------------------------------------------------*/
/* Stucture declarations                                                     */
/*---------------------------------------------------------------------------*/

/**
 * @brief The two children of a non-terminal node.
 */
struct DdChildren {
    struct DdNode *T;	/**< then (true) child */
    struct DdNode *E;	/**< else (false) child */
};

/**
 * @brief Decision diagram node.
 */
struct DdNode {
    DdHalfWord index;		/**< variable index */
    DdHalfWord ref;		/**< reference count */
    DdNode *next;		/**< next pointer for unique table */
    union {
	CUDD_VALUE_TYPE value;	/**< for constant (terminal) nodes */
	DdChildren kids;	/**< for internal nodes */
    } type;			/**< terminal or internal */
};

/**
 * @brief CUDD generator.
 */
struct DdGen {
    DdManager	*manager;
    int		type;
    int		status;
    union {
	struct {
	    int			*cube;
	    CUDD_VALUE_TYPE	value;
	} cubes;
	struct {
	    int			*cube;
	    DdNode		*ub;
	} primes;
	struct {
	    int                 size;
	} nodes;
    } gen;
    struct {
	int	sp;
	DdNode	**stack;
    } stack;
    DdNode	*node;
};

/**
 ** @brief CUDD hook
 **
 ** Hooks in CUDD are functions that the application registers with the
 ** manager so that they are called at appropriate times. The functions
 ** are passed the manager as argument; they should return 1 if
 ** successful and 0 otherwise.
 */
struct DdHook {
    DD_HFP f;			/**< function to be called */
    struct DdHook *next;	/**< next element in the list */
};

/**
 *  @brief Generic local cache item.
 */
struct DdLocalCacheItem {
    DdNode *value;
#ifdef DD_CACHE_PROFILE
    ptrint count;
#endif
    DdNode *key[1];
};

/**
 *  @brief Local cache.
 */
struct DdLocalCache {
    DdLocalCacheItem *item;
    unsigned int itemsize;
    unsigned int keysize;
    unsigned int slots;
    int shift;
    double lookUps;
    double minHit;
    double hits;
    unsigned int maxslots;
    DdManager *manager;
    struct DdLocalCache *next;
};

/**
 *  @brief Local hash table item.
 */
struct DdHashItem {
    struct DdHashItem *next;	/**< collision list link */
    ptrint count;		/**< reference count of item */
    DdNode *value;		/**< value %DD */
    DdNode *key[1];		/**< key pointers */
};

/**
 * @brief Local hash table.
 */
struct DdHashTable {
    unsigned int keysize;	/**< number of pointers in the key */
    unsigned int itemsize;	/**< size of hash table item in bytes */
    DdHashItem **bucket;	/**< array of buckets */
    DdHashItem *nextFree;	/**< item free list */
    DdHashItem **memoryList;	/**< list of memory blocks for items */
    unsigned int numBuckets;	/**< number of buckets in array */
    int shift;			/**< shift used in hash function */
    unsigned int size;		/**< number of items stored in table */
    unsigned int maxsize;	/**< threshold for table resizing */
    DdManager *manager;		/**< %DD manager */
};

/**
 *  @brief Computed table.
 */
struct DdCache {
    DdNode *f,*g;		/**< DDs */
    ptruint h;			/**< either operator or %DD */
    DdNode *data;		/**< already constructed %DD */
#ifdef DD_CACHE_PROFILE
    ptrint count;		/**< statistical counter */
#endif
};

/**
 *  @brief Subtable for one index.
 */
struct DdSubtable {
    DdNode **nodelist;		/**< hash table */
    int shift;			/**< shift for hash function */
    unsigned int slots;		/**< size of the hash table */
    unsigned int keys;		/**< number of nodes stored in this table */
    unsigned int maxKeys;	/**< slots * DD_MAX_SUBTABLE_DENSITY */
    unsigned int dead;		/**< number of dead nodes in this table */
    unsigned int next;		/**< index of next variable in group */
    int bindVar;		/**< flag to bind this variable to its level        标记将此变量与其级别绑定*/
    /* Fields for lazy sifting. */
    Cudd_VariableType varType;  /**< variable type (ps, ns, pi) */
    int pairIndex;              /**< corresponding variable index (ps <-> ns) */
    int varHandled;		/**< flag: 1 means variable is already handled */
    Cudd_LazyGroupType varToBeGrouped; /**< tells what grouping to apply */
};

/**
 *  @brief Specialized %DD symbol table.
 */
struct DdManager {
    /* Constants 常量*/
    DdNode sentinel;		/**< for collision lists 用于碰撞列表*/
    DdNode *one;		/**< constant 1 */
    DdNode *zero;		/**< constant 0 */
    DdNode *plusinfinity;	/**< plus infinity  正无穷*/
    DdNode *minusinfinity;	/**< minus infinity 负无穷*/
    DdNode *background;		/**< background value */
    /* Computed Table */
    DdCache *acache;		/**< address of allocated memory for cache  为缓存分配的内存地址*/
    DdCache *cache;		/**< the cache-based computed table           基于缓存的计算表*/
    unsigned int cacheSlots;	/**< total number of cache entries    缓存条目总数*/
    int cacheShift;		/**< shift value for cache hash function      缓存哈希函数的移位值*/
    double cacheMisses;		/**< number of cache misses (since resizing) */
    double cacheHits;		/**< number of cache hits (since resizing) */
    double minHit;		/**< hit percentage above which to resize */
    int cacheSlack;		/**< slots still available for resizing       仍可调整大小的时段*/
    unsigned int maxCacheHard;	/**< hard limit for cache size */
    /* Unique Table */
    int size;			/**< number of unique subtables                   唯一子表数*/
    int sizeZ;			/**< for %ZDD */
    int maxSize;		/**< max number of subtables before resizing    调整大小前子表的最大数量*/
    int maxSizeZ;		/**< for %ZDD */
    DdSubtable *subtables;	/**< array of unique subtables */
    DdSubtable *subtableZ;	/**< for %ZDD */
    DdSubtable constants;	/**< unique subtable for the constants */
    unsigned int slots;		/**< total number of hash buckets */
    unsigned int keys;		/**< total number of %BDD and %ADD nodes */
    unsigned int keysZ;		/**< total number of %ZDD nodes */
    unsigned int dead;		/**< total number of dead %BDD and %ADD nodes */
    unsigned int deadZ;		/**< total number of dead %ZDD nodes */
    unsigned int maxLive;	/**< maximum number of live nodes */
    unsigned int minDead;	/**< do not GC if fewer than these dead  如果死亡人数少于上述人数，则不进行 GC */
    int gcEnabled;		/**< gc is enabled */
    double gcFrac;		/**< gc when this fraction is dead */
    unsigned int looseUpTo;	/**< slow growth beyond this limit */
				/**< (measured w.r.t. slots, not keys) */
    unsigned int initSlots;	/**< initial size of a subtable        子表格的初始大小*/
    DdNode **stack;		/**< stack for iterative procedures          迭代程序的堆栈*/
    double allocated;		/**< number of nodes allocated             分配的节点数*/
				/**< (not during reordering)   不在重新排序期间 */
    double reclaimed;		/**< number of nodes brought back from the dead 重新唤醒的节点数目*/
    int *perm;			/**< current variable perm. (index to level) */
    int *permZ;			/**< for %ZDD */
    int *invperm;		/**< current inv. var. perm. (level to index) */
    int *invpermZ;		/**< for %ZDD */
    DdNode **vars;		/**< projection functions */
    int *map;			/**< variable map for fast swap */
    DdNode **univ;		/**< %ZDD 1 for each variable */
    unsigned int isolated;	/**< isolated projection functions */
    unsigned int originalSize;	/**< used by lazy sifting */
    int linearSize;		/**< number of rows and columns of linear     线性行数和线性列数*/
    ptruint *interact;		/**< interacting variable matrix          交互变量矩阵*/
    ptruint *linear;		/**< linear transform matrix                线性变换矩阵*/
    /* Memory Management */
    DdNode **memoryList;	/**< memory manager for symbol table */
    DdNode *nextFree;		/**< list of free nodes */
    char *stash;		/**< memory reserve */
#ifndef DD_NO_DEATH_ROW
    DdNode **deathRow;		/**< queue for dereferencing */
    int deathRowDepth;		/**< number of slots in the queue         队列中的插槽数 */
    int nextDead;		/**< index in the queue                         队列中的索引*/
    unsigned deadMask;		/**< mask for circular index update */
#endif
    /* General Parameters */
    CUDD_VALUE_TYPE epsilon;	/**< tolerance on comparisons */
    /* Dynamic Reordering Parameters                                动态重排序参数*/
    int reordered;		/**< flag set at the end of reordering        重排序结束时设置的标志*/
    unsigned int reorderings;	/**< number of calls to Cudd_ReduceHeap 调用 Cudd_ReduceHeap 的次数*/
    unsigned int maxReorderings;/**< maximum number of calls to Cudd_ReduceHeap 调用 Cudd_ReduceHeap 的最大次数*/
    int siftMaxVar;		/**< maximum number of vars sifted            最大筛选变量数*/
    int siftMaxSwap;		/**< maximum number of swaps per sifting    每次筛选的最大交换次数*/
    int ddTotalNumberSwapping;  /**< number of %BDD/%ADD swaps completed */
    int zddTotalNumberSwapping; /**< number of %ZDD swaps completed */
    int reordCycle;		/**< how often to apply alternate threshold   交替阈值的使用频率*/
    double maxGrowth;		/**< maximum growth during reordering */
    double maxGrowthAlt;	/**< alternate maximum growth for reordering */
    int autoDyn;		/**< automatic dynamic reordering flag (BDD) */
    int autoDynZ;		/**< automatic dynamic reordering flag (ZDD) */
    Cudd_ReorderingType autoMethod;  /**< default reordering method */
    Cudd_ReorderingType autoMethodZ; /**< default reordering method (ZDD) */
    int realign;		/**< realign %ZDD order after %BDD reordering */
    int realignZ;		/**< realign %BDD order after %ZDD reordering */
    unsigned int nextDyn;	/**< reorder if this size is reached      如果达到此尺寸，则重新排序 */
    unsigned int countDead;	/**< if 0, count deads to trigger reordering */
    MtrNode *tree;		/**< variable group tree (BDD)                可变组树*/
    MtrNode *treeZ;		/**< variable group tree (ZDD) */
    Cudd_AggregationType groupcheck; /**< used during group sifting         用于组筛选的参数变量*/
    int recomb;			/**< used during group sifting */
    int symmviolation;		/**< used during group sifting */
    int arcviolation;		/**< used during group sifting */
    int populationSize;		/**< population size for GA */
    int	numberXovers;		/**< number of crossovers for GA */
    unsigned int randomizeOrder; /**< perturb the next reordering threshold */
    DdLocalCache *localCaches;	/**< local caches currently in existence */
    void *hooks;		/**< application-specific field (used by vis)           应用程序专用字段*/
    DdHook *preGCHook;		/**< hooks to be called before GC */
    DdHook *postGCHook;		/**< hooks to be called after GC */
    DdHook *preReorderingHook;	/**< hooks to be called before reordering */
    DdHook *postReorderingHook;	/**< hooks to be called after reordering */
    FILE *out;			/**< stdout for this manager */
    FILE *err;			/**< stderr for this manager */
    Cudd_ErrorType errorCode;	/**< info on last error */
    unsigned long startTime;	/**< start time in milliseconds */
    unsigned long timeLimit;	/**< CPU time limit */
    DD_THFP terminationCallback; /**< termination callback */
    void * tcbArg;		/**< second argument passed to termination handler */
    DD_OOMFP outOfMemCallback;	/**< out-of-memory callback */
    DD_TOHFP timeoutHandler;	/**< timeout handler */
    void * tohArg;		/**< second argument passed to timeout handler */
    /* Statistical counters.                                            统计计数器*/
    size_t memused;		/**< total memory allocated for the manager */
    size_t maxmem;		/**< target maximum memory */
    size_t maxmemhard;		/**< hard limit for maximum memory */
    int garbageCollections;	/**< number of garbage collections          垃圾回收的次数！！次数*/
    unsigned long GCTime;	/**< total time spent in garbage collection */
    unsigned long reordTime;	/**< total time spent in reordering */
    double totCachehits;	/**< total number of cache hits */
    double totCacheMisses;	/**< total number of cache misses */
    double cachecollisions;	/**< number of cache collisions */
    double cacheinserts;	/**< number of cache insertions */
    double cacheLastInserts;	/**< insertions at the last cache resizing */
    double cachedeletions;	/**< number of deletions during garbage coll. */
    unsigned int peakLiveNodes;	/**< maximum number of live nodes */
    /* Random number generator. */
    int32_t cuddRand;		/**< state of the random number generator */
    int32_t cuddRand2;		/**< state of the random number generator */
    int32_t shuffleSelect;	/**< state of the random number generator */
    int32_t shuffleTable[STAB_SIZE]; /**< state of the random number generator */
#ifdef DD_STATS
    double nodesFreed;		/**< number of nodes returned to the free list */
    double nodesDropped;	/**< number of nodes killed by dereferencing */
    int	totalNISwaps;		/**< number of non-interacting (cheap) swaps */
    int extsymmcalls;		/**< number of calls to symmetry check fn */
    int extsymm;		/**< number of successful symmetry checks */
    int secdiffcalls;		/**< number of calls to second difference fn */
    int secdiff;		/**< number of successful second diff. checks */
    int secdiffmisfire;		/**< number of misfired second diff. checks */
    int tosses;			/**< number of coin tosses in annealing */
    int acceptances;		/**< number of acceptances in annealing */
    int totalShuffles;		/**< number of shuffles in exact reordering */
    int totalNumberLinearTr;	/**< number of linear transformations */
    int num_calls;		/**< should equal 2n-1 (n is the # of nodes) */
#endif
#ifdef DD_UNIQUE_PROFILE
    double uniqueLookUps;	/**< number of unique table lookups */
    double uniqueLinks;		/**< total distance traveled in coll. chains */
#endif
#ifdef DD_COUNT
    double recursiveCalls;	/**< number of recursive calls */
#ifdef DD_STATS
    double nextSample;		/**< when to write next line of stats */
#endif
    double swapSteps;		/**< number of elementary reordering steps */
#endif
#ifdef DD_DEBUG
    int addPermuteRecurHits;	/**< debug variable for variable permutation */
    int bddPermuteRecurHits;	/**< debug variable for variable permutation */
    int bddVectorComposeHits;	/**< debug variable for vector composition */
    int addVectorComposeHits;	/**< debug variable for vector composition */
    int addGeneralVectorComposeHits; /**< debug var. for vector composition */
    int enableExtraDebug;	/**< deposit a 1 here to enable more debugging */
#endif
};

/**
 *  @brief Reordering move record.
 */
struct Move {
    DdHalfWord x;
    DdHalfWord y;
    unsigned int flags;
    int size;
    struct Move *next;
};

/**
 *  @brief Used to sort variables for reordering.
 */
struct IndexKey {
    int index;
    int keys;
};

/**
 *  @brief Generic level queue item.
 */
struct DdQueueItem {
    struct DdQueueItem *next;
    struct DdQueueItem *cnext;
    void *key;
};

/**
 *  @brief Level queue.
 */
struct DdLevelQueue {
    void *first;
    DdQueueItem **last;
    DdQueueItem *freelist;
    DdQueueItem **buckets;
    int levels;
    int itemsize;
    int size;
    int maxsize;
    int numBuckets;
    int shift;
    DdManager *manager;
};

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

/**
  @brief Adds node to the head of the free list.

  @details Does not deallocate memory chunks that become free.  This
  function is also used by the dynamic reordering functions.

  @sideeffect None

  @see cuddAllocNode cuddDynamicAllocNode cuddDeallocMove

*/
#define cuddDeallocNode(unique,node) \
    (node)->next = (unique)->nextFree; \
    (unique)->nextFree = node;

/**
  @brief Adds node to the head of the free list.

  @details Does not deallocate memory chunks that become free.  This
  function is also used by the dynamic reordering functions.

  @sideeffect None

  @see cuddDeallocNode cuddDynamicAllocNode

*/
#define cuddDeallocMove(unique,node) \
    ((DdNode *)(node))->ref = 0; \
    ((DdNode *)(node))->next = (unique)->nextFree; \
    (unique)->nextFree = (DdNode *)(node);


/**
  @brief Increases the reference count of a node, if it is not
  saturated.如果节点的引用计数未达到饱和，则增加该节点的引用计数。

  @details This being a macro, it is faster than Cudd_Ref, but it
  cannot be used in constructs like cuddRef(a = b()).作为一个宏，它比 Cudd_Ref 更快，但不能用于 cuddRef(a = b()) 这样的构造。

  @sideeffect none

  @see Cudd_Ref

*/
#define cuddRef(n) cuddSatInc(Cudd_Regular(n)->ref)


/**
  @brief Decreases the reference count of a node, if it is not
  saturated.如果节点的引用计数未达到饱和，则减少该节点的引用计数。

  @details It is primarily used in recursive procedures to decrease
  the ref count of a result node before returning it. This
  accomplishes the goal of removing the protection applied by a
  previous cuddRef. This being a macro, it is faster than Cudd_Deref,
  but it cannot be used in constructs like cuddDeref(a = b()).
  它主要用于递归程序，在返回结果节点之前减少该节点的 ref 数量。
  这样做的目的是移除前一个 cuddRef 应用的保护。
  作为一个宏，它比 Cudd_Deref 更快，但不能用于 cuddDeref(a = b())之类的结构。

  @sideeffect none

  @see Cudd_Deref

*/
#define cuddDeref(n) cuddSatDec(Cudd_Regular(n)->ref)


/**
  @brief Returns 1 if the node is a constant node.

  @details Returns 1 if the node is a constant node (rather than an
  internal node). All constant nodes have the same index
  (CUDD_CONST_INDEX). The pointer passed to Cudd_IsConstantInt may be either
  regular or complemented.

  @sideeffect none

  @see cuddIsConstant Cudd_IsConstant

*/
#define Cudd_IsConstantInt(node) ((Cudd_Regular(node))->index == CUDD_CONST_INDEX)


/**
  @brief Returns 1 if the node is a constant node.

  @details Returns 1 if the node is a constant node (rather than an
  internal node). All constant nodes have the same index
  (CUDD_CONST_INDEX). The pointer passed to cuddIsConstant must be regular.

  @sideeffect none

  @see Cudd_IsConstant Cudd_IsConstantInt

*/
#define cuddIsConstant(node) ((node)->index == CUDD_CONST_INDEX)


/**
  @brief Returns the then child of an internal node.

  @details If <code>node</code> is a constant node, the result is
  unpredictable.  The pointer passed to cuddT must be regular.

  @sideeffect none

  @see Cudd_T

*/
#define cuddT(node) ((node)->type.kids.T)


/**
  @brief Returns the else child of an internal node.

  @details If <code>node</code> is a constant node, the result is
  unpredictable.  The pointer passed to cuddE must be regular.

  @sideeffect none

  @see Cudd_E

*/
#define cuddE(node) ((node)->type.kids.E)


/**
  @brief Returns the value of a constant node.

  @details If <code>node</code> is an internal node, the result is
  unpredictable.  The pointer passed to cuddV must be regular.

  @sideeffect none

  @see Cudd_V

*/
#define cuddV(node) ((node)->type.value)


/**
  @brief Finds the current position of variable index in the
  order.

  @details This macro duplicates the functionality of Cudd_ReadPerm,
  but it does not check for out-of-bounds indices and it is more
  efficient.

  @sideeffect none

  @see Cudd_ReadPerm

*/
#define cuddI(dd,index) (((index)==CUDD_CONST_INDEX)?(int)(index):(dd)->perm[(index)])


/**
  @brief Finds the current position of %ZDD variable index in the
  order.

  @details This macro duplicates the functionality of
  Cudd_ReadPermZdd, but it does not check for out-of-bounds indices
  and it is more efficient.

  @sideeffect none

  @see Cudd_ReadPermZdd

*/
#define cuddIZ(dd,index) (((index)==CUDD_CONST_INDEX)?(int)(index):(dd)->permZ[(index)])


/**
  @brief Hash function for the unique table.

  @details 

  @sideeffect none

  @see ddCHash ddCHash2

*/
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
#define ddHash(f,g,s) \
((((unsigned)(ptruint)(f) * DD_P1 + \
   (unsigned)(ptruint)(g)) * DD_P2) >> (s))
#else
#define ddHash(f,g,s) \
((((unsigned)(f) * DD_P1 + (unsigned)(g)) * DD_P2) >> (s))
#endif


/**
  @brief Hash function for the cache.

  @sideeffect none

  @see ddHash ddCHash2

*/
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
#define ddCHash(o,f,g,h,s) \
((((((unsigned)(ptruint)(f) + (unsigned)(ptruint)(o)) * DD_P1 + \
    (unsigned)(ptruint)(g)) * DD_P2 + \
   (unsigned)(ptruint)(h)) * DD_P3) >> (s))
#else
#define ddCHash(o,f,g,h,s) \
((((((unsigned)(f) + (unsigned)(o)) * DD_P1 + (unsigned)(g)) * DD_P2 + \
   (unsigned)(h)) * DD_P3) >> (s))
#endif


/**
  @brief Hash function for the cache for functions with two operands.

  @sideeffect none

  @see ddHash ddCHash

*/
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
#define ddCHash2(o,f,g,s) \
(((((unsigned)(ptruint)(f) + (unsigned)(ptruint)(o)) * DD_P1 + \
   (unsigned)(ptruint)(g)) * DD_P2) >> (s))
#else
#define ddCHash2(o,f,g,s) \
(((((unsigned)(f) + (unsigned)(o)) * DD_P1 + (unsigned)(g)) * DD_P2) >> (s))
#endif


/**
  @brief Clears the 4 least significant bits of a pointer.

  @sideeffect none

*/
#define cuddClean(p) ((DdNode *)((ptruint)(p) & ~ (ptruint) 0xf))


/**
  @brief Computes the minimum of two numbers.

  @sideeffect none

  @see ddMax

*/
#define ddMin(x,y) (((y) < (x)) ? (y) : (x))


/**
  @brief Computes the maximum of two numbers.

  @sideeffect none

  @see ddMin

*/
#define ddMax(x,y) (((y) > (x)) ? (y) : (x))


/**
  @brief Computes the absolute value of a number.

  @sideeffect none

*/
#define ddAbs(x) (((x)<0) ? -(x) : (x))


/**
  @brief Returns 1 if the absolute value of the difference of the two
  arguments x and y is less than e.

  @sideeffect none

*/
#define ddEqualVal(x,y,e) (ddAbs((x)-(y))<(e))


/**
  @brief Saturating increment operator.

  @details Saturation is only necessary on 32-bit machines, where the
  reference count is only 16-bit wide.

  @sideeffect none

  @see cuddSatDec

*/
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
#define cuddSatInc(x) ((x)++)
#else
#define cuddSatInc(x) ((x) += (x) != (DdHalfWord)DD_MAXREF)
#endif


/**
  @brief Saturating decrement operator.

  @details Saturation is only necessary on 32-bit machines, where the
  reference count is only 16-bit wide.

  @sideeffect none

  @see cuddSatInc

*/
#if SIZEOF_VOID_P == 8 && SIZEOF_INT == 4
#define cuddSatDec(x) ((x)--)
#else
#define cuddSatDec(x) ((x) -= (x) != (DdHalfWord)DD_MAXREF)
#endif


/**
  @brief Returns the constant 1 node.

  @sideeffect none

  @see DD_ZERO DD_PLUS_INFINITY DD_MINUS_INFINITY

*/
#define DD_ONE(dd)		((dd)->one)


/**
  @brief Returns the arithmetic 0 constant node.

  @details This is different from the logical zero. The latter is
  obtained by Cudd_Not(DD_ONE(dd)).

  @sideeffect none

  @see DD_ONE Cudd_Not DD_PLUS_INFINITY DD_MINUS_INFINITY

*/
#define DD_ZERO(dd) ((dd)->zero)


/**
  @brief Returns the plus infinity constant node.

  @sideeffect none

  @see DD_ONE DD_ZERO DD_MINUS_INFINITY

*/
#define DD_PLUS_INFINITY(dd) ((dd)->plusinfinity)


/**
  @brief Returns the minus infinity constant node.

  @sideeffect none

  @see DD_ONE DD_ZERO DD_PLUS_INFINITY

*/
#define DD_MINUS_INFINITY(dd) ((dd)->minusinfinity)


/**
  @brief Enforces DD_MINUS_INF_VAL <= x <= DD_PLUS_INF_VAL.

  @details Furthermore, if x <= DD_MINUS_INF_VAL/2, x is set to
  DD_MINUS_INF_VAL. Similarly, if DD_PLUS_INF_VAL/2 <= x, x is set to
  DD_PLUS_INF_VAL.  Normally this macro is a NOOP. However, if
  HAVE_IEEE_754 is not defined, it makes sure that a value does not
  get larger than infinity in absolute value, and once it gets to
  infinity, stays there.  If the value overflows before this macro is
  applied, no recovery is possible.

  @sideeffect none

*/
#ifdef HAVE_IEEE_754
#define cuddAdjust(x)
#else
#define cuddAdjust(x)		((x) = ((x) >= DD_CRI_HI_MARK) ? DD_PLUS_INF_VAL : (((x) <= DD_CRI_LO_MARK) ? DD_MINUS_INF_VAL : (x)))
#endif


/**
  @brief Outputs a line of stats.

  @details Outputs a line of stats if DD_COUNT and DD_STATS are
  defined. Increments the number of recursive calls if DD_COUNT is
  defined.

  @sideeffect None

*/
#ifdef DD_COUNT
#ifdef DD_STATS
#define statLine(dd)                                                    \
    do {                                                                \
        (dd)->recursiveCalls++;                                         \
        if ((dd)->recursiveCalls == (dd)->nextSample) {                 \
            (void) fprintf((dd)->err,                                   \
                           "@%.0f: %u nodes %u live %.0f dropped"       \
                           " %.0f reclaimed\n",                         \
                           (dd)->recursiveCalls, (dd)->keys,            \
                           (dd)->keys - (dd)->dead,                     \
                           (dd)->nodesDropped, (dd)->reclaimed);        \
            (dd)->nextSample += 250000;}                                \
    } while (0)
#else
#define statLine(dd) (dd)->recursiveCalls++
#endif
#else
#define statLine(dd)
#endif


/**
  @brief Checks for termination or timeout.
*/
#define checkWhetherToGiveUp(dd)                                        \
    do {                                                                \
        if (((int64_t) CUDD_CHECK_MASK & (int64_t) (dd)->cacheMisses) == 0) { \
            if ((dd)->terminationCallback != NULL &&                    \
                (dd)->terminationCallback((dd)->tcbArg)) {              \
                (dd)->errorCode = CUDD_TERMINATION;                     \
                return(NULL);                                           \
            }                                                           \
            if (util_cpu_time() - (dd)->startTime > (dd)->timeLimit) {  \
                (dd)->errorCode = CUDD_TIMEOUT_EXPIRED;                 \
                return(NULL);                                           \
            }                                                           \
        }                                                               \
    } while (0)


/** \cond */

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern DdNode * cuddAddExistAbstractRecur(DdManager *manager, DdNode *f, DdNode *cube);
extern DdNode * cuddAddUnivAbstractRecur(DdManager *manager, DdNode *f, DdNode *cube);
extern DdNode * cuddAddOrAbstractRecur(DdManager *manager, DdNode *f, DdNode *cube);
extern DdNode * cuddAddApplyRecur(DdManager *dd, DdNode * (*)(DdManager *, DdNode **, DdNode **), DdNode *f, DdNode *g);
extern DdNode * cuddAddMonadicApplyRecur(DdManager * dd, DdNode * (*op)(DdManager *, DdNode *), DdNode * f);
extern DdNode * cuddAddScalarInverseRecur(DdManager *dd, DdNode *f, DdNode *epsilon);
extern DdNode * cuddAddIteRecur(DdManager *dd, DdNode *f, DdNode *g, DdNode *h);
extern DdNode * cuddAddCmplRecur(DdManager *dd, DdNode *f);
extern DdNode * cuddAddNegateRecur(DdManager *dd, DdNode *f);
extern DdNode * cuddAddRoundOffRecur(DdManager *dd, DdNode *f, double trunc);
extern DdNode * cuddUnderApprox(DdManager *dd, DdNode *f, int numVars, int threshold, int safe, double quality);
extern DdNode * cuddRemapUnderApprox(DdManager *dd, DdNode *f, int numVars, int threshold, double quality);
extern DdNode * cuddBiasedUnderApprox(DdManager *dd, DdNode *f, DdNode *b, int numVars, int threshold, double quality1, double quality0);
extern DdNode * cuddBddAndAbstractRecur(DdManager *manager, DdNode *f, DdNode *g, DdNode *cube);
extern int cuddAnnealing(DdManager *table, int lower, int upper);
extern DdNode * cuddBddExistAbstractRecur(DdManager *manager, DdNode *f, DdNode *cube);
extern DdNode * cuddBddXorExistAbstractRecur(DdManager *manager, DdNode *f, DdNode *g, DdNode *cube);
extern DdNode * cuddBddBooleanDiffRecur(DdManager *manager, DdNode *f, DdNode *var);
extern DdNode * cuddBddIteRecur(DdManager *dd, DdNode *f, DdNode *g, DdNode *h);
extern DdNode * cuddBddIntersectRecur(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddBddAndRecur(DdManager *manager, DdNode *f, DdNode *g);
extern DdNode * cuddBddXorRecur(DdManager *manager, DdNode *f, DdNode *g);
extern DdNode * cuddBddTransfer(DdManager *ddS, DdManager *ddD, DdNode *f);
extern DdNode * cuddAddBddDoPattern(DdManager *dd, DdNode *f);
extern int cuddInitCache(DdManager *unique, unsigned int cacheSize, unsigned int maxCacheSize);
extern void cuddCacheInsert(DdManager *table, ptruint op, DdNode *f, DdNode *g, DdNode *h, DdNode *data);
extern void cuddCacheInsert2(DdManager *table, DdNode * (*)(DdManager *, DdNode *, DdNode *), DdNode *f, DdNode *g, DdNode *data);
extern void cuddCacheInsert1(DdManager *table, DdNode * (*)(DdManager *, DdNode *), DdNode *f, DdNode *data);
extern DdNode * cuddCacheLookup(DdManager *table, ptruint op, DdNode *f, DdNode *g, DdNode *h);
extern DdNode * cuddCacheLookupZdd(DdManager *table, ptruint op, DdNode *f, DdNode *g, DdNode *h);
extern DdNode * cuddCacheLookup2(DdManager *table, DdNode * (*)(DdManager *, DdNode *, DdNode *), DdNode *f, DdNode *g);
extern DdNode * cuddCacheLookup1(DdManager *table, DdNode * (*)(DdManager *, DdNode *), DdNode *f);
extern DdNode * cuddCacheLookup2Zdd(DdManager *table, DdNode * (*)(DdManager *, DdNode *, DdNode *), DdNode *f, DdNode *g);
extern DdNode * cuddCacheLookup1Zdd(DdManager *table, DdNode * (*)(DdManager *, DdNode *), DdNode *f);
extern DdNode * cuddConstantLookup(DdManager *table, ptruint op, DdNode *f, DdNode *g, DdNode *h);
extern int cuddCacheProfile(DdManager *table, FILE *fp);
extern void cuddCacheResize(DdManager *table);
extern void cuddCacheFlush(DdManager *table);
extern int cuddComputeFloorLog2(unsigned int value);
extern int cuddHeapProfile(DdManager *dd);
extern void cuddPrintNode(DdNode *f, FILE *fp);
extern void cuddPrintVarGroups(DdManager * dd, MtrNode * root, int zdd, int silent);
extern DdNode * cuddBddClippingAnd(DdManager *dd, DdNode *f, DdNode *g, int maxDepth, int direction);
extern DdNode * cuddBddClippingAndAbstract(DdManager *dd, DdNode *f, DdNode *g, DdNode *cube, int maxDepth, int direction);
extern void cuddGetBranches(DdNode *g, DdNode **g1, DdNode **g0);
extern DdNode * cuddCofactorRecur(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddBddComposeRecur(DdManager *dd, DdNode *f, DdNode *g, DdNode *proj);
extern DdNode * cuddAddComposeRecur(DdManager *dd, DdNode *f, DdNode *g, DdNode *proj);
extern int cuddExact(DdManager *table, int lower, int upper);
extern DdNode * cuddBddConstrainRecur(DdManager *dd, DdNode *f, DdNode *c);
extern DdNode * cuddBddRestrictRecur(DdManager *dd, DdNode *f, DdNode *c);
extern DdNode * cuddBddNPAndRecur(DdManager *dd, DdNode *f, DdNode *c);
extern DdNode * cuddAddConstrainRecur(DdManager *dd, DdNode *f, DdNode *c);
extern DdNode * cuddAddRestrictRecur(DdManager *dd, DdNode *f, DdNode *c);
extern DdNode * cuddBddLICompaction(DdManager *dd, DdNode *f, DdNode *c);
extern int cuddGa(DdManager *table, int lower, int upper);
extern int cuddTreeSifting(DdManager *table, Cudd_ReorderingType method);
extern int cuddZddInitUniv(DdManager *zdd);
extern void cuddZddFreeUniv(DdManager *zdd);
extern void cuddSetInteract(DdManager *table, int x, int y);
extern int cuddTestInteract(DdManager *table, int x, int y);
extern int cuddInitInteract(DdManager *table);
extern DdLocalCache * cuddLocalCacheInit(DdManager *manager, unsigned int keySize, unsigned int cacheSize, unsigned int maxCacheSize);
extern void cuddLocalCacheQuit(DdLocalCache *cache);
extern void cuddLocalCacheInsert(DdLocalCache *cache, DdNodePtr *key, DdNode *value);
extern DdNode * cuddLocalCacheLookup(DdLocalCache *cache, DdNodePtr *key);
extern void cuddLocalCacheClearDead(DdManager *manager);
extern int cuddIsInDeathRow(DdManager *dd, DdNode *f);
extern int cuddTimesInDeathRow(DdManager *dd, DdNode *f);
extern void cuddLocalCacheClearAll(DdManager *manager);
#ifdef DD_CACHE_PROFILE
extern int cuddLocalCacheProfile(DdLocalCache *cache);
#endif
extern DdHashTable * cuddHashTableInit(DdManager *manager, unsigned int keySize, unsigned int initSize);
extern void cuddHashTableQuit(DdHashTable *hash);
extern void cuddHashTableGenericQuit(DdHashTable *hash);
extern int cuddHashTableInsert(DdHashTable *hash, DdNodePtr *key, DdNode *value, ptrint count);
extern DdNode * cuddHashTableLookup(DdHashTable *hash, DdNodePtr *key);
extern int cuddHashTableInsert1(DdHashTable *hash, DdNode *f, DdNode *value, ptrint count);
extern DdNode * cuddHashTableLookup1(DdHashTable *hash, DdNode *f);
extern int cuddHashTableInsert2(DdHashTable *hash, DdNode *f, DdNode *g, DdNode *value, ptrint count);
extern DdNode * cuddHashTableLookup2(DdHashTable *hash, DdNode *f, DdNode *g);
extern int cuddHashTableInsert3(DdHashTable *hash, DdNode *f, DdNode *g, DdNode *h, DdNode *value, ptrint count);
extern DdNode * cuddHashTableLookup3(DdHashTable *hash, DdNode *f, DdNode *g, DdNode *h);
extern int cuddHashTableGenericInsert(DdHashTable * hash, DdNode * f, void * value);
extern void * cuddHashTableGenericLookup(DdHashTable * hash, DdNode * f);
extern DdLevelQueue * cuddLevelQueueInit(int levels, int itemSize, int numBuckets, DdManager * manager);
extern void cuddLevelQueueQuit(DdLevelQueue *queue);
extern void * cuddLevelQueueFirst(DdLevelQueue * queue, void * key, int  level);
extern void * cuddLevelQueueEnqueue(DdLevelQueue *queue, void *key, int level);
extern void cuddLevelQueueDequeue(DdLevelQueue *queue, int level);
extern int cuddLinearAndSifting(DdManager *table, int lower, int upper);
extern int cuddLinearInPlace(DdManager * table, int  x, int  y);
extern void cuddUpdateInteractionMatrix(DdManager * table, int  xindex, int  yindex);
extern int cuddInitLinear(DdManager *table);
extern int cuddResizeLinear(DdManager *table);
extern DdNode * cuddBddLiteralSetIntersectionRecur(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddCProjectionRecur(DdManager *dd, DdNode *R, DdNode *Y, DdNode *Ysupp);
extern DdNode * cuddBddClosestCube(DdManager *dd, DdNode *f, DdNode *g, CUDD_VALUE_TYPE bound);
extern void cuddReclaim(DdManager *table, DdNode *n);
extern void cuddReclaimZdd(DdManager *table, DdNode *n);
extern void cuddClearDeathRow(DdManager *table);
extern void cuddShrinkDeathRow(DdManager *table);
extern DdNode * cuddDynamicAllocNode(DdManager *table);
extern int cuddSifting(DdManager *table, int lower, int upper);
extern int cuddSwapping(DdManager *table, int lower, int upper, Cudd_ReorderingType heuristic);
extern int cuddNextHigh(DdManager *table, int x);
extern int cuddNextLow(DdManager *table, int x);
extern int cuddSwapInPlace(DdManager *table, int x, int y);
extern int cuddBddAlignToZdd(DdManager *table);
extern DdNode * cuddBddMakePrime(DdManager *dd, DdNode *cube, DdNode *f);
extern DdNode * cuddSolveEqnRecur(DdManager *bdd, DdNode *F, DdNode *Y, DdNode **G, int n, int *yIndex, int i);
extern DdNode * cuddVerifySol(DdManager *bdd, DdNode *F, DdNode **G, int *yIndex, int n);
#ifdef ST_H_
extern DdNode* cuddSplitSetRecur(DdManager *manager, st_table *mtable, int *varSeen, DdNode *p, double n, double max, int index);
#endif
extern DdNode * cuddSubsetHeavyBranch(DdManager *dd, DdNode *f, int numVars, int threshold);
extern DdNode * cuddSubsetShortPaths(DdManager *dd, DdNode *f, int numVars, int threshold, int hardlimit);
extern int cuddSymmCheck(DdManager *table, int x, int y);
extern int cuddSymmSifting(DdManager *table, int lower, int upper);
extern int cuddSymmSiftingConv(DdManager *table, int lower, int upper);
extern DdNode * cuddAllocNode(DdManager *unique);
extern DdManager * cuddInitTable(unsigned int numVars, unsigned int numVarsZ, unsigned int numSlots, unsigned int looseUpTo);
extern void cuddFreeTable(DdManager *unique);
extern int cuddGarbageCollect(DdManager *unique, int clearCache);
extern DdNode * cuddZddGetNode(DdManager *zdd, int id, DdNode *T, DdNode *E);
extern DdNode * cuddZddGetNodeIVO(DdManager *dd, int index, DdNode *g, DdNode *h);
extern DdNode * cuddUniqueInter(DdManager *unique, int index, DdNode *T, DdNode *E);
extern DdNode * cuddUniqueInterIVO(DdManager *unique, int index, DdNode *T, DdNode *E);
extern DdNode * cuddUniqueInterZdd(DdManager *unique, int index, DdNode *T, DdNode *E);
extern DdNode * cuddUniqueConst(DdManager *unique, CUDD_VALUE_TYPE value);
extern void cuddRehash(DdManager *unique, int i);
extern void cuddShrinkSubtable(DdManager *unique, int i);
extern int cuddInsertSubtables(DdManager *unique, int n, int level);
extern int cuddDestroySubtables(DdManager *unique, int n);
extern int cuddResizeTableZdd(DdManager *unique, int index);
extern void cuddSlowTableGrowth(DdManager *unique);
extern int cuddP(DdManager *dd, DdNode *f);
#ifdef ST_H_
extern enum st_retval cuddStCountfree(void *key, void *value, void *arg);
extern int cuddCollectNodes(DdNode *f, st_table *visited);
#endif
extern DdNodePtr * cuddNodeArray(DdNode *f, int *n);
extern int cuddWindowReorder(DdManager *table, int low, int high, Cudd_ReorderingType submethod);
extern DdNode * cuddZddProduct(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddZddUnateProduct(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddZddWeakDiv(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddZddWeakDivF(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddZddDivide(DdManager *dd, DdNode *f, DdNode *g);
extern DdNode * cuddZddDivideF(DdManager *dd, DdNode *f, DdNode *g);
extern int cuddZddGetCofactors3(DdManager *dd, DdNode *f, int v, DdNode **f1, DdNode **f0, DdNode **fd);
extern int cuddZddGetCofactors2(DdManager *dd, DdNode *f, int v, DdNode **f1, DdNode **f0);
extern DdNode * cuddZddComplement(DdManager *dd, DdNode *node);
extern int cuddZddGetPosVarIndex(DdManager * dd, int index);
extern int cuddZddGetNegVarIndex(DdManager * dd, int index);
extern int cuddZddGetPosVarLevel(DdManager * dd, int index);
extern int cuddZddGetNegVarLevel(DdManager * dd, int index);
extern int cuddZddTreeSifting(DdManager *table, Cudd_ReorderingType method);
extern DdNode * cuddZddIsop(DdManager *dd, DdNode *L, DdNode *U, DdNode **zdd_I);
extern DdNode * cuddBddIsop(DdManager *dd, DdNode *L, DdNode *U);
extern DdNode * cuddMakeBddFromZddCover(DdManager *dd, DdNode *node);
extern int cuddZddLinearSifting(DdManager *table, int lower, int upper);
extern int cuddZddAlignToBdd(DdManager *table);
extern int cuddZddNextHigh(DdManager *table, int x);
extern int cuddZddNextLow(DdManager *table, int x);
extern int cuddZddUniqueCompare(void const *ptr_x, void const *ptr_y);
extern int cuddZddSwapInPlace(DdManager *table, int x, int y);
extern int cuddZddSwapping(DdManager *table, int lower, int upper, Cudd_ReorderingType heuristic);
extern int cuddZddSifting(DdManager *table, int lower, int upper);
extern DdNode * cuddZddIte(DdManager *dd, DdNode *f, DdNode *g, DdNode *h);
extern DdNode * cuddZddUnion(DdManager *zdd, DdNode *P, DdNode *Q);
extern DdNode * cuddZddIntersect(DdManager *zdd, DdNode *P, DdNode *Q);
extern DdNode * cuddZddDiff(DdManager *zdd, DdNode *P, DdNode *Q);
extern DdNode * cuddZddChangeAux(DdManager *zdd, DdNode *P, DdNode *zvar);
extern DdNode * cuddZddSubset1(DdManager *dd, DdNode *P, int var);
extern DdNode * cuddZddSubset0(DdManager *dd, DdNode *P, int var);
extern DdNode * cuddZddChange(DdManager *dd, DdNode *P, int var);
extern int cuddZddSymmCheck(DdManager *table, int x, int y);
extern int cuddZddSymmSifting(DdManager *table, int lower, int upper);
extern int cuddZddSymmSiftingConv(DdManager *table, int lower, int upper);
extern int cuddZddP(DdManager *zdd, DdNode *f);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

/** \endcond */

#endif /* CUDD_INT_H_ */
