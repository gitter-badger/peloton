/*-------------------------------------------------------------------------
 *
 * visibilitymap.h
 *		visibility map interface
 *
 *
 * Portions Copyright (c) 2007-2015, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/access/visibilitymap.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef VISIBILITYMAP_H
#define VISIBILITYMAP_H

#include "parser/access/xlogdefs.h"
#include "parser/storage/block.h"
#include "parser/storage/buf.h"
#include "parser/utils/relcache.h"

extern void visibilitymap_clear(Relation rel, BlockNumber heapBlk,
					Buffer vmbuf);
extern void visibilitymap_pin(Relation rel, BlockNumber heapBlk,
				  Buffer *vmbuf);
extern bool visibilitymap_pin_ok(BlockNumber heapBlk, Buffer vmbuf);
extern void visibilitymap_set(Relation rel, BlockNumber heapBlk, Buffer heapBuf,
				  XLogRecPtr recptr, Buffer vmBuf, TransactionId cutoff_xid);
extern bool visibilitymap_test(Relation rel, BlockNumber heapBlk, Buffer *vmbuf);
extern BlockNumber visibilitymap_count(Relation rel);
extern void visibilitymap_truncate(Relation rel, BlockNumber nheapblocks);

#endif   /* VISIBILITYMAP_H */
