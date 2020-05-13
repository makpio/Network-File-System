#include "loop.h"
#include "command.h"
#include "reader.h"
#include "utils.h"
#include "command_handlers/handlers.h"
#include <iostream>

int run_loop(Connector* connector, bool& exit){
    bool _run = true;
    while(_run && (!exit)){
        disp_prompt();
        Command command = get_command();


        switch(command.type){
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
                get_handler(command, &s, connector);
                break;
            }
            case Command::Put:{
                Mock_reader r;
                put_handler(command, &r, connector);
                break;
            }
            case Command::Exit:{
                std::cout<<'\n';
                disp_prompt();
                std::cout<<"exit\n";
                _run = false;
                break;
            }
        }
    }
    return 0;
}