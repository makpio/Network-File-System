#ifndef WORKER_HPP
#define WORKER_HPP
#include <vector>
#include <thread>
#include <unordered_map>

#include <sys/types.h>
#include "DescriptorsMapper.h"



class Worker {
public:
  Worker(int socket_fd);
  //~Worker();
  void run();
  std::thread spawn();
private:
  int socket_fd;
  DescriptorsMapper mapper;

};

#endif