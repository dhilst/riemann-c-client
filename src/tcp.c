#include <riemann/_config.h> 
#include "riemann/tcp.h"        /* This header will not be installed so I use `"' */

int riemann_tcp_recv(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout, ssize_t *recv_bytes)
{
        ssize_t bytes;

        assert(cli);
        assert(buf);
        assert(len >= 0);

#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_lock(&cli->mutex);
#endif
        bytes = recv(cli->sock, buf, len, flags);
#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_unlock(&cli->mutex);
#endif
        if (bytes == -1) {
                fprintf(stderr, "tcp.c riemann_tcp_client_recv(%d): Error while receiving data from server: %s\n", __LINE__, strerror(errno));
                return -1;
        }

        if (recv_bytes)
                *recv_bytes = bytes;
        return 0;
}

int riemann_tcp_send(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout)
{
        ssize_t bytes;

        assert(cli);
        assert(buf);
        assert(len >= 0);

#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_lock(&cli->mutex);
#endif
        bytes = send(cli->sock, buf, len, flags);
#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_unlock(&cli->mutex);
#endif
      
        if (bytes == -1) {
                return -1;
        }

        return 0;
}

uint32_t riemann_tcp_recv_header(riemann_client_t *cli, int flags, struct timeval *tout)
{
        uint32_t header;
        int error;

        error = riemann_tcp_recv(cli, (uint8_t *) &header, sizeof(header), flags, tout, NULL);
        if (error)
                return -1;

        return header;
}

riemann_message_t *riemann_tcp_recv_message(riemann_client_t *cli, uint8_t *buf, size_t len)
{
        return NULL;
}

