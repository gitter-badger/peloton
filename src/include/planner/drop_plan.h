//===----------------------------------------------------------------------===//
//
//                         PelotonDB
//
// drop_plan.h
//
// Identification: /peloton/src/include/planner/drop_plan.h
//
// Copyright (c) 2015, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include "planner/abstract_plan.h"

namespace peloton {
namespace storage {
class DataTable;
}
namespace parser {
class DropParse;
}
namespace catalog {
class Schema;
}

namespace planner {
class DropPlan : public AbstractPlan {
 public:

  DropPlan() = delete;
  DropPlan(const DropPlan &) = delete;
  DropPlan &operator=(const DropPlan &) = delete;
  DropPlan(DropPlan &&) = delete;
  DropPlan &operator=(DropPlan &&) = delete;

  explicit DropPlan(storage::DataTable *table);

  explicit DropPlan(std::string name);

  explicit DropPlan(parser::DropParse *parse_tree);

  inline PlanNodeType GetPlanNodeType() const {
    return PLAN_NODE_TYPE_DROP;
  }

  const std::string GetInfo() const {
    std::string returned_string = "DropPlan:\n";
	returned_string += "\tTable name: " + table_name + "\n";
    return returned_string;
  }

  std::unique_ptr<AbstractPlan> Copy() const {
    return std::unique_ptr<AbstractPlan>(new DropPlan(target_table_));
  }

  std::string GetTableName() const { return table_name; }

  bool IsMissing() const { return missing; }

 private:
  // Target Table
  storage::DataTable *target_table_ = nullptr;
  std::string table_name;
  bool missing;

};
}
}
