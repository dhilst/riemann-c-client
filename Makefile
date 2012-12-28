objs := riemann_client.o common.o proto.pb-c.o tcp.o query.o
protofiles = proto.pb-c.h proto.pb-c.c
CFLAGS := -Wall -Werror

.PHONY: all
all: libriemann_client.so examples

libriemann_client.so: $(objs)
	gcc $(CFLAGS) $(LDFLAGS) -shared -o libriemann_client.so $(objs) -lprotobuf-c

riemann_client.o: riemann_client.c riemann_client.h $(protofiles)
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c riemann_client.c

common.o: common.h common.c
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c common.c 

tcp.o: tcp.h tcp.c
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c tcp.c

query.o: query.h query.c
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c query.c	

proto.pb-c.o: $(protofiles)
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c proto.pb-c.c

$(protofiles): proto.proto
	protoc-c --c_out=$(PWD) proto.proto

.PHONY : examples
examples:
	cd examples; $(MAKE)

clean:
	rm -f test *.o proto.pb-c.* *~ *.so examples/{query_events,send_events,*.o}
