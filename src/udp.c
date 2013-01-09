#include <riemann/_config.h>
#include "riemann/udp.h"        /* This header will not be installed, so I use `"'. */

int riemann_udp_recv(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout, ssize_t *recv_bytes)
{
        return -1;              /* Not implemented */
}

int riemann_udp_send(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout)
{
        size_t bytes;

        assert(cli);
        assert(buf);
        assert(len >= 0);

#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_lock(&cli->mutex);
#endif
        bytes = sendto(cli->sock, buf, len, flags, cli->srv_addrinfo->ai_addr, cli->srv_addrinfo->ai_addrlen);
#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_unlock(&cli->mutex);
#endif
        if (bytes == -1) {
                return -1;
        }
        return 0;
}
