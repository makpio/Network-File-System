#ifndef MESSAGES_CPP
#define MESSAGES_CPP

#include <cstdint>
#include <sys/types.h>
#include <vector>
#include <string>

u_int8_t OPEN_REQUEST_CODE = 1;
u_int8_t OPEN_RESPONSE_CODE = 2;
u_int8_t READ_REQUEST_CODE = 3;
u_int8_t READ_RESPONSE_CODE = 4;
u_int8_t WRITE_REQUEST_CODE = 5;
u_int8_t WRITE_RESPONSE_CODE = 6;
u_int8_t LSEEK_REQUEST_CODE = 7;
u_int8_t LSEEK_RESPONSE_CODE = 8;
u_int8_t CLOSE_REQUEST_CODE = 9;
u_int8_t CLOSE_RESPONSE_CODE = 10;

/*
 *fd = file descriptor
 *
 *
 * 
 */ 


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
