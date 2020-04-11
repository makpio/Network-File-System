#ifndef MESSAGES_CPP
#define MESSAGES_CPP

#include <cstdint>
#include <sys/types.h>
#include <vector>
#include <string>

struct OpenRequest {
  char *path;
  int oflag;
  int mode;
};

struct OpenResponse {
  int result;
  int error;
};

struct ReadRequest {
  int fd;
  ssize_t count;
};

struct ReadResponse {
  int result;
  std::vector<char> buf;
  int error;
};

struct WriteRequest {
  int fd;
  const char* buf;
  ssize_t count;
};

struct WriteResponse {
  ssize_t result;
  int error;
};

struct LseekRequest {
  int fd;
  off_t offset;
  int whence;
};

struct LseekResponse {
  off_t result;
  int error;
};

struct CloseRequest {
  int fd;
};

struct CloseResponse {
  int result;
  int error;
};

#endif
