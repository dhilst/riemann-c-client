# riemann-c-client-lib

O client library to rieman writen in C

## Download 
https://sites.google.com/site/gkoshwdir/home/files/libriemann_client-0.0.0.tar.gz

## Features
- TCP and UDP support for sending events
- TCP support for quering

## Dependencies
- Protobuf-c http://code.google.com/p/protobuf-c/

## @TODO
- Improve TCP code
  - Implement timeout (select)
- Improve error signaling, return kind of errno
- Improve UDP code
  - Does riemann responds UDP?
- Autotools
  - Add --with-libprotobuf-c=libprotobuf-c_DIR option to configure
  - Implement an alternative to getaddrinfo(), (gethostbyname!?)
    at compile time, using config.h
  - Start using config.h
  - Write INSTALL and README 
  - Improve checks (I haven't take a look on this yet)
    - Add failure when fails to link against protobuf-c 
- Implement locking system configurable at compile time. (./configure --with-thread_safe)
- Doxygen?
- Git log ChangeLog's.
- Test on this enviroments
  - AIX
  - Solaris
  - FreeBSD
  - CygWin
    - Add -no-undefined to libriemann_clients.* flags
  

## Install

WARNING: This is in really early stages, and was not fully tested.

1. Download and extract
```
# wget 'https://sites.google.com/site/gkoshwdir/home/files/libriemann_client-0.0.0.tar.gz' -O libriemann_client-0.0.0.tar.gz
# tar xf libriemann_client-0.0.0.tar.gz
```

2. Build
```
# cd libriemann_client-0.0.0
# ./configure
# make
```

3. Install
```
# sudo make install
```

## Usage
Include you the headers
```C
#include "riemann/event.h"
#include "riemann/message.h"
#include "riemann/client.h"
```

Create messages. Queries and Events are send attached in messages.
Also create a client, this will be your connection to riemann
server. riemann_client_connect() returns non-zero on failure.
```C
riemann_message_t msg = RIEMANN_MSG_INIT;
riemann_client_t cli = RIEMANN_CLIENT_INIT;
int error = riemann_client_connect(&cli, TCP, "localhost", 5555);
```

If you'll send events create the events and alloc them. There no
simpler way to send a sigle event. Check the returned pointers. NULL
means that malloc failed. Then set the event fields.
```C
riemann_event_t **events;
events = riemann_event_alloc_events(1);
events[0] = riemann_event_alloc_event();
riemann_event_set_host(events[0], "batcave");
riemann_event_set_service(events[0], "batservice");
riemann_event_set_metric_f(events[0], 1);
riemann_event_set_state(events[0], "ok");
```

Attach events to message
```C
riemann_message_set_events(&msg, events, 1);
```

Send the message! 3th parameter is flags to be passed to send() call,
4th parameter is a timeout struct(struct timeval), but this is not
implemented yet, so just passes NULL.
```C
error = riemann_client_send_message(&cli, &msg, 0, NULL);
```

If you want to make sure that server received your events, ask it for
a response.
```C
riemann_message_t *resp = NULL;
resp = riemann_client_recv_message(&cli, 0, NULL);
if (resp->ok)
   puts("SUCCESS"); /* your message was received with success */
```

Responses need to be freed. Also events and clients.
```C
riemann_message_free(resp);
riemann_events_free(events, n_events);
riemann_client_free(&cli);
```

When compiling your code, link it against libriemann_client
```
# cc -o your_program your_code.c -lriemann_client
```

For complete examples look at src/examples directory.







