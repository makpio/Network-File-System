#include "saver.h"
#include "utils.h"


bool Mock_saver::save(std::string name, char* buffer, uint len){
    // TODO: zrobić zapisywanie po kawałku bufora.
    std::cout<<"\nZapisywanie pliku '"+name+"' o wielkosci " + std::to_string(len)<<'\n';
    std::cout<<convertToString(buffer, len)<<'\n';
    return true;
}  