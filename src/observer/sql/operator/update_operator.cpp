//
// Created by Moon on 2022/10/18.
//

#include "update_operator.h"

#include "common/log/log.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"
#include "sql/operator/operator_factory.h"

RC UpdateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("update operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  for (int i = update_stmt_->select_stmt().size() - 1; i >= 0; i--) {
    auto select_stmt = update_stmt_->select_stmt()[i];
    if (select_stmt == nullptr) {
      continue;
    }
    ProjectOperator project_oper;
    OperatorFactory::GetProjectOperator(select_stmt, &project_oper);
    rc = project_oper.open();
    if (rc != RC::SUCCESS) {
      return rc;
    }

    TupleCell cell;
    if (project_oper.next() == RC::SUCCESS) {
      Tuple *tuple = project_oper.current_tuple();
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get current record. rc=%s", strrc(rc));
        return rc;
      }
      if (tuple->cell_num() != 1) {
        rc = RC::INTERNAL;
        return rc;
      }
      tuple->cell_at(0, cell);
    } else {
      return RC::SUCCESS;
    }
    if (project_oper.next() == RC::SUCCESS) {
      return RC::INTERNAL;
    }
    *update_stmt_->get_values()[i] = cell.to_value();
  }

  Table *table = update_stmt_->table();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    auto row_tuple = dynamic_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    rc = table->update_record(trx_, &record, update_stmt_->update_fields(), update_stmt_->values());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC UpdateOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}