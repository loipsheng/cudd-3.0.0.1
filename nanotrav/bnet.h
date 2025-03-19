/**
  @file 

  @ingroup nanotrav

  @brief Simple-minded package to read a blif file.

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

#ifndef _BNET
#define _BNET

/*---------------------------------------------------------------------------*/
/* Nested includes                                                           */
/*---------------------------------------------------------------------------*/

#include "util.h"
#include "st.h"
#include "cudd.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

/* Different types of nodes. (Used in the "BnetNode" type.) */
#define BNET_CONSTANT_NODE 0
#define BNET_INPUT_NODE 1
#define BNET_PRESENT_STATE_NODE 2
#define BNET_INTERNAL_NODE 3
#define BNET_OUTPUT_NODE 4
#define BNET_NEXT_STATE_NODE 5

/* Type of DD of a node. */
#define BNET_LOCAL_DD 0
#define BNET_GLOBAL_DD 1


/*---------------------------------------------------------------------------*/
/* Stucture declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/* The following types implement a very simple data structure for a boolean
** network. The intent is to be able to read a minimal subset of the blif
** format in a data structure from which it's easy to build DDs for the
** circuit.以下类型用于实现一个非常简单的数据结构来表示布尔网络。
目的是能够读取 BLIF 格式的一个最小子集，并将其存储在一个数据结构中，便于为电路构建决策图（DD）。*/

/**
 ** @brief Type to store a line of the truth table of a node.
 **
 ** @details The entire truth table implemented as a linked list of
 ** objects of this type.
 */
typedef struct BnetTabline {
    char *values;		/**< string of 1, 0, and - */
    struct BnetTabline *next;	/**< pointer to next table line */
} BnetTabline;

/**
 **  @brief Node of the boolean network.        BnetNode 结构体：布尔网络中的节点
 **
 ** @details There is one node in the network for each primary input     在网络中，每个 主输入（primary input） 或 .names 指令定义的逻辑门都会对应一个 BnetNode 结构体。
 ** and for each .names directive. This structure has a field to point
 ** to the DD of the node function. The function may be either in       该结构体包含一个字段 指向该节点的决策图（DD）。
 ** terms of primary inputs, or it may be in terms of the local
 ** inputs. The latter implies that each node has a variable index
 ** associated to it at some point in time. The field "var" stores
 ** that variable index, and "active" says if the association is
 ** currently valid.  (It is indeed possible for an index to be
 ** associated to different nodes at different times.)
 */
typedef struct BnetNode {
    char *name;		/**< name of the output signal */
    int type;		/**< input, internal, constant, ... */
    int ninp;		/**< number of inputs to the node                   该节点的 输入数*/
    int nfo;		/**< number of fanout nodes for this node           该节点的 输出节点数*/
    char **inputs;	/**< input names                                    输入信号的名称*/
    BnetTabline *f;	/**< truth table for this node                      该节点的 真值表（以 BnetTabline 形式存储）*/
    int polarity;	/**< f is the onset (0) or the offset (1) */
    int active;		/**< node has variable associated to it (1) or not (0) */
    int var;		/**< %DD variable index associated to this node     该节点对应的 BDD 变量索引*/
    DdNode *dd;		/**< decision diagram for the function of this node */
    int exdc_flag;	/**< whether an exdc node or not */
    struct BnetNode *exdc; /**< pointer to exdc of dd node */
    int count;		/**< auxiliary field for %DD dropping */
    int level;		/**< maximum distance from the inputs               该节点 到输入端的最大距离（用于排序）*/
    int visited;	/**< flag for search */
    struct BnetNode *next; /**< pointer to implement the linked list of nodes   指向 下一个 BnetNode，构成 链表*/
} BnetNode;

/**
 ** @brief Very simple boolean network data structure.  BnetNetwork 结构体：布尔网络的整体数据结构
 */
typedef struct BnetNetwork {
    char *name;		/**< network name: from the .model directive            网络名称（来自 .model 指令）*/
    int npis;		/**< number of primary inputs                           主输入数（来自 .inputs 指令）*/
    int ninputs;	/**< number of inputs                                   输入数*/
    char **inputs;	/**< primary input names: from the .inputs directive    主输入名称*/
    int npos;		/**< number of primary outputs                          主输出数*/
    int noutputs;	/**< number of outputs                                  输出数*/
    char **outputs;	/**< primary output names: from the .outputs directive  主输出名称*/
    int nlatches;	/**< number of latches                                  触发器（latches）数量*/
    char ***latches;	/**< next state names: from the .latch directives   触发器名称（来自 .latch 指令）*/
    BnetNode *nodes;	/**< linked list of the nodes                       布尔网络中的节点链表*/
    st_table *hash;	/**< symbol table to access nodes by name               符号表（用于按名称查找 BnetNode）*/
    char *slope;	/**< wire_load_slope */
} BnetNetwork;

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/

#ifndef TRUE
#   define TRUE 1
#endif
#ifndef FALSE
#   define FALSE 0
#endif

/** \cond */

/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

extern BnetNetwork * Bnet_ReadNetwork (FILE *fp, int pr);
extern void Bnet_PrintNetwork (BnetNetwork *net);
extern void Bnet_FreeNetwork (BnetNetwork *net);
extern int Bnet_BuildNodeBDD (DdManager *dd, BnetNode *nd, st_table *hash, int params, int nodrop);
extern int Bnet_DfsVariableOrder (DdManager *dd, BnetNetwork *net);
extern int Bnet_bddDump (DdManager *dd, BnetNetwork *network, char *dfile, int dumpFmt, int reencoded);
extern int Bnet_bddArrayDump (DdManager *dd, BnetNetwork *network, char *dfile, DdNode **outputs, char **onames, int noutputs, int dumpFmt);
extern int Bnet_ReadOrder (DdManager *dd, char *ordFile, BnetNetwork *net, int locGlob, int nodrop);
extern int Bnet_PrintOrder (BnetNetwork * net, DdManager *dd);

/** \endcond */


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* _BNET */
