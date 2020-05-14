#include <iostream>
#include <string.h>
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
/*
    char *path = "../README.md";
    int fd = client.open(path, O_RDONLY, 0);
    std::cout << "open_fd: " << fd << std::endl;
    std::cout << "open_error: " << error << std::endl;

    char buffer[1024];
    int len = client.read(fd, buffer, 1023);
    buffer[len] = 0;
    std::cout << "read_len: " << len << std::endl;
    std::cout << "read_error: " << error << std::endl;
    std::cout << "read_buffer: " << buffer << std::endl;
*/

    char *path = "../xdd";
    int fd = client.open(path, O_RDWR, 0);

    std::cout << "open_fd: " << fd << std::endl;
    std::cout << "open_error: " << error << std::endl;

    off_t of = 32;
    off_t offset = client.lseek(fd, of, SEEK_SET);
    std::cout << "lseek_fd: " << fd << std::endl;
    std::cout << "lseek_offset: " << offset << std::endl;
    std::cout << "lseek_error: " << error << std::endl;


    char buffer1[128] = {0};
    for(int i = 0 ; i < 127; ++i) {buffer1[i] = 'a';}


  std::cout << "buffer1_sizeof: " << sizeof(buffer1) << std::endl;

    int lent = client.write(fd, buffer1, strlen(buffer1));
 
    std::cout << "write_fd: " << fd << std::endl;
    std::cout << "write_len: " << lent << std::endl;
    std::cout << "write_error: " << error << std::endl;
    std::cout << "write_buffer: " << buffer1[0] << std::endl;


    int fd1 = client.close(fd);
    std::cout << "close_fd: " << fd1 << std::endl;
    std::cout << "close_error: " << error << std::endl;

    const char* path1 = "../xdd";
    int isZero = client.unlink(path1);
    std::cout << "unlink_isZero: " << isZero << std::endl;
    std::cout << "unlink_error: " << error << std::endl;

}