#include "tcp.h"

uint8_t* riemann_tcp_message_pack(Msg *msg, size_t *len)
{
        uint8_t *buf;
        uint32_t header;

        *len = msg__get_packed_size(msg);

        header = htobe32(*len);    /* header */
        buf = malloc(*len + sizeof(header));
        if (!buf) {
                fprintf(stderr, "riemann_client.c riemann_tcp_message_pack(%d): malloc() fails\n", __LINE__);
                return NULL;
        }

        memcpy(buf, &header, sizeof(header));
        msg__pack(msg, buf + sizeof(header));

        *len += sizeof(header);
        return buf;
}
        
uint8_t* riemann_tcp_events_pack(riemann_events_t *evts, size_t *len)
{
        Msg msg = MSG__INIT;
        uint8_t *buf;

        msg.events = evts->events;
        msg.n_events = evts->n_events;
        buf = riemann_tcp_message_pack(&msg, len);
        if (!buf) {
                fprintf(stderr, "tcp.c riemann_tcp_events_pack(%d): riemann_tcp_message_pack fails\n", __LINE__);
                return NULL;
        }

        return buf;
}
                        

int riemann_tcp_client_connect(riemann_tcp_client_t *cli, const char *hostname, uint16_t port)
{
        int sock;
        int error;
        struct addrinfo saddr, *psaddr;

        if (cli->srv_addrinfo) {
                fprintf(stderr, "tcp.c riemann_tcp_client_create(%d): Called with a not initialized rieman_tcp_client_t\n", __LINE__);
                return -1;
        }

                memset(&saddr, '\0', sizeof(saddr));
        saddr.ai_family = AF_INET;
        saddr.ai_socktype = SOCK_STREAM;

        error = getaddrinfo(hostname, NULL, &saddr, &psaddr);
        if (error) {
                fprintf(stderr, "tcp.c riemann_tcp_client_create(%d): getaddrinfo: %s\n", __LINE__, gai_strerror(error));
                return -2;
        }

        sock = socket(psaddr->ai_family, psaddr->ai_socktype, 0);
        if (sock == -1) {
                fprintf(stderr, "tcp.c riemann_tcp_client_create(%d): Error while creating socket\n", __LINE__);
                return -3;
        }

        ((struct sockaddr_in *)psaddr->ai_addr)->sin_port = htons(port);

        error = connect(sock, psaddr->ai_addr, psaddr->ai_addrlen);
        if (error) {
                fprintf(stderr, "tcp.c riemann_tcp_client_create(%d): Error while connecting socket: %s\n", __LINE__, strerror(errno));
                return -4;
        }

        cli->sock = sock;
        cli->srv_addrinfo = psaddr;

        return 0;
}

int riemann_tcp_client_send(riemann_tcp_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout)
{
        ssize_t bytes;

        assert(cli);
        assert(buf);
        assert(len >= 0);

        bytes = send(cli->sock, buf, len, flags);
        if (bytes == -1) {
                fprintf(stderr, "tcp.c riemann_tcp_client_send(%d): Error while sending data to server: %s\n", __LINE__, strerror(errno));
                return -1;
        }

        return 0;
}

int riemann_tcp_client_recv(riemann_tcp_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout, ssize_t *recv_bytes)
{
        ssize_t bytes;

        assert(cli);
        assert(buf);
        assert(len >= 0);

        bytes = recv(cli->sock, buf, len, flags);
        if (bytes == -1) {
                fprintf(stderr, "tcp.c riemann_tcp_client_recv(%d): Error while receiving data from server: %s\n", __LINE__, strerror(errno));
                return -1;
        }

        if (recv_bytes)
                *recv_bytes = bytes;
        return 0;
}

int riemann_tcp_client_recv_ack(riemann_tcp_client_t *cli, int flags, struct timeval *tout)
{
        uint8_t buf[65536];
        ssize_t bytes;
        Msg *msg;
        int error;

        error = riemann_tcp_client_recv(cli, buf, 65536, 0, NULL, &bytes);
        if (error) {
                fprintf(stderr, "tcp.c riemann_tcp_client_send_events(%d): riemann_tcp_client_recv fail\n", __LINE__);
                return -1;
        }

        if (bytes >= 65536) {
                fprintf(stderr, "tcp.c riemann_tcp_client_send_events(%d): riemann_tcp_client_recv buffer overflow\n", __LINE__);
                return -1;
        }                

        msg = msg__unpack(NULL, bytes, buf);
        if (!msg->ok) 
                fprintf(stderr, "tcp.c riemann_tcp_client_send_events(%d): Message error: %s", __LINE__, msg->error);

        return msg->ok;
}



int riemann_tcp_client_send_events(riemann_events_t *evts, riemann_tcp_client_t *cli, int flags, struct timeval *tout)
{
        uint8_t *buf;
        size_t len;
        int error;
        
        buf = riemann_tcp_events_pack(evts, &len);
        if (!buf) {
                fprintf(stderr, "tcp.c riemann_tcp_client_send_events(%d): riemann_tcp_events_pack fail\n", __LINE__);
                return -1;
        }
        
        error = riemann_tcp_client_send(cli, buf, len, flags, tout);
        if (error) {
                fprintf(stderr, "tcp.c riemann_tcp_client_send_events(%d): riemann_tcp_client_send fail\n", __LINE__);
                return -1;
        }

        return 0;
}

