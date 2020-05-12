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

    FileDescriptor fd = connector->open(source, std::ios::in, 0);
    int len = connector->read(fd, buf, 4096);
    connector->close(fd);
    

    saver->save(dst, buf, len);

    return true;
};

