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
  std::vector<u_int8_t> result = builder.build();
  std::vector<u_int8_t> expected = std::vector<u_int8_t>{1, 0, 0, 0, 1, 2};

  std::cout << (result == expected) << std::endl;
}