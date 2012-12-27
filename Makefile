objs := riemann_client.o common.o udp.o proto.pb-c.o

CFLAGS := -Wall -Werror

libriemann_client.so: $(objs)
	gcc $(CFLAGS) $(LDFLAGS) -shared -o libriemann_client.so $(objs) -lprotobuf-c

riemann_client.o: riemann_client.c proto.pb-c.[hc]
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c riemann_client.c

common.o: common.h common.c
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c common.c 

udp.o: udp.c udp.h
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c udp.c

proto.pb-c.o: proto.pb-c.[hc]
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c proto.pb-c.c

proto.pb-c.[hc]: proto.proto
	protoc-c --c_out=$(PWD) proto.proto

example.o: example.c riemann_client.h
	gcc $(CFLAGS) $(LDFLAGS) -c example.c 

test: libriemann_client.so example.o
	gcc -g -o test example.o $(CFLAGS) $(LDFLAGS) -L. -lriemann_client

clean:
	rm -f test *.o proto.pb-c.* *~ *.so
