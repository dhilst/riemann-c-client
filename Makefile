objs := riemann_client.o common.o proto.pb-c.o tcp.o
protofiles = proto.pb-c.h proto.pb-c.c

CFLAGS := -Wall -Werror

libriemann_client.so: $(objs)
	gcc $(CFLAGS) $(LDFLAGS) -shared -o libriemann_client.so $(objs) -lprotobuf-c

riemann_client.o: riemann_client.c riemann_client.h $(protofiles)
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c riemann_client.c

common.o: common.h common.c
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c common.c 

tcp.o: tcp.h tcp.c
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c tcp.c

proto.pb-c.o: $(protofiles)
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c proto.pb-c.c

$(protofiles): proto.proto
	protoc-c --c_out=$(PWD) proto.proto

example.o: example.c riemann_client.h
	gcc $(CFLAGS) $(LDFLAGS) -c example.c 

test: libriemann_client.so example.o
	gcc -g -o test example.o $(CFLAGS) $(LDFLAGS) -L. -lriemann_client

clean:
	rm -f test *.o proto.pb-c.* *~ *.so
