SUBDIRS = . examples

AM_CFLAGS= -Wall -Werror

EXTRA_DIST = proto.proto
BUILT_SOURCES = riemann/proto.pb-c.h riemann/proto.pb-c.c
lib_LTLIBRARIES = libriemann_client.la
libriemann_client_la_SOURCES = client.c  common.c  event.c  message.c  query.c  tcp.c  udp.c riemann/proto.pb-c.c
libriemann_client_la_LDFLAGS = $(WITH_LOCK_LDFLAGS) $(PROTOBUF_C_LDFLAGS) -lprotobuf-c -version-info 2:0:0 -no-undefined 
libriemann_client_la_CFLAGS = $(PROTOBUF_C_CFLAGS)
nobase_include_HEADERS =  riemann/message.h riemann/event.h riemann/query.h riemann/client.h riemann/proto.pb-c.h

riemann/proto.pb-c.h riemann/proto.pb-c.c : proto.proto
	protoc-c --c_out=$(CURDIR)/riemann proto.proto
