#include "saver.h"
#include "utils.h"


bool Mock_saver::save(char* buffer, uint len){
    if(len == 0){
        return true;
    }
    // TODO: zrobić zapisywanie po kawałku bufora.
    std::cout<<"\nZapisywanie pliku '"+name_+"' o wielkosci " + std::to_string(len)<<'\n';
    std::cout<<convertToString(buffer, len)<<'\n';
    return true;
}  

bool Mock_saver::open(std::string file_name){
    if(0!=name_.compare(std::string(""))){
        return false;
    }
    std::cout<<"Otwieranie pliku "+file_name<<'\n';
    name_ = file_name;
}

void Mock_saver::close(){
    name_ = std::string("");
}
