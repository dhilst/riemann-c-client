subdirs := examples
sources := client.c udp.c tcp.c message.c event.c query.c common.c proto.pb-c.c
objs := client.o udp.o tcp.o message.o event.o query.o common.o proto.pb-c.o

.PHONY : all
all : libriemann_client.so examples

libriemann_client.so : $(objs)
	gcc $(CFLAGS) $(LDFLAGS) -shared -o libriemann_client.so $(objs) -lprotobuf-c

CFLAGS := -Wall -Werror -fPIC -I.
$(objs) : $(sources)

$(sources) : proto

.PHONY : proto
proto : 
	protoc-c --c_out=$(PWD) proto.proto

.PHONY : examples
examples : libriemann_client.so
	cd examples; $(MAKE)

clean :
	rm *.o proto.pb-c.[hc] libriemann_client.so || echo -n ""
	for d in $(subdirs) ; do \
		cd $$d; $(MAKE) clean ; \
	done

