#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../libraries/core/messages.hpp"
#include "../libraries/core/serializers.hpp"

#include "../tests/utils.hpp"
#include "worker.hpp"
#include "handler.h"

Worker::Worker(int socket_fd) {
  this->socket_fd = socket_fd;
}
void Worker::run() {
    if(!authenticateUser())
        return;

  std::vector<u_int8_t> byte_request;
  std::vector<u_int8_t> byte_response;
  while(true){
      try{
          byte_request = receiveMessage(socket_fd);
          byte_response = handler.make_response(byte_request);
          sendMessage(socket_fd, byte_response);
      }
      catch (std::ios_base::failure&) {
          std::cout << "Ending connection with client" << std::endl;
          break;
      }
  }
}
std::thread Worker::spawn() {
  return std::thread( [this] { this->run(); } );
}

bool Worker::authenticateUser() {
    std::vector<u_int8_t> byte_request = receiveMessage(socket_fd);

    MessageParser parser = MessageParser(byte_request);
    if(parser.readMessageType() != MessageType::AUTHENTICATE_REQUEST)
        return false;

    AuthenticateResponse authenticateResponse = handler.authenticate_handler(byte_request);
    bool isAuthenticated = authenticateResponse.result == 0;

    sendMessage(socket_fd, SerializeAuthenticateResponse(authenticateResponse));
    return isAuthenticated;
}

