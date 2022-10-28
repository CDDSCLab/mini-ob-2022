//
// Created by Zqyi on 2022/10/17.
//

#ifndef __OBSERVER_STORAGE_COMMON_TEXT_H__
#define __OBSERVER_STORAGE_COMMON_TEXT_H__

#include "rc.h"

#define TEXT_SIZE 4097
#define TEXT_FILE "text"
RC insert_text(char *text, int *id);
RC get_text(int id, char *text);
RC update_text(int id, char *text);

#endif  //__OBSERVER_STORAGE_COMMON_TEXT_H__