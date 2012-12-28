subdirs := examples
sources := client.c udp.c tcp.c message.c event.c query.c common.c riemann/proto.pb-c.c
objs := client.o udp.o tcp.o message.o event.o query.o common.o riemann/proto.pb-c.o

.PHONY : all
all : libriemann_client.so examples

libriemann_client.so : $(objs)
	gcc -Wall -Werror $(LDFLAGS) -shared -o libriemann_client.so $(objs) -lprotobuf-c

CFLAGS := -Wall -Werror -fPIC -I.
$(objs) : $(sources)

$(sources) : proto

.PHONY : proto
proto : 
	protoc-c --c_out=$(PWD)/riemann proto.proto

.PHONY : examples
examples : libriemann_client.so
	cd examples; $(MAKE)

clean :
	rm *.o riemann/proto.pb-c.[hco] libriemann_client.so || echo -n ""
	for d in $(subdirs) ; do \
		cd $$d; $(MAKE) clean ; \
	done

