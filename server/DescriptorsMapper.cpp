#include "DescriptorsMapper.h"

int DescriptorsMapper::operator[](int key) {
    if(mapper.find(key) != mapper.end())
        return mapper[key];
    else
        throw std::out_of_range("Descriptor does not exists");
}

void DescriptorsMapper::addDescritor(int key, int value) {
    if(mapper.find(key) != mapper.end())
        throw std::invalid_argument("Descriptor already exists");
    else
        mapper[key] = value;
}

int DescriptorsMapper::getLowestDescriptor() {
    return 0;
}
