#ifndef WORKER_CPP
#define WORKER_CPP
#include <vector>

#include <sys/types.h>

std::vector<u_int8_t> open_handler(std::vector<u_int8_t> byte_request);

std::vector<u_int8_t> read_handler(std::vector<u_int8_t> byte_request);

std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request);

class Worker {
public:
    Worker(int socket_fd){
        this->socket_fd = socket_fd;
    }
    void Run(){

    }
private:
    int socket_fd;
};

#endif