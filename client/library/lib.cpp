#include "lib.hpp"
#include "src/messeges.cpp"

extern int error;

void NFSClient::connect(char *host, int port, char *user, char *password) {}

int NFSClient::open(char *path, int oflag, int mode) {}
ssize_t NFSClient::read(int fd, void *buf, size_t count) {}
ssize_t NFSClient::write(int fd, const void *buf, size_t count) {}
off_t NFSClient::lseek(int fd, off_t offset, int whence) {}
int NFSClient::close(int fd) {}
int NFSClient::unlink(const char *pathname) {}

int NFSClient::opendir(const char *name) {}
dirent *NFSClient::readdir(int dirfd) {}
int NFSClient::closedir(int dirfd) {}
