#include <endian.h>

#include "riemann_client.h"
#include "proto.pb-c.h"
#include "tcp.h"

riemann_events_t *riemann_query_tcp_send(riemann_tcp_client_t *cli, char *qstr);
