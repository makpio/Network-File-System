#include "utils.h"
#include <iostream>


void display_welcome_message(){
    std::cout<<"Welcome to micro NFS! \n\n";
    std::cout<<"         _   _  ______  _____ "<<'\n';
    std::cout<<"        | \\ | ||  ____|/ ____|"<<'\n';
    std::cout<<"  _   _ |  \\| || |__  | (___  "<<'\n';
    std::cout<<" | | | || . ` ||  __|  \\___ \\ "<<'\n';
    std::cout<<" | |_| || |\\  || |     ____) |"<<'\n';
    std::cout<<" | ._,_||_| \\_||_|    |_____/ "<<'\n';
    std::cout<<" | |                          "<<'\n';
    std::cout<<" |_|   \n\n"<<std::endl;


    display_help_prompt();
}

void disp_prompt(){
    std::cout<<">>>";
}

void display_error_message(){
    std::cout<<"Invalid command :/ \n";
};
void display_help_prompt(){
    std::cout<<"Type 'help' for help :) "<<std::endl;
};

void display_help(){
    std::cout<<"No na razie nic nie śmiaga w sumie\n\n";
    std::cout<<"help - wyswietla to menu\n";
}

std::string convertToString(char* a, int size) { 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 
  