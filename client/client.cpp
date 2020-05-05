#include <iostream>
#include <string>
#include <fcntl.h>

#include "../libraries/client/lib.hpp"


char *HOST = "localhost";
int PORT = 9000;
char *USER = "user";
char *PASSWORD = "password";


int main(){
    NFSClient client;
    std::cout << "try to connect" << std::endl;
    client.connect4(HOST, PORT, USER, PASSWORD);
    std::cout << "connected" << std::endl;

    char *path = "../README.md";
    int fd = client.open(path, O_RDONLY, 0);
    std::cout << "fd: " << fd << std::endl;

    // char buffer[1024];
    // client.read(fd, buffer, 1024);

    // std::cout << buffer << std::endl;
}