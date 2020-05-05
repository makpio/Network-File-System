#ifndef SERIALIZERS_HPP
#define SERIALIZERS_HPP

#include <vector>
#include <string>

#include "./messages.hpp"

extern int test_libcore(int x);

const size_t MESSAGE_TYPE_OFFSET_ = 0;
const size_t DATA_SIZE_OFFSET_ = 1;
const size_t DATA_OFFSET_ = 5;

/* message schema:

- name: message_type
  type: u_int8_t
- name: data_size
  type: u_int32_t
- name: data
  len: char[`data_size`]
*/
class MessageBuilder {
public:
  MessageBuilder();

  void writeMessageType(MessageType type);

  void write(u_int8_t x);
  void write(int32_t x);
  void write(u_int32_t x);
  void write(u_int64_t x);
  void write(char* buf, size_t size);
  void write(std::string str);

  std::vector<u_int8_t> build();

private:
  std::vector<u_int8_t> buffer_;
  size_t data_len_;
};

class MessageParser {
public:
  MessageParser(std::vector<u_int8_t>);

  MessageType readMessageType();
  int32_t readSize();

  u_int8_t readUInt8T();
  int32_t readInt32T();
  u_int32_t readUInt32T();
  u_int64_t readUInt64T();
  std::vector<u_int8_t> readBytes();
  std::string readString();

private:
  std::vector<u_int8_t> buffer_;
  size_t next_data_;
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
extern std::vector<u_int8_t> SerializeOpenRequest(OpenRequest open_request);
extern OpenRequest DeserializeToOpenRequest(std::vector<u_int8_t> byte_request);

/* byte_open_response data schema:

  - name: result
    type: int32_t
  - name: error
    type: int32_t
*/
extern std::vector<u_int8_t> SerializeOpenResponse(OpenResponse open_response);
extern OpenResponse DeserializeToOpenResponse(std::vector<u_int8_t> byte_response);


/* byte_open_request data schema:

- name: fd
  type: int32_t
- name: count
  type: int32_t
*/
extern std::vector<u_int8_t> SerializeReadRequest(ReadRequest read_request);
extern ReadRequest DeserializeToReadRequest(std::vector<u_int8_t> byte_request);

/* byte_open_response data schema:

  - name: result
    type: int32_t
  - name: error
    type: int32_t
*/
extern std::vector<u_int8_t> SerializeReadResponse(ReadResponse read_response);
extern ReadResponse DeserializeToReadResponse(std::vector<u_int8_t> byte_response);

#endif
