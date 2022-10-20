
//
// Created by Benevor on 2022/10/20.
//

#include "sql/stmt/show_index_stmt.h"

#include "common/log/log.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

ShowIndexStmt::ShowIndexStmt(Table *table) : table_(table)
{}

ShowIndexStmt::~ShowIndexStmt()
{}

DeleteStmt::DeleteStmt(Table *table, FilterStmt *filter_stmt) : table_(table), filter_stmt_(filter_stmt)
{}

RC ShowIndexStmt::create(Db *db, const ShowIndex &show_index, Stmt *&stmt)
{
  const char *table_name = show_index.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  stmt = new ShowIndexStmt(table);
  return RC::SUCCESS;
}