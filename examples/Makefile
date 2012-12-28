CFLAGS := -I../
LDFLAGS := -L../ -lriemann_client

.PHONY : all
all: query_events send_events
query_events: query_events.o 
send_events: send_events.o
query_events.o: query_events.c
send_events.o: send_events.c

