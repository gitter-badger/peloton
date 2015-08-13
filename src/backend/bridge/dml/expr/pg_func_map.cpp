
#include "backend/bridge/dml/expr/pg_func_map.h"

namespace peloton {
namespace bridge {


/**
 * @brief Mapping PG Function Id to Peloton Function Meta Info.
 */
std::unordered_map<Oid, const PltFuncMetaInfo> kPgFuncMap({

    //====--------------------------------
    // Relational comparison
    //====--------------------------------
    {63, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },
    {65, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },
    {67, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },
    {158, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },
    {159, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },
    {287, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },
    {293, { EXPRESSION_TYPE_COMPARE_EQ, 2 } },

    {84, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {144, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {145, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {157, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {164, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {165, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {288, { EXPRESSION_TYPE_COMPARE_NE, 2 } },
    {294, { EXPRESSION_TYPE_COMPARE_NE, 2 } },

    {56, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {64, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {66, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {160, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {161, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {1246, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {289, { EXPRESSION_TYPE_COMPARE_LT, 2 } },
    {295, { EXPRESSION_TYPE_COMPARE_LT, 2 } },

    {57, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {73, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {146, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {147, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {162, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {163, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {291, { EXPRESSION_TYPE_COMPARE_GT, 2 } },
    {297, { EXPRESSION_TYPE_COMPARE_GT, 2 } },

    {74, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {150, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {151, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {168, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {169, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {1692, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {292, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },
    {298, { EXPRESSION_TYPE_COMPARE_GTE, 2 } },

    {72, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {148, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {149, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {166, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {167, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {1691, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {290, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },
    {296, { EXPRESSION_TYPE_COMPARE_LTE, 2 } },

    //====--------------------------------
    // Basic arithmetics
    //====--------------------------------
    {176, { EXPRESSION_TYPE_OPERATOR_PLUS, 2 } },
    {177, { EXPRESSION_TYPE_OPERATOR_PLUS, 2 } },
    {178, { EXPRESSION_TYPE_OPERATOR_PLUS, 2 } },
    {179, { EXPRESSION_TYPE_OPERATOR_PLUS, 2 } },
    {204, { EXPRESSION_TYPE_OPERATOR_PLUS, 2 } },
    {218, { EXPRESSION_TYPE_OPERATOR_PLUS, 2 } },

    {180, { EXPRESSION_TYPE_OPERATOR_MINUS, 2 } },
    {181, { EXPRESSION_TYPE_OPERATOR_MINUS, 2 } },
    {182, { EXPRESSION_TYPE_OPERATOR_MINUS, 2 } },
    {183, { EXPRESSION_TYPE_OPERATOR_MINUS, 2 } },
    {205, { EXPRESSION_TYPE_OPERATOR_MINUS, 2 } },
    {219, { EXPRESSION_TYPE_OPERATOR_MINUS, 2 } },

    {141, { EXPRESSION_TYPE_OPERATOR_MULTIPLY, 2 } },
    {152, { EXPRESSION_TYPE_OPERATOR_MULTIPLY, 2 } },
    {170, { EXPRESSION_TYPE_OPERATOR_MULTIPLY, 2 } },
    {171, { EXPRESSION_TYPE_OPERATOR_MULTIPLY, 2 } },
    {202, { EXPRESSION_TYPE_OPERATOR_MULTIPLY, 2 } },
    {216, { EXPRESSION_TYPE_OPERATOR_MULTIPLY, 2 } },

    {153, { EXPRESSION_TYPE_OPERATOR_DIVIDE, 2 } },
    {154, { EXPRESSION_TYPE_OPERATOR_DIVIDE, 2 } },
    {172, { EXPRESSION_TYPE_OPERATOR_DIVIDE, 2 } },
    {173, { EXPRESSION_TYPE_OPERATOR_DIVIDE, 2 } },
    {203, { EXPRESSION_TYPE_OPERATOR_DIVIDE, 2 } },
    {217, { EXPRESSION_TYPE_OPERATOR_DIVIDE, 2 } }

});

/**
 * @brief Mapping PG transit function to Aggregate types.
 * We have to separate it from kPgFuncMap,
 * because the two maps may have overlapping functions that have
 * different meaning in Peloton.
 * For example, PG Function Id 218 (float8pl) means an PLUS in
 * 'ordinary' expressions,
 * but means a SUM(float) in an aggregation.
 */
std::unordered_map<Oid, const PltFuncMetaInfo> kPgTransitFuncMap({
  //====--------------------------------
  // "Transit function" of Aggregates
  //====--------------------------------
  { 768, { EXPRESSION_TYPE_AGGREGATE_MAX, 1} },
  { 770, { EXPRESSION_TYPE_AGGREGATE_MAX, 1} },
  { 223, { EXPRESSION_TYPE_AGGREGATE_MAX, 1} },

  { 769, { EXPRESSION_TYPE_AGGREGATE_MIN, 1} },
  { 771, { EXPRESSION_TYPE_AGGREGATE_MIN, 1} },
  { 224, { EXPRESSION_TYPE_AGGREGATE_MIN, 1} },

  { 1840, { EXPRESSION_TYPE_AGGREGATE_SUM, 1} },
  { 1841, { EXPRESSION_TYPE_AGGREGATE_SUM, 1} },
  { 1842, { EXPRESSION_TYPE_AGGREGATE_SUM, 1} },
  { 218,  { EXPRESSION_TYPE_AGGREGATE_SUM, 1} },

  { 222,  {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },
  { 1834, {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },
  { 1835, {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },
  { 1836, {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },
  { 1833, {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },
  { 1962, {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },
  { 1963, {EXPRESSION_TYPE_AGGREGATE_AVG,  1} },

  {1219,  {EXPRESSION_TYPE_AGGREGATE_COUNT, 1} },
  {2804,  {EXPRESSION_TYPE_AGGREGATE_COUNT, 1} }

});


}
}
