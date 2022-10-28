//
// Created by Zqyi on 2022/10/17.
//
#include <sys/fcntl.h>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include "text.h"

RC try_create_text_file()
{
  int fd = ::open(TEXT_FILE, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST != errno) {
      return RC::IOERR;
    }
  }
  close(fd);
  return RC::SUCCESS;
}

int text_id = 0;
RC insert_text(char *text, int *id)
{
  RC rc = RC::SUCCESS;
  rc = try_create_text_file();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::ofstream out;
  out.open(TEXT_FILE, std::ios::out | std::ios::in);
  if (!out.is_open()) {
    return RC::IOERR;
  }

  out.seekp(text_id * TEXT_SIZE);
  char *temp = new char[TEXT_SIZE - 1];
  memset(temp, 'a', TEXT_SIZE - 1);
  // temp[TEXT_SIZE - 1] = '\n';
  out << temp << std::endl;

  out.seekp(text_id * TEXT_SIZE);
  memcpy(temp, text, TEXT_SIZE - 1);
  int len = strnlen(text, TEXT_SIZE - 1);
  // temp[len] = '\n';
  out << temp << std::endl;

  out.close();

  *id = text_id;
  text_id++;

  free(temp);
  return rc;
}

RC get_text(int id, char *text)
{
  RC rc = RC::SUCCESS;
  std::ifstream in;
  in.open(TEXT_FILE);
  if (!in.is_open()) {
    return RC::IOERR;
  }

  in.seekg(id * TEXT_SIZE);
  in.getline(text, TEXT_SIZE);

  in.close();
  return rc;
}

RC update_text(int id, char *text)
{
  RC rc = RC::SUCCESS;
  std::ofstream out;
  out.open(TEXT_FILE, std::ios::out | std::ios::in);
  if (!out.is_open()) {
    return RC::IOERR;
  }

  // out.seekp(id * TEXT_SIZE);
  char *temp = new char[TEXT_SIZE - 1];
  // memset(temp, 'a', TEXT_SIZE - 1);
  // // temp[TEXT_SIZE - 1] = '\n';
  // out << temp << std::endl;

  out.seekp(id * TEXT_SIZE);
  int len = strnlen(text, TEXT_SIZE - 1);
  memcpy(temp, text, len);
  temp[len] = '\n';
  for (int i = 0; i <= len; i++) {
    out << temp[i];
  }

  out.close();
  free(temp);
  return rc;
}
