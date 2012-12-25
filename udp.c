#include "common.h"
#include "udp.h"

int riemann_udp_client_create(riemann_udp_client_t *cli, const char* hostname, uint16_t port)
{
        int sock;
        int error;
        struct addrinfo saddr, *psaddr;

        if (cli->srv_addrinfo) {
                fprintf(stderr, "udp.c riemann_udp_client_create(%d): Called with a not initialized rieman_udp_client_t\n", __LINE__);
                return -3;
        }

        memset(&saddr, '\0', sizeof(saddr));
        saddr.ai_family = AF_INET;
        saddr.ai_socktype = SOCK_DGRAM;

        error = getaddrinfo(hostname, NULL, &saddr, &psaddr);

        if (error) {
                fprintf(stderr, "udp.c riemann_udp_client_create(%d): getaddrinfo: %s\n", __LINE__, gai_strerror(error));
                return -2;
        }

        sock = socket(psaddr->ai_family, psaddr->ai_socktype, 0);
        if (sock == -1) {
                fprintf(stderr, "udp.c riemann_udp_client_create(%d): Error while creating socket\n", __LINE__);
                return -1;
        }


        ((struct sockaddr_in *)psaddr->ai_addr)->sin_port = htons(port);
        cli->sock = sock;
        cli->srv_addrinfo = psaddr;
        return 0;
}

void riemann_udp_client_free(riemann_udp_client_t *cli)
{
        close(cli->sock);
        cli->sock = -1;
        freeaddrinfo(cli->srv_addrinfo);
        cli->srv_addrinfo = NULL;
}

int riemann_udp_client_send(riemann_udp_client_t *cli, uint8_t *data, size_t data_len, int flags)
{
        ssize_t bytes;

        assert(cli);
        assert(data);
        assert(data_len >= 0);

        bytes = sendto(cli->sock, data, data_len, flags, 
                       cli->srv_addrinfo->ai_addr, cli->srv_addrinfo->ai_addrlen);
        
        if (bytes == -1) {
                fprintf(stderr, "udp.c riemann_udp_client_send: Error while sending data to server");
                return -1;
        }
        return 0;
}

int riemann_udp_client_recv(riemann_udp_client_t *cli, uint8_t *data, size_t data_len, int flags)
{
        ssize_t bytes;
        assert(cli);
        assert(data);
        assert(data_len >= 0);
        
        bytes = recvfrom(cli->sock, data, data_len, flags, NULL, 0);
        if (bytes == -1) {
                fprintf(stderr, "udp.c:riemann_udp_client_recv: Error while receiving data from server");
                return -1;
        }
        return 0;
}
