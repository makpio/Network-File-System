#include "saver.h"



bool Mock_saver::save(std::string name, char* buffer, uint len){
    std::cout<<"\nZapisywanie pliku '"+name+"' o wielkosci " + std::to_string(len)<<'\n';
}