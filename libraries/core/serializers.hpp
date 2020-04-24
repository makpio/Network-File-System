#ifndef SERIALIZERS_HPP
#define SERIALIZERS_HPP

#include <vector>
#include <string>

#include "./messages.hpp"

extern int test_libcore(int x);

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
  void writeMessageType(u_int8_t code);

  void write(u_int8_t x);
  void write(int32_t x);
  void write(u_int64_t x);
  void write(char* buf, size_t size);
  void write(std::string str);

  std::vector<char> build();
};

class MessageParser {
public:
  MessageParser(std::vector<char>);

  u_int8_t readMessageType();

  u_int8_t readUInt8T();
  u_int32_t readInt32T();
  u_int64_t readUInt64T();
  std::vector<char> readBytes();
  std::string readString();
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
extern std::vector<char> SerializeOpenRequest(OpenRequest open_request);

extern OpenRequest DeserializeToOpenRequest(std::vector<char> byte_request);

/* byte_open_response data schema:

  - name: result
    type: int32_t
  - name: error
    type: int32_t
*/
extern std::vector<char> SerializeOpenResponse(OpenResponse open_response);

extern OpenResponse DeserializeToOpenResponse(std::vector<char> byte_response);

#endif
