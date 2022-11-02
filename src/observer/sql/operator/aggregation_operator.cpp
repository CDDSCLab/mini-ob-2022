//
// Created by Moon on 2022/10/25.
//

#include "aggregation_operator.h"

RC AggregationOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("aggregation operator must has one child");
    return RC::INTERNAL;
  }

  RC rc = children_[0]->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  Operator *oper = children_[0];
  while (RC::SUCCESS == (rc = oper->next())) {
    hash_table_.insert_combine(make_aggregate_key(oper->current_tuple()), make_aggregate_value(oper->current_tuple()));
  }
  if (rc != RECORD_EOF) {
    return rc;
  }
  hash_table_iter_ = hash_table_.Begin();
  return RC::SUCCESS;
}

RC AggregationOperator::next()
{
  RC rc = RC::SUCCESS;
  if (!init_) {
    init_ = true;
  } else {
    ++hash_table_iter_;
  }
  // TODO(yueyang): implement having
  if (hash_table_iter_ == hash_table_.End()) {
    return RC::RECORD_EOF;
  }
  for (int i = 0; i < aggregate_field_.size(); ++i) {

    if (hash_table_iter_.Value().count <= hash_table_iter_.Value().null_counts[i]) {
      if (aggregate_field_[i].aggr_type() == AGGR_COUNT) {
      } else {
        const_cast<TupleCell *>(&(hash_table_iter_.Value().aggregates_[i]))->set_type(AttrType::NULLS);
      }
    } else {
      if (aggregate_field_[i].aggr_type() == AGGR_AVG) {
        float data = *(float *)hash_table_iter_.Value().aggregates_[i].data();
        data /= (hash_table_iter_.Value().count - hash_table_iter_.Value().null_counts[i]);
        memcpy((void *)hash_table_iter_.Value().aggregates_[i].data(), &data, sizeof(data));
      }
    }
  }
  tuple_.set_data(hash_table_iter_.Key().group_bys_, hash_table_iter_.Value().aggregates_);
  return rc;
}

RC AggregationOperator::close()
{
  if (children_.size() != 1) {
    LOG_WARN("aggregation operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->close();
}

Tuple *AggregationOperator::current_tuple()
{
  if (hash_table_iter_ == hash_table_.End()) {
    return nullptr;
  }
  return &tuple_;
}
