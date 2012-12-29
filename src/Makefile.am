SUBDIRS = . examples

BUILT_SOURCES = riemann/proto.pb-c.h riemann/proto.pb-c.c
lib_LTLIBRARIES = libriemann_client.la
libriemann_client_la_SOURCES = client.c  common.c  event.c  message.c  query.c  tcp.c  udp.c riemann/proto.pb-c.c
libriemann_client_la_LD_FLAGS = -lprotobuf-c
include_HEADERS = riemann/udp.h riemann/common.h riemann/message.h riemann/event.h riemann/tcp.h riemann/query.h riemann/client.h

riemann/proto.pb-c.h riemann/proto.pb-c.c : proto.proto
	protoc-c --c_out=$(CURDIR)/riemann proto.proto
