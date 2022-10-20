
//
// Created by Benevor on 2022/10/20.
//

#pragma once

#include "rc.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/parse_defs.h"

class Table;
class FilterStmt;

class ShowIndexStmt : public Stmt {
public:
  ShowIndexStmt(Table *table);
  ~ShowIndexStmt() override;

  void set(Table *table);

  StmtType type() const override
  {
    return StmtType::SHOW_INDEX;
  }

public:
  static RC create(Db *db, const ShowIndex &show_index, Stmt *&stmt);

public:
private:
  Table *table_ = nullptr;
};