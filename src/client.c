#include <riemann/_config.h>

#include <arpa/inet.h>

#ifdef RIEMANN_WITH_LOCK
# include <pthread.h>
#endif

#include "riemann/tcp.h"
#include "riemann/udp.h"
#include "riemann/client.h"


int riemann_client_init(riemann_client_t *cli)
{
        int error;
#ifdef RIEMANN_WITH_LOCK
        pthread_mutexattr_t attr;
#endif
        /* Like old macro */
        cli->sock = -1;          
        cli->srv_addrinfo = NULL;

#ifdef RIEMANN_WITH_LOCK
        error = pthread_mutexattr_init(&attr);
        if (error)
                return error;
        
        error = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        if (error)
                return error;

        error = pthread_mutex_init(&cli->mutex, &attr);
        if (error)
                return error;
#endif

        return 0;
}

int riemann_client_connect(riemann_client_t *cli, int type, char *hostname, int port)
{
        int sock;
        int error;
        struct addrinfo saddr, *psaddr;

        assert(!cli->srv_addrinfo);
        assert(cli->sock == -1);

        memset(&saddr, '\0', sizeof(saddr));
        saddr.ai_family = AF_INET;

        if (type == TCP) {
                saddr.ai_socktype = SOCK_STREAM;
        } else if (type == UDP) {
                saddr.ai_socktype = SOCK_DGRAM;
        } else
                return -1;

        error = getaddrinfo(hostname, NULL, &saddr, &psaddr);
        if (error) {
                return error;
        }

        sock = socket(psaddr->ai_family, psaddr->ai_socktype, 0);
        if (sock == -1) {
                return -3;
        }

        ((struct sockaddr_in *)psaddr->ai_addr)->sin_port = htons(port);

        error = connect(sock, psaddr->ai_addr, psaddr->ai_addrlen);
        if (error) {
                return -4;
        }

        cli->type = type;
        cli->sock = sock;
        cli->srv_addrinfo = psaddr;
        return 0;
}

void riemann_client_free(riemann_client_t *cli)
{
        cli->type = -1;
        cli->sock = -1;
        if (cli->srv_addrinfo) {
                freeaddrinfo(cli->srv_addrinfo);
                cli->srv_addrinfo = NULL;
        }

#ifdef RIEMANN_WITH_LOCK
        pthread_mutex_destroy(&cli->mutex);
#endif
}

int riemann_client_send_message(riemann_client_t *cli, riemann_message_t *msg, int flags, struct timeval *tout)
{
        size_t len;
        uint8_t *buf;
        int error;

        if (cli->type == TCP) {
                buf = riemann_message_to_tcp_buffer(msg, &len);
                if (!buf)
                        return -1;

                error = riemann_tcp_send(cli, buf, len, flags, tout);
                if (error)
                        return -2;

                return 0;
                
        } else if (cli->type == UDP) {
                buf = riemann_message_to_buffer(msg, &len);
                if (!buf)
                        return -3;

                error = riemann_udp_send(cli, buf, len, flags, tout);
                if (error)
                        return -4;

                return 0;
        } else {
                return -8;
        }
        return -15;
}

riemann_message_t *riemann_client_recv_message(riemann_client_t *cli, int flags, struct timeval *tout)
{
        riemann_message_t *msg;
        uint8_t *buf;
        size_t len;
        ssize_t bytes_recv;
        uint32_t header;
        int error;

        if (cli->type == TCP) {
                header = riemann_tcp_recv_header(cli, flags, tout);
                if (header == -1)
                        return NULL;

                len = ntohl(header);
                buf = malloc(len);
                assert(buf);

                error = riemann_tcp_recv(cli, buf, len, flags, tout, &bytes_recv);
                if (error)
                        return NULL;

                msg = riemann_buf_to_message(buf, len);
                if (!msg)
                        return NULL;

                return msg;
        } else if (cli->type == UDP) {
                return NULL;      /* Not implemented */
        } else {
                return NULL;
        }
}        

