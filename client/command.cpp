#include "command.h"
#include <iostream>

Command get_command(){
    std::string s;
    std::cin>>s;

    std::string command_type = get_command_type(s);

    Command c;
    c.command_string = s;

    if(command_type.find(std::string("help")) != std::string::npos){
        c.type = Command::Help;
    }else if(command_type.find(std::string("get")) != std::string::npos){
        c.type = Command::Get;
    }else{
        c.type = Command::Invalid_command;    
    }
    
    
    return c;
};

std::string get_command_type(const std::string& s){
    std::string new_s;
    bool c_begun = false;
    for(char c: s){
        if(c == ' '){
            if(c_begun){
                // konie komendy (nastepna spacja )
                break;
            }
        }else{
            if(!c_begun){
                c_begun = true;
            }
            new_s += c; 
        }
    }
    return new_s;
}