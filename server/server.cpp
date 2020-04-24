#include <iostream>

#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h>

#include "../libraries/core/serializers.hpp"

const int PORT = 9000;
const u_int HOW_MANY_CONNECTION = 5; 

void worker(int socket_fd) {
    std::cout << "I am working!" << std::endl;
    close(socket_fd);
}

int main() {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Couldn't create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    sockaddr *address_ptr = (struct sockaddr *) &address;

    int address_len = sizeof(address);
    socklen_t *address_len_ptr = (socklen_t *) &address_len;
    if (bind(server_fd, address_ptr, *address_len_ptr) < 0) {
        perror("Couldn't bind address");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, HOW_MANY_CONNECTION) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    int socket_fd;
    while (true) {
        std::cout << "wait for connection" << std::endl;
        if (socket_fd = accept( server_fd, address_ptr, address_len_ptr) < 0) {
            perror("accept error");
            exit(EXIT_FAILURE);
        }
        std::cout << "connection accepted" << std::endl;
        worker(socket_fd);
    }
}