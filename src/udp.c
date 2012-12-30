#include "riemann/udp.h"

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

        bytes = sendto(cli->sock, buf, len, flags, cli->srv_addrinfo->ai_addr, cli->srv_addrinfo->ai_addrlen);
        if (bytes == -1) {
                return -1;
        }
        return 0;
}
