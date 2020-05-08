#include "handlers.h"
#include <sstream>
#include <limits>

bool get_handler(Command c, Saver* saver){
    if(c.type != Command::Get){
        throw -1;
    }
    std::stringstream ss(c.command_string);
    std::string source;
    std::string dst;
    ss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    ss >> source;
    ss >> dst;

    saver->save(dst, nullptr, 0);


};

