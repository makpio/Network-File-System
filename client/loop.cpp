#include "loop.h"
#include "command.h"
#include "utils.h"
#include "command_handlers/handlers.h"
#include <iostream>

int run_loop(){
    while(1){
        disp_prompt();
        Command c = get_command();


        switch(c.type){
            case Command::Invalid_command:{
                display_error_message();
                display_help_prompt();
                break;
            }
            case Command::Empty:{
                continue;
            }
            case Command::Help:{
                display_help();
                break;
            }
            case Command::Get:{
                Mock_saver s;
                get_handler(c, &s);
                break;
            }
            
        }
    }
}