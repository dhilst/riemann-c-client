#ifndef RIEMANN_MESSAGE_H
# define RIEMANN_MESSAGE_H

#include <string.h>

#include "riemann/query.h"
#include "riemann/event.h"
#include "riemann/proto.pb-c.h"

typedef Msg riemann_message_t;

#define RIEMANN_MSG_INIT MSG__INIT

void riemann_message_set_query(riemann_message_t *msg,
                               riemann_query_t *query);
void riemann_message_set_events(riemann_message_t *msg, 
                               riemann_event_t **evts, 
                               size_t n_events);
void riemann_message_free(riemann_message_t *msg);        
uint8_t *riemann_message_to_buffer(riemann_message_t *msg, size_t *len);
uint8_t *riemann_message_to_tcp_buffer(riemann_message_t *msg, size_t *len);
riemann_message_t *riemann_buf_to_message(uint8_t *buf, size_t len);

#endif
