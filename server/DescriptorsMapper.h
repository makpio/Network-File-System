#ifndef NFS_DESCRIPTORSMAPPER_H
#define NFS_DESCRIPTORSMAPPER_H

#include <vector>
#include <unordered_map>


class DescriptorsMapper {
public:
    int operator[](int key){
        if(mapper.find(key) != mapper.end())
            return mapper[key];
        else
            throw std::out_of_range("Descriptor does not exists");
    }

    void addDescritor(int key, int value){
        if(mapper.find(key) != mapper.end())
            throw std::invalid_argument("Desriptor already exists");

    }

private:
    std::unordered_map<int, int> mapper;


};


#endif //NFS_DESCRIPTORSMAPPER_H
