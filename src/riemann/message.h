/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#ifndef RIEMANN_MESSAGE_H
# define RIEMANN_MESSAGE_H

#include <riemann/_config.h>
#include <riemann/query.h>
#include <riemann/event.h>
#include <riemann/proto.pb-c.h>

#ifdef RIEMANN_HAVE_STRING_H
# include <string.h>
#endif 

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
