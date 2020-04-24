#include <iostream>
#include <sstream>

#include "../libraries/core/serializers.hpp"

std::string bytes_to_string(std::vector<u_int8_t> bytes) {
  std::stringstream sstream;
  for (std::vector<u_int8_t>::const_iterator i = bytes.begin(); i != bytes.end(); ++i)
    sstream << int(*i) << ' ';

  std::string result;
  getline(sstream, result);
  return result;
}

int main() {
  MessageBuilder builder;
  builder.writeMessageType(1);
  builder.write((u_int8_t) 2);
  builder.write((int32_t)0x12345678);
  builder.write((u_int64_t)0x1234567890ABCDEF);
  std::vector<u_int8_t> result = builder.build();
  std::vector<u_int8_t> expected = std::vector<u_int8_t>{
    0x01,
    0x00, 0x00, 0x00, 13,
    2,
    0x12, 0x34, 0x56, 0x78,
    0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF
  };
  
  std::cout << (result == expected) << std::endl;
}