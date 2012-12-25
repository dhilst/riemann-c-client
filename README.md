# riemann-c-client-lib

O client library to rieman writen in C

# @TODO


- Improve UDP code
  - Implement send with ack
- Implement Queries
- Improve error signaling, return kind of errno
  instead of fprintfing everthing to stderr
- Port to libtools
- Implement TCP code
- Doxygen?
- Improve installation instructions 


# Instalation

WARNING: This is in really early stages, and was not fully tested.

1. Clone
```
git clone https://github.com/gkos/riemann-c-client-lib.git
```

2. Build

You need protobuf-c installed and on your path to do this. You can find it at http://code.google.com/p/protobuf-c/
```
make
```
This will create the libriemann_client.so

3. Install!?

This is not yet implemented, but you can move libriemann_client.so to your /usr/local/lib and use it from there.

# Usage

```C
#include <stdio.h>
#include <stdlib.h>
#include "riemann_client.h"

static char *hosts[] = {
        "host-0",
        "host-1",
        "host-2",
        "host-3",
        "host-4",
        "host-5",
        "host-6",
        "host-7",
        "host-8",
        "host-9",
};

int main(void)
{
        riemann_udp_client_t cli;
        riemann_events_t events;
        riemann_event_t *evtp;
        char *tags[] = { "cpu", "performance", "load", };
        int n_tags;
        int error;
        int i;

        error = riemann_events_init(&events, 10); /* alloc space and initialize N events */
        if (error) {
                fprintf(stderr, "Can't allocate events: %d\n", error);
                exit(EXIT_FAILURE);
        }
        
        n_tags = sizeof(tags) / sizeof(tags[0]); /* number of tags */
        FOR_EACH_EVENT(events, i, evtp) {
                riemann_event_set_host(evtp, hosts[i]);
                riemann_event_set_service(evtp, "cpu-idle");
                riemann_event_set_state(evtp, "ok");
                riemann_event_set_metric_f(evtp, 100l);
                riemann_event_set_tags(evtp, tags, n_tags);
                riemann_event_set_description(evtp, "Percent cpu idle time");
        }

        cli = RIEMANN_UDP_CLIENT_INIT;
        error = riemann_udp_client_create(&cli, "192.168.5.36", 5555);
        if (error) {
                fprintf(stderr, "Can't create UDP client\n");
                exit(EXIT_FAILURE);
        }

        error = riemann_events_send_udp(&cli, &events);
        if (error) {
                fprintf(stderr, "Can't send data to UDP server\n");
                exit(EXIT_FAILURE);
        }

        riemann_udp_client_free(&cli);
        riemann_events_free(&events);
        return 0;
}
```

- Compiling

When compiling you will need to link your code against libriemann_client.so
```
gcc -o your_bin your_code.c -lriemann_client        
```

