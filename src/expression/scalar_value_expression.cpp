//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// scalar_value_expression.cpp
//
// Identification: src/expression/scalar_value_expression.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "expression/scalar_value_expression.h"
#include "common/value_peeker.h"
#include "common/value.h"
#include "storage/tuple.h"
#include "storage/data_table.h"

namespace peloton {
namespace expression {

Value ScalarValueExpression::Evaluate(
    const AbstractTuple *tuple1, const AbstractTuple *tuple2,
    executor::ExecutorContext *context) const {
  // Execute the subquery and.Get its subquery id
  PL_ASSERT(m_left != NULL);
  Value lnv = m_left->Evaluate(tuple1, tuple2, context);

  // TODO: Get the subquery context
  // int subqueryId = ValuePeeker::PeekInteger(lnv);
  /*
  Table* table = context->GetSubqueryOutputTable(subqueryId);
  PL_ASSERT(table != NULL);
  if (table->activeTupleCount() > 1) {
      // throw runtime exception
      char message[256];
      snprintf(message, 256, "More than one row returned by a scalar/row
  subquery");
      throw Exception(message);
  }

  TableIterator& iterator = table->iterator();
  AbstractTuple tuple(table->schema());
  if (iterator.next(tuple)) {
      return tuple.GetValue(0);
  } else {
      return Value::GetNullValue(m_left->GetValueType());
  }
  */

  return lnv;
}

std::string ScalarValueExpression::DebugInfo(const std::string &spacer) const {
  return spacer + "ScalarValueExpression";
}

}  // End expression namespace
}  // End peloton namespace
