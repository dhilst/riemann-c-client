libriemann_client.so: riemann_client.o common.o proto.pb-c.o
	gcc $(CFLAGS) $(LDFLAGS) -Wall -Werror -shared -o libriemann_client.so riemann_client.o common.o proto.pb-c.o -lprotobuf-c

riemann_client.o: riemann_client.c riemann_client.h proto.pb-c_files
	gcc $(CFLAGS) $(LDFLAGS) -Wall -Werror -fPIC -c riemann_client.c

common.o: common.h common.c
	gcc $(CFLAGS) $(LDFLAGS) -Wall -Werror -fPIC -c common.c 

proto.pb-c.o: proto.pb-c_files
	gcc $(CFLAGS) $(LDFLAGS) -fPIC -c proto.pb-c.c

proto.pb-c_files: proto.proto
	protoc-c --c_out=$(PWD) proto.proto

test: libriemann_client.so
	gcc -g -o test example.c $(CFLAGS) $(LDFLAGS) -L. -lriemann_client

clean:
	rm -f test *.o proto.pb-c.* *~ *.so
