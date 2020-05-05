#ifndef WORKER_CPP
#define WORKER_CPP

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "../libraries/core/messages.hpp"
#include "../libraries/core/serializers.hpp"

std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request) {
  MessageParser parser = MessageParser(byte_request);
  switch (parser.readMessageType()) {

  case MessageType::OPEN_REQUEST:
    std::cout << "OPEN_REQUEST" << std::endl;

    OpenRequest request = DeserializeToOpenRequest(byte_request);
    int result = open(request.path.c_str(), request.oflag, request.mode);

    OpenResponse response = {result, errno};
    std::cout << "result: " << result << std::endl;
    std::cout << "errno: " << errno << std::endl;

    std::vector<u_int8_t> byte_response = SerializeOpenResponse(response);
    return byte_response;
  }
  return std::vector<u_int8_t>{0, 0, 0, 0, 0};
}

void worker(int socket_fd) {
  std::cout << "I am working!" << std::endl;
  while (true) {
    std::vector<u_int8_t> byte_request = receiveMessage(socket_fd);
    std::vector<u_int8_t> byte_response = make_response(byte_request);
    sendMessage(socket_fd, byte_response);
  }
}

#endif
