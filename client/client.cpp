#include <iostream>
#include <string>
#include <fcntl.h>

#include "../libraries/client/lib.hpp"
#include "utils.h"
#include "loop.h"


char *HOST = "localhost";
int PORT = 9000;
char *USER = "user";
char *PASSWORD = "password";


#include <signal.h>

void signal_callback_handler(int signum) {
   std::cout << "\n\nSpadam stad z powodu: " << signum << std::endl;
   // Terminate program
   exit(signum);
}


int main(){
    signal(SIGINT, signal_callback_handler);

    display_welcome_message();

    run_loop();
    // NFSClient client;
    // std::cout << "try to connect" << std::endl;
    // client.connect4(HOST, PORT, USER, PASSWORD);
    // std::cout << "connected" << std::endl;

    // char *path = "../README.md";
    // int fd = client.open(path, O_RDONLY, 0);
    // std::cout << "fd: " << fd << std::endl;
    // std::cout << "error: " << error << std::endl;

    // char buffer[1024];
    // int len = client.read(fd, buffer, 1023);
    // buffer[len] = 0;
    // std::cout << "len: " << len << std::endl;
    // std::cout << "error: " << error << std::endl;
    // std::cout << "buffer: " << buffer << std::endl;
}