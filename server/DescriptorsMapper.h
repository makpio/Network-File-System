#ifndef NFS_DESCRIPTORSMAPPER_H
#define NFS_DESCRIPTORSMAPPER_H

#include <vector>
#include <unordered_map>

class DescriptorsMapper {
public:
    int operator[](int key);
    void addDescritor(int key, int value);

private:
    std::unordered_map<int, int> mapper;

    int getLowestDescriptor();


};
#endif //NFS_DESCRIPTORSMAPPER_H
