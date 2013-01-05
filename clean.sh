#!/bin/sh

if test -f Makefile; then
    make distclean || exit -1
fi
rm -rf Makefile.in aclocal.m4 autom4te.cache/ config.guess config.h.in config.sub configure depcomp install-sh ltmain.sh missing src/Makefile.in src/examples/Makefile.in m4/* libriemann_client-*.tar.gz
