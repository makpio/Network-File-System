#ifndef LIB_HPP
#define LIB_HPP

#include <dirent.h>
#include <sys/types.h>
#include <vector>

extern int error;

class NFSClient {
public:
  NFSClient(char *host, int port, char *user, char *password);
  int connect();

  int open(char *path, int oflag, int mode);
  ssize_t read(int fd, void *buf, size_t count);
  ssize_t write(int fd, const void *buf, size_t count);
  off_t lseek(int fd, off_t offset, int whence);
  int close(int fd);
  int unlink(const char *pathname);

  int opendir(const char *name);
  dirent *readdir(int dirfd);
  int closedir(int dirfd);

private:
  void sendRequest_(std::vector<char> request);
  std::vector<char> receiveResponse_();
};

#endif
