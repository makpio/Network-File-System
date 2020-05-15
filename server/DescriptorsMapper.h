#ifndef NFS_DESCRIPTORSMAPPER_H
#define NFS_DESCRIPTORSMAPPER_H

#include <vector>
#include <unordered_map>

class DescriptorsMapper {
public:
    int operator[](int fd);
    int addDescriptor(int fd);
    void removeDescriptor(int fd);

private:
    // first -> descriptor on server, second -> descriptor on client
    std::unordered_map<int, int> mapper;

    int getLowestFreeDescriptor();
};
#endif //NFS_DESCRIPTORSMAPPER_H
