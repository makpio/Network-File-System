#ifndef NFS_HANDLER_H
#define NFS_HANDLER_H

#include "DescriptorsMapper.h"

class Handler {
public:
    std::vector<u_int8_t> open_handler(std::vector<u_int8_t> byte_request);
    std::vector<u_int8_t> read_handler(std::vector<u_int8_t> byte_request);
    std::vector<u_int8_t> authenticate_handler(std::vector<u_int8_t> byte_request);
    std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request);

private:
    DescriptorsMapper mapper;
};



#endif //NFS_HANDLER_H
