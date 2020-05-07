#include "loop.h"
#include "command.h"
#include "utils.h"
#include <iostream>

int run_loop(){
    while(1){
        disp_prompt();
        Command c = get_command();

        if(c.type == Command::Invalid_command){
            display_error_message();
            display_help_prompt();
        }

        switch(c.type){
            case Command::Help:{
                display_help();
                break;
            }
            case Command::Get:{
                std::cout<<"Komenda get jeszcze nie obslugiwana\n";
                break;
            }
            
        }
    }
}