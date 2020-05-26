#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "../libraries/client/lib.hpp"


char *HOST = "localhost";
int PORT = 9000;
char *USER = "user";
char *PASSWORD = "password";


int main(){
//connect  
    NFSClient client;
    std::cout << "try to connect" << std::endl;
    client.connect4(HOST, PORT, USER, PASSWORD);
    std::cout << "connected" << std::endl;

//read
//    char *path = "../xdd1";
//    int fd = client.open(path, O_RDONLY, 0);
//    std::cout << "open_fd: " << fd << std::endl;
//    std::cout << "open_error: " << error << std::endl;

//    char buffer[1024];
//    int len = client.read(fd, buffer, 1023);
//    buffer[len] = 0;
//    std::cout << "read_len: " << len << std::endl;
//    std::cout << "read_error: " << error << std::endl;
//    std::cout << "read_buffer: " << buffer << std::endl;

//open
    char *path = "../xdd1";
    int fd = client.open(path, O_RDWR, 0);

    std::cout << "open_fd: " << fd << std::endl;
    std::cout << "open_error: " << error << std::endl;
//lseek
//   off_t of = 32;
//    off_t offset = client.lseek(fd, of, SEEK_SET);
//    std::cout << "lseek_fd: " << fd << std::endl;
//    std::cout << "lseek_offset: " << offset << std::endl;
//    std::cout << "lseek_error: " << error << std::endl;

//write
    char buffer1[127] = {0};
    for(int i = 0 ; i < 17; ++i) {buffer1[i] = 'a';}
    int lent = client.write(fd, buffer1, strlen(buffer1));
 
    std::cout << "write_fd: " << fd << std::endl;
    std::cout << "write_len: " << lent << std::endl;
    std::cout << "write_error: " << error << std::endl;
    std::cout << "write_buffer: " << buffer1[0] << std::endl;

//close
    int fd1 = client.close(fd);
    std::cout << "close_fd: " << fd1 << std::endl;
    std::cout << "close_error: " << error << std::endl;
//unlink 
//   const char* path1 = "../xdd1";
//   int isZero = client.unlink(path*/ro: " << isZero << std::endl;
//   std::cout << "unlink_error: " << error << std::endl;

//opendir
    const char* name = "../xdd";
    int dirfd = client.opendir(name);
    std::cout << "opendir_fd: " << dirfd << std::endl;
    std::cout << "opendir_error: " << error << std::endl;

//readdir
    
    dirent dirent = client.readdir(dirfd);
    std::cout << "dirent.D_NAME: " << dirent.d_name<< std::endl;
   // std::cout<<"dirent.D_OFF: "<<dirent.d_off<<std::endl;
  // std::cout<<"direntD_reclen: "<<dirent.d_reclen<<std::endl;
    

//closedir
    int dirfd1 = client.closedir(dirfd);
    std::cout << "closedir_fd: " << dirfd1 << std::endl;
    std::cout << "closedir_error: " << error << std::endl;
}
/*
#include "include/lib.hpp"
#include "utils.h"
#include "loop.h"
#include "connector.h"
#include "include/cxxopts.hpp"
#include "linenoise_setup.h"



#include <signal.h>

bool uNFS_EXIT = false;

void signal_callback_handler(int signum) {
   std::cout << "\n\nSpadam stad z powodu: " << signum << std::endl;
   // Terminate program
   uNFS_EXIT = true;
}


int main(int argc, char* argv[]){
    signal(SIGINT, signal_callback_handler);

    cxxopts::Options options("test", "A brief description");

    options.add_options()
        ("u,user", "User name", cxxopts::value<std::string>())
        ("a,address", "Host address", cxxopts::value<std::string>())
        ("p,port", "Define port", cxxopts::value<int>()->default_value("9000"))
        ("h,help", "Print usage")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help") || !result.count("address") || !result.count("user"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }

    std::string host = result["address"].as<std::string>();
    std::string user = result["user"].as<std::string>();
    int port = result["port"].as<int>();

    // prompting for password
    std::string passwd(getpass("Password: "));

    Connector* connector = new NFSConnector(); 

    try{
      auto succ = connector->connect(host.c_str(), port, user.c_str(), passwd.c_str());
      if(succ != 0){
        std::cout<<"Nie udało się połączyć z serwerem\n";
        exit(-1);  
      }
    }
    catch(std::domain_error e){
      std::cout<<"Nie udało się połączyć z serwerem\n";
      exit(-1);
    }

    display_welcome_message();


    custom_linenoise_setup();
    run_loop(connector, uNFS_EXIT);


    delete connector;
    linenoiseHistorySave(".uNSFcommandhistory.txt");
    
}
*/