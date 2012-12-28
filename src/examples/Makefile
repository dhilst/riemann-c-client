CFLAGS := -I../ -Wall -Werror
LDFLAGS := -L../ -lriemann_client

progs := exmp01 exmp02
objs := $(wildcard *.o)
sources := $(wildcard *.c)

.PHONY : all

all : $(progs)

$(progs) : $(objs)

$(objs) : $(sources)

clean :
	rm $(progs) *.o || echo -n ""
