#include <sys/types.h>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "handler.h"
#include "../libraries/core/serializers.hpp"


std::vector<u_int8_t> Handler::open_handler(std::vector<u_int8_t> byte_request) {
    std::cout << "OPEN" << std::endl;

    OpenRequest request = DeserializeToOpenRequest(byte_request);
    std::cout << "Request:" << std::endl;
    std::cout << "  path: " << request.path << std::endl;
    std::cout << "  oflag: " << request.oflag << std::endl;
    std::cout << "  mode: " << request.mode << std::endl;
    int result = open(request.path.c_str(), request.oflag, request.mode);

    int fileFd = mapper.addDescriptor(result);

    OpenResponse response = {fileFd, errno};
    std::cout << "Response:" << std::endl;
    std::cout << "  fd: " << response.result << std::endl;
    std::cout << "  error: " << response.error << std::endl;
    std::cout << std::endl;

    std::vector<u_int8_t> byte_response = SerializeOpenResponse(response);
    return byte_response;
}

std::vector<u_int8_t> Handler::read_handler(std::vector<u_int8_t> byte_request) {
    std::cout << "READ" << std::endl;

    ReadRequest request = DeserializeToReadRequest(byte_request);
    std::cout << "Request:" << std::endl;
    std::cout << "  fd: " << request.fd << std::endl;
    std::cout << "  count: " << request.count << std::endl;

    std::vector<u_int8_t> buf = std::vector<u_int8_t>(request.count);
    int result = read(request.fd, buf.data(), request.count);
    buf.resize(result);

    ReadResponse response = {result, buf, errno};
    std::cout << "Response:" << std::endl;
    std::cout << "  result: " << response.result << std::endl;
    std::cout << "  error: " << response.error << std::endl;
    std::cout << std::endl;

    std::vector<u_int8_t> byte_response = SerializeReadResponse(response);
    return byte_response;
}

std::vector<u_int8_t> Handler::authenticate_handler(std::vector<u_int8_t> byte_request){

}

std::vector<u_int8_t> Handler::make_response(std::vector<u_int8_t> byte_request) {
    MessageParser parser = MessageParser(byte_request);
    switch (parser.readMessageType()) {
        case MessageType::OPEN_REQUEST:
            return open_handler(byte_request);
        case MessageType::READ_REQUEST:
            return read_handler(byte_request);
        case MessageType::AUTHENTICATE_REQUEST:
            return authenticate_handler(byte_request);
        default:
            return std::vector<u_int8_t>{0, 0, 0, 0, 0};
    }
}