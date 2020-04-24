#include <vector>
#include <string>

#include "./messages.hpp"
#include "./serializers.hpp"


extern int test_libcore(int x) {
  return x * 123;
};

void MessageBuilder::writeMessageType(u_int8_t code) {};

void MessageBuilder::write(u_int8_t x) {};
void MessageBuilder::write(int32_t x) {};
void MessageBuilder::write(u_int64_t x) {};
void MessageBuilder::write(char* buf, size_t size) {};
void MessageBuilder::write(std::string str) {};

std::vector<char> MessageBuilder::build() {};


MessageParser::MessageParser(std::vector<char>) {};

u_int8_t MessageParser::readMessageType() {};

u_int8_t MessageParser::readUInt8T() {};
u_int32_t MessageParser::readInt32T() {};
u_int64_t MessageParser::readUInt64T() {};
std::vector<char> MessageParser::readBytes() {};
std::string MessageParser::readString() {};


extern std::vector<char> SerializeOpenRequest(OpenRequest open_request) {
  u_int8_t message_type = static_cast<u_int8_t> (MessageType::OPEN_REQUEST);
  std::string path = open_request.path;
  int32_t oflag = open_request.oflag;
  int32_t mode = open_request.mode;

  MessageBuilder request_builder;
  request_builder.writeMessageType(message_type);
  request_builder.write(path);
  request_builder.write(oflag);
  request_builder.write(mode);

  std::vector<char> byte_request = request_builder.build();
  return byte_request;
}

extern OpenRequest DeserializeToOpenRequest(std::vector<char> byte_request) {
  MessageParser request_parser(byte_request);
  u_int8_t message_type = request_parser.readMessageType();
  std::string path = request_parser.readString();
  int32_t oflag = request_parser.readInt32T();
  int32_t mode = request_parser.readInt32T();

  OpenRequest open_request{path, oflag, mode};
  return open_request;
}

extern std::vector<char> SerializeOpenResponse(OpenResponse open_response) {
  u_int8_t message_type = static_cast<u_int8_t> (MessageType::OPEN_RESPONSE);
  int32_t result = open_response.result;
  int32_t error = open_response.error;

  MessageBuilder request_builder;
  request_builder.writeMessageType(message_type);
  request_builder.write(result);
  request_builder.write(error);

  std::vector<char> byte_request = request_builder.build();
  return byte_request;
}

extern OpenResponse DeserializeToOpenResponse(std::vector<char> byte_response) {
  MessageParser request_parser(byte_response);
  u_int8_t message_type = request_parser.readMessageType();
  int32_t result = request_parser.readInt32T();
  int32_t error = request_parser.readInt32T();

  OpenResponse open_response{result, error};
  return open_response;
}