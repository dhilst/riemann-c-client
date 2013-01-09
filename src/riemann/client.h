#ifndef RIEMANN_CLIENT_H
# define RIEMANN_CLIENT_H

#include <riemann/_config.h>

struct riemann_client_s {
#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_t mutex;
#endif
        int type;
        int sock;
        struct addrinfo *srv_addrinfo;
};

#include <netdb.h>
#include <riemann/message.h>

typedef struct riemann_client_s riemann_client_t;

enum c_types {
        TCP,
        UDP,
};

int riemann_client_init(riemann_client_t *cli);
int riemann_client_connect(riemann_client_t *cli, int type, char *hostname, int port);
void riemann_client_free(riemann_client_t *cli);
int riemann_client_send_message(riemann_client_t *cli, riemann_message_t *msg, int flags, struct timeval *tout);
riemann_message_t *riemann_client_recv_message(riemann_client_t *cli, int flags, struct timeval *tout);        

#endif
