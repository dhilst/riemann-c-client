#include "query.h"

riemann_events_t *riemann_query_tcp_send(riemann_tcp_client_t *cli, char *qstr)
{
        Msg msg = MSG__INIT;
        Msg *resp = NULL;
        Query qry = QUERY__INIT;
        uint8_t *buf;
        size_t len;
        int error;
        ssize_t bytes;
        uint32_t resp_len;
        riemann_events_t *evts;

        qry.string = qstr;
        msg.query = &qry;
        buf = riemann_tcp_message_pack(&msg, &len);

        error = riemann_tcp_client_send(cli, buf, len, 0, NULL);
        if (error)  {
                fprintf(stderr, "query.c riemann_query_tcp_send(%d): riemann_tcp_client_send fails\n", __LINE__);
                return NULL;
        }
        
        error = riemann_tcp_client_recv(cli,(uint8_t *) &resp_len, sizeof(resp_len), 0, NULL, &bytes);
        if (error)  {
                fprintf(stderr, "query.c riemann_query_tcp_recv(%d): riemann_tcp_client_recv fails\n", __LINE__);
                return NULL;
        }

        free(buf);
        
        len = be32toh(resp_len);
        buf = malloc(len);
        if (!buf) {
                fprintf(stderr, "query.c riemann_query_tcp_recv(%d): malloc fails\n", __LINE__);
                return NULL;
        }

        error = riemann_tcp_client_recv(cli, buf, len, 0, NULL, &bytes);
        if (error)  {
                fprintf(stderr, "query.c riemann_query_tcp_recv(%d): riemann_tcp_client_recv fails\n", __LINE__);
                return NULL;
        }

        resp = msg__unpack(NULL, bytes, buf);
        if (!resp->ok) {
                fprintf(stderr, "query.c riemann_query_tcp_recv(%d): Message error %s\n", __LINE__, resp->error);
                return NULL;
        }

        evts = malloc(sizeof(riemann_events_t));
        if (!evts) {
                fprintf(stderr, "query.c riemann_query_tcp_recv(%d): malloc fails\n", __LINE__);
                return NULL;
        }

        evts->events = resp->events;
        evts->n_events = resp->n_events;

        return evts;
}


