//
// Created by Moonmen on 2022/10/20.
//

#pragma once

#include "rc.h"
#include "sql/parser/parse_defs.h"

RC int2float(Value *value);

RC int2char(Value *value);

RC float2int(Value *value);

RC float2char(Value *value);

RC char2int(Value *value);

RC char2float(Value *value);

RC char2date(Value *value);
