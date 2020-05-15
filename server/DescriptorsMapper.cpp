#include "DescriptorsMapper.h"

int DescriptorsMapper::operator[](int fd) {
    if(mapper.find(fd) != mapper.end())
        return mapper[fd];
    else
        throw std::out_of_range("Descriptor does not exists");
}
int DescriptorsMapper::addDescriptor(int fd) {
    if(mapper.find(fd) != mapper.end())
        throw std::invalid_argument("Descriptor already exists");
    else
        mapper[fd] = getLowestFreeDescriptor();
    return mapper[fd];
}
void DescriptorsMapper::removeDescriptor(int fd) {
    if(mapper.find(fd) != mapper.end())
        mapper.erase(fd);
    else
        throw std::out_of_range("Descriptor does not exists");
}
int DescriptorsMapper::getLowestFreeDescriptor() {
    for()
}
