

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


Worker::Worker(int socket_fd){
  this->socket_fd = socket_fd;
}
// Worker::~Worker(){
//   close(socket_fd);
// }
void Worker::run(){
  std::cout << "I am working!" << std::endl;
  std::vector<u_int8_t> byte_request;
  std::vector<u_int8_t> byte_response;
  std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
  while (true) {
    byte_request = receiveMessage(socket_fd);
    byte_response = make_response(byte_request);
    sendMessage(socket_fd, byte_response);
  }
  std::cout<<"Stop working" << std::endl;
}
std::thread Worker::spawn() {
  return std::thread( [this] { this->run(); } );
}

