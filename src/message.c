/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#include <arpa/inet.h>

#include "riemann/message.h"

void riemann_message_set_query(riemann_message_t *msg,
                               riemann_query_t *query)
{
        assert(msg);
        assert(query);
        
        msg->query = query;
}


void riemann_message_set_events(riemann_message_t *msg, 
                               riemann_event_t **evts, 
                               size_t n_events)
{
        assert(msg);
        assert(evts);
        assert(n_events >= 0);

        msg->events = evts;
        msg->n_events = n_events;
}

void riemann_message_free(riemann_message_t *msg)
{
        assert(msg);
        
        msg__free_unpacked(msg, NULL);
}        

uint8_t *riemann_message_to_buffer(riemann_message_t *msg, size_t *len)
{
        uint8_t *buf; 
        
        *len = msg__get_packed_size(msg);
        buf = malloc(*len);
        assert(buf);
        msg__pack(msg, buf);
        return buf;
}

uint8_t *riemann_message_to_tcp_buffer(riemann_message_t *msg, size_t *len)
{
        uint8_t *buf;
        uint32_t header;

        *len = msg__get_packed_size(msg);

        header = htonl(*len);    /* header */
        buf = malloc(*len + sizeof(header));
        assert(buf);

        memcpy(buf, &header, sizeof(header));
        msg__pack(msg, buf + sizeof(header));

        *len += sizeof(header);
        return buf;
}

riemann_message_t *riemann_buf_to_message(uint8_t *buf, size_t len)
{
        return (msg__unpack(NULL, len, buf));
}
