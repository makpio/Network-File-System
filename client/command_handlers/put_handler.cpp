#include "handlers.h"
#include <limits>
#include <sstream>


bool put_handler(Command c, Reader* reader, Connector* connector){
    if(c.type != Command::Put){
        throw -1;
    }
    std::stringstream ss(c.command_string);
    std::string source;
    std::string dst;
    ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    ss >> source;
    ss >> dst;

    char buf[4096];

    if(reader->open(source) == false){
        return false;
    }
    FileDescriptor fd = connector->open(dst, std::ios::out, 0);

    ssize_t len;
    do{
        len = reader->read(buf, 4096);
        connector->write(fd, buf, len);
    }while(len != 0);
    
    connector->close(fd);
    
    reader->close();
    
    return true;
};