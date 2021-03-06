/*-------------------------------------------------------------------------
 *
 * nodeRecursiveunion.h
 *
 *
 *
 * Portions Copyright (c) 1996-2015, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/executor/nodeRecursiveunion.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef NODERECURSIVEUNION_H
#define NODERECURSIVEUNION_H

#include "parser/nodes/execnodes.h"

extern RecursiveUnionState *ExecInitRecursiveUnion(RecursiveUnion *node, EState *estate, int eflags);
extern TupleTableSlot *ExecRecursiveUnion(RecursiveUnionState *node);
extern void ExecEndRecursiveUnion(RecursiveUnionState *node);
extern void ExecReScanRecursiveUnion(RecursiveUnionState *node);

#endif   /* NODERECURSIVEUNION_H */
