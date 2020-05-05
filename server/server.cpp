#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "./worker.cpp"


const u_int PORT = 9000;
const u_int HOW_MANY_CONNECTION = 5;


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

  while (true) {
    int socket_fd = accept(server_fd, (struct sockaddr *)0, (unsigned int *)0);
    if (socket_fd == -1) {
      perror("accept");
      exit(3);
    }
    worker(socket_fd);
  }
}