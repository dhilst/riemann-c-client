test: riemann_client.o common.o proto.pb-c.o example.c
	gcc -g -o test example.c $(CFLAGS) $(LDFLAGS) riemann_client.o -lprotobuf-c common.o proto.pb-c.o

riemann_client.o: riemann_client.c riemann_client.h common.o proto.pb-c.o
	gcc -c riemann_client.c

common.o: common.h common.c
	gcc -c common.c 

proto.pb-c.o: proto.pb-c.h proto.pb-c.c
	gcc -c proto.pb-c.c

proto.pb-c.c proto.pb-c.h: proto.proto
	protoc-c --c_out=$(PWD) proto.proto

clean:
	rm -f test *.o proto.pb-c.* *~
