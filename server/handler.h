#ifndef NFS_HANDLER_H
#define NFS_HANDLER_H

std::vector<u_int8_t> open_handler(std::vector<u_int8_t> byte_request);

std::vector<u_int8_t> read_handler(std::vector<u_int8_t> byte_request);

std::vector<u_int8_t> make_response(std::vector<u_int8_t> byte_request);

#endif //NFS_HANDLER_H
