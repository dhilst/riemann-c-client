#ifndef RIEMANN_CLIENT_H
# define RIEMANN_CLIENT_H

#include <netdb.h>

#include "riemann/message.h"

struct riemann_client_s {
        int type;
        int sock;
        struct addrinfo *srv_addrinfo;
        
};
typedef struct riemann_client_s riemann_client_t;

enum c_types {
        TCP,
        UDP,
};

#include "riemann/tcp.h"
#include "riemann/udp.h"

#define RIEMANN_CLIENT_INIT ((riemann_client_t){ -1, -1, NULL })

int riemann_client_connect(riemann_client_t *cli, int type, char *hostname, int port);
void riemann_client_free(riemann_client_t *cli);
int riemann_client_send_message(riemann_client_t *cli, riemann_message_t *msg, int flags, struct timeval *tout);
riemann_message_t *riemann_client_recv_message(riemann_client_t *cli, int flags, struct timeval *tout);        

#endif
