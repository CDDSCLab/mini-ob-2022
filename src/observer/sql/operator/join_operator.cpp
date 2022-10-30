//
// Created by LiuJibo on 2022/10/18.
//

#include "sql/operator/join_operator.h"
#include "storage/common/table.h"
#include "sql/stmt/filter_stmt.h"
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
  while (true) {
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
    if (do_predicate((RowTuple &)(joined_tuple_))) {
      break;
    }
  }
  return RC::SUCCESS;
};

bool JoinOperator::do_predicate(RowTuple &tuple)
{
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    // add by Benevor
    if (left_cell.attr_type() == UNDEFINED || right_cell.attr_type() == UNDEFINED) {
      return true;
    }

    bool filter_result = false;
    const int compare = left_cell.compare(right_cell);
    switch (comp) {
      case EQUAL_TO: {
        filter_result = (0 == compare);
      } break;
      case LESS_EQUAL: {
        filter_result = (compare <= 0);
      } break;
      case NOT_EQUAL: {
        filter_result = (compare != 0);
      } break;
      case LESS_THAN: {
        filter_result = (compare < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (compare >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (compare > 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp);
      } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}

// TODO: 将两个tuple合并为一个tuple，参考project_operator
// TupleCellSpec, FieldExpr, Field, TupleCell, Tuple
bool JoinOperator::do_join(Tuple *left, Tuple *right)
{
  joined_tuple_.set_tuple(left, right, left_is_row_);
  return true;
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
