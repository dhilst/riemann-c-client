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

uint8_t *riemann_message_to_tcp_buffer(riemann_message_t *msg, size_t *len)
{
        uint8_t *buf;
        uint32_t header;

        *len = msg__get_packed_size(msg);

        header = htobe32(*len);    /* header */
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
