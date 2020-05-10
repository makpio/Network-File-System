#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <sys/types.h>
#include <string>
#include <fstream>
#include <map>

using FileDescriptor = int;

class Connector{
public:
    
    virtual int connect(std::string host, uint port, std::string user, std::string passwd)=0;
    virtual int open(std::string path, int oflag, int mode)=0;
    virtual ssize_t read(FileDescriptor fd, char *buf, size_t count)=0;
    virtual ssize_t write(FileDescriptor fd, const char* buf, size_t count)=0;
    virtual int close(FileDescriptor fd)=0;
};


class LocalFSConnector: public Connector{
public:
    int connect(std::string host, uint port, std::string user, std::string passwd);
    FileDescriptor open(std::string path, int oflag, int mode);
    ssize_t read(FileDescriptor fd, char *buf, size_t count);
    ssize_t write(FileDescriptor fd, const char* buf, size_t count){return 0;};
    int close(FileDescriptor fd);

    ~LocalFSConnector();
private:
    std::map<FileDescriptor, std::fstream*> open_files{}; 
};


#endif