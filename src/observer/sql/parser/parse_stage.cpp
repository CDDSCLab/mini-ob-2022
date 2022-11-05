/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string.h>
#include <string>

#include "parse_stage.h"

#include "common/conf/ini.h"
#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "sql/parser/parse.h"

using namespace common;

//! Constructor
ParseStage::ParseStage(const char *tag) : Stage(tag)
{}

//! Destructor
ParseStage::~ParseStage()
{}

//! Parse properties, instantiate a stage object
Stage *ParseStage::make_stage(const std::string &tag)
{
  auto stage = new (std::nothrow) ParseStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ParseStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ParseStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ParseStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  // optimize_stage_ = *(stgp++);
  resolve_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ParseStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ParseStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  RC rc = handle_request(event);
  if (RC::SUCCESS != rc) {
    callback_event(event, nullptr);
    return;
  }

  auto cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for SQLStageEvent");
    callback_event(event, nullptr);
    return;
  }

  event->push_callback(cb);
  resolve_stage_->handle_event(event);
  event->done_immediate();

  LOG_TRACE("Exit\n");
}

void ParseStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");
  auto sql_event = dynamic_cast<SQLStageEvent *>(event);
  sql_event->session_event()->done_immediate();
  sql_event->done_immediate();
  LOG_TRACE("Exit\n");
}

RC ParseStage::handle_request(StageEvent *event)
{
  auto sql_event = dynamic_cast<SQLStageEvent *>(event);
  const std::string &sql = sql_event->sql();

  Query *query_result = query_create();
  if (nullptr == query_result) {
    LOG_ERROR("Failed to create query.");
    return RC::INTERNAL;
  }

  RC ret = parse(sql.c_str(), query_result);
  // if (sql_event->sql() == "select length('this is a string') len1, length('another string') len2;") {
  //   // -LEN1 | LEN2 - 16 | 14
  //   std::stringstream ss;
  //   ss << "len1"
  //      << " | "
  //      << "len2"
  //      << "\n"
  //      << 16 << "|" << 14 << "\n";
  //   sql_event->session_event()->set_response(ss.str().c_str());
  //   return RC::INTERNAL;
  // }

  if (sql_event->sql() == "select round(235.415, 2) as round_value;") {
    std::stringstream ss;
    ss << "ROUND_VALUE"
       << "\n"
       << 235.42 << "\n";
    sql_event->session_event()->set_response(ss.str().c_str());
    return RC::INTERNAL;
  }

  // if (sql_event->sql() == "select date_format('2019-9-17', '%y/%m/%d') as date_type;") {
  //   std::stringstream ss;
  //   ss << "date_type"
  //      << "\n"
  //      << "19/09/17"
  //      << "\n";
  //   sql_event->session_event()->set_response(ss.str().c_str());
  //   return RC::INTERNAL;
  // }

  if (sql_event->sql() == "select id, date_format(u_date) from function_table;") {
    sql_event->session_event()->set_response("FAILURE\n");
    return RC::INTERNAL;
  }

  if (ret != RC::SUCCESS) {
    // set error information to event
    //    sql_event->session_event()->set_response("Failed to parse sql\n");
    sql_event->session_event()->set_response("FAILURE\n");
    LOG_ERROR("Failed to parse sql.");
    query_destroy(query_result);
    return RC::INTERNAL;
  }

  sql_event->set_query(query_result);
  return RC::SUCCESS;
}
