#ifndef NFS_DESCRIPTORSMAPPER_H
#define NFS_DESCRIPTORSMAPPER_H

#include <vector>
#include <map>

class DescriptorsMapper {
public:
    int operator[](int fd);
    int addDescriptor(int fd);
    void removeDescriptor(int fd);

private:
    // first -> descriptor on client, second -> descriptor on server
    std::map<int, int> mapper;
    int getLowestFreeDescriptor();
};
#endif //NFS_DESCRIPTORSMAPPER_H
