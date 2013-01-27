#!/bin/sh


# OSX uses glibtoolize for gnu libtool 
if which glibtoolize 2>&1> /dev/null; then
    alias libtoolize=glibtoolize
fi

aclocal -I m4 && \
autoheader && \
autoconf && \
libtoolize -ic && \
automake -ac 
