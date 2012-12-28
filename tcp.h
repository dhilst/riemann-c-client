#ifndef RIEMANN_TCP_H 
# define RIEMANN_TCP_H

#include <assert.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "riemann_client.h"
#include "proto.pb-c.h"

struct riemann_tcp_client_s {
        int sock;
        struct addrinfo *srv_addrinfo;
};
typedef struct riemann_tcp_client_s riemann_tcp_client_t;

#define RIEMANN_TCP_CLIENT_INIT \
        (riemann_tcp_client_t) { .sock = -1,     \
                        .srv_addrinfo = NULL }

uint8_t* riemann_tcp_events_pack2(riemann_events_t *evts, size_t *len);
uint8_t* riemann_tcp_message_pack(Msg *msg, size_t *len);
int riemann_tcp_client_recv_ack(riemann_tcp_client_t *cli, int flags, struct timeval *tout);
uint8_t* riemann_tcp_events_pack(riemann_events_t *evts, size_t *len);
int riemann_tcp_client_connect(riemann_tcp_client_t *cli, const char *hostname, uint16_t port);
int riemann_tcp_client_send(riemann_tcp_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout);
int riemann_tcp_client_recv(riemann_tcp_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout, ssize_t *recv_bytes);
int riemann_tcp_client_send_events(riemann_events_t *evts, riemann_tcp_client_t *cli, int flags, struct timeval *tout);

#endif 
