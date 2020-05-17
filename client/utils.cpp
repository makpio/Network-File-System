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
    std::cout<<"get <remote file name> <local file name> - pobiera plik z serwera i zapisuje go lokalnie \n";
    std::cout<<"put <local file> <remote file> - zapisuje lokalny plik na serwerze\n";
    std::cout<<"record <remote file> <record size> <record number> (jeszcze nie ma)\n";
    std::cout<<"ls <path> - wyświetla pliki w podanym folderze\n";
    std::cout<<"exit - wyjscie z programu\n";

}

std::string convertToString(char* a, int size) { 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

void show_not_implemented_info(){
    std::cout<<"We are sorry but your command has not yet been implemented or is incorrect\n";
}
  