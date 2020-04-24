#include <iostream>
#include <vector>
#include <string>

#include "./messages.hpp"
#include "./serializers.hpp"


extern int test_libcore(int x) {
  return x * 123;
};

MessageBuilder::MessageBuilder() {
  buffer_ = std::vector<u_int8_t>(DATA_OFFSET_);
  data_len_ = 0;
} 

void MessageBuilder::writeMessageType(u_int8_t code) {
  buffer_[0] = code;
};

void MessageBuilder::write(u_int8_t x) {
  buffer_.push_back(x);
  data_len_ += 1;
};

void MessageBuilder::write(int32_t x) {
  for (int i = 0; i < 4; i++)
    buffer_.push_back(x >> ((3 - i) * 8));
  data_len_ += 4;  
};

void MessageBuilder::write(u_int64_t x) {
  for (int i = 0; i < 8; i++)
    buffer_.push_back(x >> ((7 - i) * 8));
  data_len_ += 8;  
};
void MessageBuilder::write(char* buf, size_t size) {};
void MessageBuilder::write(std::string str) {};

std::vector<u_int8_t> MessageBuilder::build() {
  for (int i = 0; i < 4; i++) 
    buffer_[1 + i] = (data_len_ >> ((3 - i) * 8));
  return buffer_;
};


MessageParser::MessageParser(std::vector<u_int8_t>) {};

u_int8_t MessageParser::readMessageType() {};

u_int8_t MessageParser::readUInt8T() {};
u_int32_t MessageParser::readInt32T() {};
u_int64_t MessageParser::readUInt64T() {};
std::vector<u_int8_t> MessageParser::readBytes() {};
std::string MessageParser::readString() {};


extern std::vector<u_int8_t> SerializeOpenRequest(OpenRequest open_request) {
  u_int8_t message_type = static_cast<u_int8_t> (MessageType::OPEN_REQUEST);
  std::string path = open_request.path;
  int32_t oflag = open_request.oflag;
  int32_t mode = open_request.mode;

  MessageBuilder request_builder;
  request_builder.writeMessageType(message_type);
  request_builder.write(path);
  request_builder.write(oflag);
  request_builder.write(mode);

  std::vector<u_int8_t> byte_request = request_builder.build();
  return byte_request;
}

extern OpenRequest DeserializeToOpenRequest(std::vector<u_int8_t> byte_request) {
  MessageParser request_parser(byte_request);
  u_int8_t message_type = request_parser.readMessageType();
  std::string path = request_parser.readString();
  int32_t oflag = request_parser.readInt32T();
  int32_t mode = request_parser.readInt32T();

  OpenRequest open_request{path, oflag, mode};
  return open_request;
}

extern std::vector<u_int8_t> SerializeOpenResponse(OpenResponse open_response) {
  u_int8_t message_type = static_cast<u_int8_t> (MessageType::OPEN_RESPONSE);
  int32_t result = open_response.result;
  int32_t error = open_response.error;

  MessageBuilder request_builder;
  request_builder.writeMessageType(message_type);
  request_builder.write(result);
  request_builder.write(error);

  std::vector<u_int8_t> byte_request = request_builder.build();
  return byte_request;
}

extern OpenResponse DeserializeToOpenResponse(std::vector<u_int8_t> byte_response) {
  MessageParser request_parser(byte_response);
  u_int8_t message_type = request_parser.readMessageType();
  int32_t result = request_parser.readInt32T();
  int32_t error = request_parser.readInt32T();

  OpenResponse open_response{result, error};
  return open_response;
}