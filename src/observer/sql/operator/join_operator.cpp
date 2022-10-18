//
// Created by LiuJibo on 2022/10/18.
//

#include "sql/operator/join_operator.h"
#include "storage/common/table.h"
#include "rc.h"

RC JoinOperator::open()
{
  RC rc;
  rc = left_->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open left child operator: %s", strrc(rc));
    return rc;
  }

  rc = right_->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open right child operator: %s", strrc(rc));
    return rc;
  }

  // 先试一试全部放到内存，主要是没找到如何重置算子，难道是关了再打开就行？
  // while (left_->next() == RC::SUCCESS) {
  //   left_tuples_.emplace_back(left_->current_tuple());
  // }

  // while (right_->next() == RC::SUCCESS) {
  //   right_tuples_.emplace_back(right_->current_tuple());
  // }

  return RC::SUCCESS;
};

RC JoinOperator::next()
{
  RC rc = RC::SUCCESS;
  if (round_done_) {
    rc = left_->next();
    round_done_ = false;
  }
  if (rc != RC::SUCCESS) {
    return RC::RECORD_EOF;
  }
  RC b = right_->next();
  if (b != RC::SUCCESS) {
    rc = left_->next();
    right_->close();
    right_->open();
    b = right_->next();
    if (rc != RC::SUCCESS || b != RC::SUCCESS) {
      return RC::RECORD_EOF;
    }
  }

  // do join to create joined_tuple_
  do_join(left_->current_tuple(), right_->current_tuple());
  return RC::SUCCESS;
};

// TODO: 将两个tuple合并为一个tuple，参考project_operator
// TupleCellSpec, FieldExpr, Field, TupleCell, Tuple
bool JoinOperator::do_join(Tuple *left, Tuple *right)
{
  joined_tuple_.set_tuple(left, right, left_is_row_);
}

Tuple *JoinOperator::current_tuple()
{
  return &joined_tuple_;
}

RC JoinOperator::close()
{
  RC rc;
  rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left child operator: %s", strrc(rc));
    return rc;
  }

  rc = right_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close right child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
};
