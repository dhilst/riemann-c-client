SUBDIRS = . examples

lib_LTLIBRARIES = libriemann_client.la
libriemann_client_la_SOURCES = client.c  common.c  event.c  message.c  query.c  tcp.c  udp.c
include_HEADERS = riemann/udp.h riemann/common.h riemann/message.h riemann/event.h riemann/tcp.h riemann/query.h riemann/client.h


riemann/proto.pb-c[hc] : proto.proto
	protoc-c --c_out=$(CURDIR)/riemann proto.proto
