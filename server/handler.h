#ifndef NFS_HANDLER_H
#define NFS_HANDLER_H

#include "DescriptorsMapper.h"
#include "../libraries/core/messages.hpp"

class Handler {
public:
    AuthenticateResponse authenticate_handler(std::vector<u_int8_t> byte_request);
    std::vector<u_int8_t> open_handler(std::vector<u_int8_t> byte_request);
    std::vector<u_int8_t> read_handler(std::vector<u_int8_t> byte_request);
    std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request);

private:
    int authenticate(std::string username, std::size_t passwordHash);

    DescriptorsMapper mapper;
    const static std::string shadowFilePath;
};



#endif //NFS_HANDLER_H
