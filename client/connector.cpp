#include "connector.h"

int LocalFSConnector::connect(std::string host, uint port, std::string user, std::string passwd){
    return 1;
}

FileDescriptor LocalFSConnector::open(std::string path, int oflag, int mode){
    std::fstream *s = new std::fstream(path, std::ios::in);
    FileDescriptor fd;
    if(open_files.empty()){
        fd = 1;
    }else{
        fd = open_files.rbegin()->first + 1;
    }
    
    open_files[fd] = s;
    return fd;
}


ssize_t LocalFSConnector::read(FileDescriptor fd, char *buf, size_t count){
    // TODO: sprawdzić czy plik istnieje
    if(open_files.find(fd) != open_files.end()){
        std::fstream* s = open_files[fd];
        s->get(buf, count);
        return s->gcount();
    }
    
}

int LocalFSConnector::close(FileDescriptor fd){
    if(open_files.find(fd) != open_files.end()){
        open_files[fd]->close();
        delete open_files[fd];
        open_files.erase(fd);
    }
}

LocalFSConnector::~LocalFSConnector(){
    for (auto iter = open_files.rbegin(); iter != open_files.rend(); ++iter) {
        close(iter->first);
    }
}
