#include "connector.h"

int LocalFSConnector::connect(std::string host, uint port, std::string user, std::string passwd){
    return 1;
}

FileDescriptor LocalFSConnector::open(std::string path, int oflag, int mode){
    std::fstream *s = new std::fstream(path);
    FileDescriptor fd = open_files.rbegin()->first + 1;
    open_files[fd] = s;
}

int LocalFSConnector::close(FileDescriptor fd){
    open_files[fd]->close();
    delete open_files[fd];
    open_files.erase(fd);

}
