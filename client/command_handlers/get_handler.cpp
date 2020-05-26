#include "handlers.h"
#include <sstream>
#include <limits>

bool get_handler(Command c, Saver* saver, Connector* connector){
    if(c.type != Command::Get){
        throw -1;
    }
    std::stringstream ss(c.command_string);
    std::string source;
    std::string dst;
    ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    ss >> source;
    ss >> dst;

    char buf[4096];

    FileDescriptor fd;

    try{
        fd = connector->open(source, std::ios::in, 0);
    }
    catch(std::ios_base::failure e){
        return false;
    }

    if(fd < 0){
        return false;
    }

    if(saver->open(dst) == false){
        return false;
    }

    ssize_t len;
    do{
        len = connector->read(fd, buf, 4096);
        saver->save(buf, len);
    }while(len != 0);
    
    connector->close(fd);
    
    saver->close();
    
    return true;
};

