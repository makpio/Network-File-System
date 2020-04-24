#include <iostream>
#include <sstream>
#include <cassert>

#include "../libraries/core/serializers.hpp"


int main() {
  std::vector<u_int8_t> data = std::vector<u_int8_t>{
    (u_int8_t) MessageType::CLOSE_REQUEST,
    0x00, 0x00, 0x00, 0x01,
    0x69
  };

  MessageParser parser = MessageParser(data);
  assert(parser.readMessageType() == MessageType::CLOSE_REQUEST);
  assert(parser.readSize() == 1);
  
  assert(parser.readUInt8T() == 0x69);
}