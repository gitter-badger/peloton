//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// index_factory.cpp
//
// Identification: src/index/index_factory.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <iostream>

#include "common/types.h"
#include "common/logger.h"
#include "common/macros.h"
#include "index/index_factory.h"
#include "index/index_key.h"
#include "index/btree_index.h"
#include "index/skip_list_index.h"

namespace peloton {
namespace index {

Index *IndexFactory::GetInstance(IndexMetadata *metadata) {

  LOG_TRACE("Creating index %s", metadata->GetName().c_str());
  const auto key_size = metadata->key_schema->GetLength();
  LOG_INFO("key_size : %d", key_size);

  auto index_type = metadata->GetIndexMethodType();
  LOG_TRACE("Index type : %d", index_type);

  if (index_type == INDEX_TYPE_BTREE) {

    if (key_size <= 4) {
      return new BTreeIndex<GenericKey<4>, ItemPointer *, GenericComparator<4>,
                            GenericEqualityChecker<4>>(metadata);
    } else if (key_size <= 8) {
      return new BTreeIndex<GenericKey<8>, ItemPointer *, GenericComparator<8>,
                            GenericEqualityChecker<8>>(metadata);
    } else if (key_size <= 16) {
      return new BTreeIndex<GenericKey<16>, ItemPointer *,
                            GenericComparator<16>, GenericEqualityChecker<16>>(
          metadata);
    } else if (key_size <= 64) {
      return new BTreeIndex<GenericKey<64>, ItemPointer *,
                            GenericComparator<64>, GenericEqualityChecker<64>>(
          metadata);
    } else if (key_size <= 256) {
      return new BTreeIndex<GenericKey<256>, ItemPointer *,
                            GenericComparator<256>,
                            GenericEqualityChecker<256>>(metadata);
    } else {
      return new BTreeIndex<TupleKey, ItemPointer *, TupleKeyComparator,
                            TupleKeyEqualityChecker>(metadata);
    }
  }

  if (index_type == INDEX_TYPE_SKIPLIST) {

    if (key_size <= 4) {
      return new SkipListIndex<GenericKey<4>, ItemPointer *, GenericComparatorRaw<4>,
                            GenericEqualityChecker<4>>(metadata);
    } else if (key_size <= 8) {
      return new SkipListIndex<GenericKey<8>, ItemPointer *, GenericComparatorRaw<8>,
                            GenericEqualityChecker<8>>(metadata);
    } else if (key_size <= 16) {
      return new SkipListIndex<GenericKey<16>, ItemPointer *,
                            GenericComparatorRaw<16>, GenericEqualityChecker<16>>(
          metadata);
    } else if (key_size <= 64) {
      return new SkipListIndex<GenericKey<64>, ItemPointer *,
                            GenericComparatorRaw<64>, GenericEqualityChecker<64>>(
          metadata);
    } else if (key_size <= 256) {
      return new SkipListIndex<GenericKey<256>, ItemPointer *,
                            GenericComparatorRaw<256>,
                            GenericEqualityChecker<256>>(metadata);
    } else {
      return new SkipListIndex<TupleKey, ItemPointer *, TupleKeyComparatorRaw,
                            TupleKeyEqualityChecker>(metadata);
    }
  }


  throw IndexException("Unsupported index scheme.");
  return NULL;
}

}  // End index namespace
}  // End peloton namespace
