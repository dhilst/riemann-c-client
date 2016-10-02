/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#include <riemann/_config.h> 
#include "riemann/tcp.h"        /* This header will not be installed so I use `"' */

int riemann_tcp_recv(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout, ssize_t *recv_bytes)
{
        ssize_t bytes;
#ifdef RIEMANN_WITH_TIMEOUT
        fd_set fds;
        int rc;
#endif

        assert(cli);
        assert(buf);
        assert(len >= 0);

#ifdef RIEMANN_WITH_TIMEOUT
        FD_ZERO(&fds);
        FD_SET(cli->sock, &fds);
        rc = select(cli->sock + 1, &fds, NULL, NULL, tout);
        if (rc == -1) {
                return -2;
        } else if (rc == 0) {
                return -3;      /* Timeout */
        }
                
        if (FD_ISSET(cli->sock, &fds)) {
#endif
                bytes = recv(cli->sock, buf, len, flags);
#ifdef RIEMANN_WITH_TIMEOUT
        } else { 
                return -4;      /* Should not happen  */
        }/* if (FD_ISSET(cli->sock, &fds)) { */
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
#ifdef RIEMANN_WITH_TIMEOUT
        fd_set fds;
        int rc;
#endif

        assert(cli);
        assert(buf);
        assert(len >= 0);

#ifdef RIEMANN_WITH_TIMEOUT
        FD_ZERO(&fds);
        FD_SET(cli->sock, &fds);
        rc = select(cli->sock + 1, NULL, &fds, NULL, tout);
        if (rc == -1) {
                return -2;
        } else if (rc == 0) {
                return -3;      /* Timeout */
        }
                
        if (FD_ISSET(cli->sock, &fds)) {
#endif
        bytes = send(cli->sock, buf, len, flags);
#ifdef RIEMANN_WITH_TIMEOUT
        } else { 
                return -4;      /* Should not happen  */
        }/* if (FD_ISSET(cli->sock, &fds)) { */
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

