#ifndef GET_HANDLER_H
#define GET_HANDLER_H
#include "../command.h"
#include "../saver.h"
#include "../reader.h"
#include "../connector.h"

bool get_handler(Command c, Saver *saver, Connector *);

bool put_handler(Command c, Reader *reader, Connector *);


#endif