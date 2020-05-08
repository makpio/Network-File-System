#ifndef SAVER_H
#define SAVER_H
#include <string>
#include <iostream>

class Saver{
    public:
    virtual bool save(std::string name, char* buffer, uint len)=0;
};

class Mock_saver: public Saver{
    public:
    bool save(std::string name, char* buffer, uint len);
};

#endif