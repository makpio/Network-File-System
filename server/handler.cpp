#include <sys/types.h>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include "handler.h"
#include "../libraries/core/serializers.hpp"

const std::string Handler::shadowFilePath = "../server/shadowfile.txt";

AuthenticateResponse Handler::authenticate_handler(std::vector<u_int8_t> byte_request){
    std::cout << "AUTHENTICATE" << std::endl;

    AuthenticateRequest request = DeserializeAuthenticateRequest(byte_request);
    std::cout << "Request:" << std::endl;
    std::cout << "  username: " << request.username << std::endl;

    std::size_t passwordHash = std::hash<std::string>{}(request.password);

    int result = authenticate(request.username, passwordHash);
    AuthenticateResponse response = {result, errno};

    std::cout << "Response:" << std::endl;
    std::cout << "  result: " << response.result << std::endl;
    std::cout << "  error: " << response.error << std::endl;
    std::cout << std::endl;

    return response;
}

int Handler::authenticate(std::string username, std::size_t passwordHash){
    std::ifstream infile(shadowFilePath);
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string name;
        std::size_t pass;
        if (!(iss >> name >> pass))
            break;
        if(username.compare(name) == 0) {
            if(pass == passwordHash)
                return 0;
            else
                return 1;
        }
    }
    return 2;
}

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
    int result;
    std::vector<u_int8_t> buf = std::vector<u_int8_t>(request.count);
    try {
        int server_fd = mapper[request.fd];
        result = read(server_fd, buf.data(), request.count);
        buf.resize(result);
    }
    catch (std::out_of_range&) {
        result = -1;
        errno = 1;
    }
    ReadResponse response = {result, buf, errno};
    std::cout << "Response:" << std::endl;
    std::cout << "  result: " << response.result << std::endl;
    std::cout << "  error: " << response.error << std::endl;
    std::cout << std::endl;

    std::vector<u_int8_t> byte_response = SerializeReadResponse(response);
    return byte_response;
}

std::vector<u_int8_t> Handler::make_response(std::vector<u_int8_t> byte_request) {
    MessageParser parser = MessageParser(byte_request);
    switch (parser.readMessageType()) {
        case MessageType::OPEN_REQUEST:
            return open_handler(byte_request);
        case MessageType::READ_REQUEST:
            return read_handler(byte_request);
        default:
            return std::vector<u_int8_t>{0, 0, 0, 0, 0};
    }
}