#ifndef WORKER_HPP
#define WORKER_HPP
#include <vector>
#include <thread>
#include <unordered_map>

#include <sys/types.h>

std::vector<u_int8_t> open_handler(std::vector<u_int8_t> byte_request);

std::vector<u_int8_t> read_handler(std::vector<u_int8_t> byte_request);

std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request);

class Worker {
public:
  Worker(int socket_fd);
  //~Worker();
  void run();
  std::thread spawn();
private:
  int socket_fd;
};

#endif