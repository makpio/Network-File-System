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

    // int fd = client.open("/home/kowies/plik.txt", O_RDONLY, 0);

    // char buffer[1024];
    // client.read(fd, buffer, 1024);

    // std::cout << buffer << std::endl;
}