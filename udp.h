#ifndef RIEMANN_UDP_H
# define RIEMANN_UDP_H

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "riemann_client.h"

int riemann_udp_client_send(riemann_udp_client_t *cli, uint8_t *data, size_t data_len, int flags);

#endif 
