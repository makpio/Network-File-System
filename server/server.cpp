#include <iostream>
#include <thread>
#include <vector>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "worker.hpp"
#include "../libraries/core/messages.hpp"
#include "../libraries/core/serializers.hpp"

const u_int PORT = 9000;
const u_int HOW_MANY_CONNECTION = 5;

void work(int);

int main() {
  int server_fd;
  unsigned int length;
  struct sockaddr_in server_addr;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("opening stream socket");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof server_addr) == -1) {
    perror("binding stream socket");
    exit(1);
  }

  length = sizeof server_addr;
  if (getsockname(server_fd, (struct sockaddr *)&server_addr, &length) == -1) {
    perror("getting socket name");
    exit(2);
  }
  printf("Socket port #%d\n", ntohs(server_addr.sin_port));
  listen(server_fd, 5);
  std::cout << "Server_fd: " << server_fd << std::endl;

  // auto workers = std::vector<std::thread>();
  auto fds = std::vector<int>();
  //fds.push_back(server_fd);

  while (true) {
    int socket_fd = accept(server_fd, (struct sockaddr *)0, (unsigned int *)0);
    if (socket_fd == -1) 
      perror("accept");
    else{
      work(socket_fd);
    }
    close(socket_fd);
    //fds.push_back(socket_fd);
    // std::cout << "Thread_fd: " << socket_fd << std::endl; 
    // workers.push_back(Worker(socket_fd).spawn());
  }

  std::cout<<"Stop working" << std::endl;
  // for(auto& worker : workers)
  //   worker.join();
  // for(int i : fds)
  //   close(i);
}

void work(int socket_fd){
  std::cout << "I am working!" << std::endl;
  std::vector<u_int8_t> byte_request;
  std::vector<u_int8_t> byte_response;
  std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
  //while (true) {
    byte_request = receiveMessage(socket_fd);
    byte_response = make_response(byte_request);
    sendMessage(socket_fd, byte_response);
  //}
}