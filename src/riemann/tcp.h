/*
 * Copyright 2016, Daniel Hilst Selli <danielhilst@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
#ifndef RIEMANN_TCP_H
# define RIEMANN_TCP_H
#include <riemann/_config.h>

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

#include <riemann/client.h>

int riemann_tcp_recv(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout, ssize_t *recv_bytes);
int riemann_tcp_send(riemann_client_t *cli, uint8_t *buf, size_t len, int flags, struct timeval *tout);
uint32_t riemann_tcp_recv_header(riemann_client_t *cli, int flags, struct timeval *tout);
riemann_message_t *riemann_tcp_recv_message(riemann_client_t *cli, uint8_t *buf, size_t len);
        
#endif
