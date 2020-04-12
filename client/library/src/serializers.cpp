#ifndef SERIALIZERS_CPP
#define SERIALIZERS_CPP

#include <vector>
#include <string>

#include "./messages.cpp"

/* message schema:

- name: message_type
  type: u_int8_t
- name: data_size
  type: u_int64_t
- name: data
  len: char[`data_size`]
*/
class MessageBuilder {
public:
  void writeMessageType(u_int8_t code) {};

  void write(u_int8_t x) {};
  void write(int32_t x) {};
  void write(u_int64_t x) {};
  void write(char* buf, size_t size) {};
  void write(std::string str) {};

  std::vector<char> build() {};
};

class MessageParser {
public:
  MessageParser(std::vector<char>) {};

  u_int8_t readMessageType() {};

  u_int8_t readUInt8T() {};
  u_int32_t readInt32T() {};
  u_int64_t readUInt64T() {};
  std::vector<char> readBytes() {};
  std::string readString() {};
};

/* byte_open_request data schema:

- name: path_size
  type: u_int8_t
- name: path
  type: char[`path_size`]
- name: oflag
  type: int32_t
- name: mode
  type: int32_t
*/
std::vector<char> SerializeOpenRequest(OpenRequest open_request) {
  u_int8_t message_type = OPEN_REQUEST_CODE;
  std::string path = open_request.path;
  int32_t oflag = open_request.oflag;
  int32_t mode = open_request.mode;

  MessageBuilder request_builder;
  request_builder.writeMessageType(OPEN_REQUEST_CODE);
  request_builder.write(path);
  request_builder.write(oflag);
  request_builder.write(mode);

  std::vector<char> byte_request = request_builder.build();
  return byte_request;
}

OpenRequest DeserializeToOpenRequest(std::vector<char> byte_request) {
  MessageParser request_parser(byte_request);
  u_int8_t message_type = request_parser.readMessageType();
  std::string path = request_parser.readString();
  int32_t oflag = request_parser.readInt32T();
  int32_t mode = request_parser.readInt32T();

  OpenRequest open_request{path, oflag, mode};
  return open_request;
};

/* byte_open_response data schema:

  - name: result
    type: int32_t
  - name: error
    type: int32_t
*/
std::vector<char> SerializeOpenResponse(OpenResponse open_response) {
  int32_t result = open_response.result;
  int32_t error = open_response.error;

  MessageBuilder request_builder;
  request_builder.writeMessageType(OPEN_RESPONSE_CODE);
  request_builder.write(result);
  request_builder.write(error);

  std::vector<char> byte_request = request_builder.build();
  return byte_request;
}

OpenResponse DeserializeToOpenResponse(std::vector<char> byte_response) {
  MessageParser request_parser(byte_response);
  u_int8_t message_type = request_parser.readMessageType();
  int32_t result = request_parser.readInt32T();
  int32_t error = request_parser.readInt32T();

  OpenResponse open_response{result, error};
  return open_response;
}

#endif
