#ifndef MESSAGES_CPP
#define MESSAGES_CPP

#include <cstdint>
#include <sys/types.h>
#include <vector>
#include <string>

u_int8_t OPEN_CODE = 1;
u_int8_t READ_CODE = 2;
u_int8_t WRITE_CODE = 3;
u_int8_t LSEEK_CODE = 4;
u_int8_t CLOSE_CODE = 5;


struct OpenRequest {
  std::string path;
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
  std::vector<char> buf;
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
