

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../libraries/core/messages.hpp"
#include "../libraries/core/serializers.hpp"

#include "../tests/utils.hpp"
#include "worker.h"

std::vector<u_int8_t> open_handler(std::vector<u_int8_t> byte_request) {
  std::cout << "OPEN" << std::endl;

  OpenRequest request = DeserializeToOpenRequest(byte_request);
  std::cout << "Request:" << std::endl;
  std::cout << "  path: " << request.path << std::endl;
  std::cout << "  oflag: " << request.oflag << std::endl;
  std::cout << "  mode: " << request.mode << std::endl;
  int result = open(request.path.c_str(), request.oflag, request.mode);

  OpenResponse response = {result, errno};
  std::cout << "Response:" << std::endl;
  std::cout << "  fd: " << response.result << std::endl;
  std::cout << "  error: " << response.error << std::endl;
  std::cout << std::endl;

  std::vector<u_int8_t> byte_response = SerializeOpenResponse(response);
  return byte_response;
}

std::vector<u_int8_t> read_handler(std::vector<u_int8_t> byte_request) {
  std::cout << "READ" << std::endl;

  ReadRequest request = DeserializeToReadRequest(byte_request);
  std::cout << "Request:" << std::endl;
  std::cout << "  fd: " << request.fd << std::endl;
  std::cout << "  count: " << request.count << std::endl;

  std::vector<u_int8_t> buf = std::vector<u_int8_t>(request.count);
  int result = read(request.fd, buf.data(), request.count);
  buf.resize(result);

  ReadResponse response = {result, buf, errno};
  std::cout << "Response:" << std::endl;
  std::cout << "  result: " << response.result << std::endl;
  std::cout << "  error: " << response.error << std::endl;
  std::cout << std::endl;

  std::vector<u_int8_t> byte_response = SerializeReadResponse(response);
  return byte_response;
}

//+
std::vector<u_int8_t> write_handler(std::vector<u_int8_t> byte_request) {
  std::cout << "WRITE" << std::endl;

  WriteRequest request = DeserializeToWriteRequest(byte_request);
  std::cout << "Request:" << std::endl;
  std::cout << "  fd: " << request.fd << std::endl;
  //std::cout << "  buf: " << request.buf << std::endl;

  //std::vector<u_int8_t> buf = std::vector<u_int8_t>(request.count);
  size_t nbytes = (size_t) sizeof(std::vector<u_int8_t>) + (sizeof(u_int8_t) * request.buf.size());

  int result = write(request.fd, request.buf.data(), nbytes);

  WriteResponse response = {result, errno};
  std::cout << "Response:" << std::endl;
  std::cout << "  result: " << response.result << std::endl;
  std::cout << "  error: " << response.error << std::endl;
  std::cout << std::endl;

  std::vector<u_int8_t> byte_response = SerializeWriteResponse(response);
  return byte_response;
}

//+
std::vector<u_int8_t> lseek_handler(std::vector<u_int8_t> byte_request) {
  std::cout << "LSEEK" << std::endl;

  LseekRequest request = DeserializeToLseekRequest(byte_request);
  std::cout << "Request:" << std::endl;
  std::cout << "  fd: " << request.fd << std::endl;
  std::cout << "  offset: " << request.offset << std::endl;
  std::cout << "  whence: " << request.whence << std::endl;

  off_t result =  lseek(request.fd, request.offset, request.whence);

  LseekResponse response = {result, errno};
  std::cout << "Response:" << std::endl;
  std::cout << "  result: " << response.result << std::endl;
  std::cout << "  error: " << response.error << std::endl;
  std::cout << std::endl;

  std::vector<u_int8_t> byte_response = SerializeLseekResponse(response);
  return byte_response;
}

std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request) {
  MessageParser parser = MessageParser(byte_request);
  switch (parser.readMessageType()) {
  case MessageType::OPEN_REQUEST:
    return open_handler(byte_request);
  case MessageType::READ_REQUEST:
    return read_handler(byte_request);
  case MessageType::WRITE_REQUEST:
    return write_handler(byte_request);
  default:
    return std::vector<u_int8_t>{0, 0, 0, 0, 0};
  }
}

void worker(int socket_fd) {
  std::cout << "I am working!" << std::endl;
  std::vector<u_int8_t> byte_request;
  std::vector<u_int8_t> byte_response;
  while (true) {
    byte_request = receiveMessage(socket_fd);
    byte_response = make_response(byte_request);
    sendMessage(socket_fd, byte_response);
  }
}


