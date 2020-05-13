#ifndef SAVER_H
#define SAVER_H
#include <string>
#include <iostream>

class Saver{
    public:
    virtual bool save(char* buffer, uint len)=0;
    virtual bool open(std::string name)=0;
    virtual void close()=0;
};

class Mock_saver: public Saver{
    public:
    Mock_saver():name_(std::string("")){};
    bool save(char* buffer, uint len);
    bool open(std::string name);
    void close();
    private:
    std::string name_;
};

#endif