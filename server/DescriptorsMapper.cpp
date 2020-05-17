#include <algorithm>
#include "DescriptorsMapper.h"

int DescriptorsMapper::operator[](int fd) {
    if(mapper.find(fd) != mapper.end())
        return mapper[fd];
    else
        throw std::out_of_range("Descriptor does not exists");
}
int DescriptorsMapper::addDescriptor(int fd) {
    int lowestFreeFd = getLowestFreeDescriptor();
    mapper[lowestFreeFd] = fd;
    return lowestFreeFd;
}
void DescriptorsMapper::removeDescriptor(int fd) {
    if(mapper.find(fd) != mapper.end())
        mapper.erase(fd);
    else
        throw std::out_of_range("Descriptor does not exists");
}
int DescriptorsMapper::getLowestFreeDescriptor() {
    int i = 1;
    while(mapper.find(i) != mapper.end())
        ++i;
    return i;
}
