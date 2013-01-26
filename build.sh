#!/bin/sh


# OSX uses glibtoolize for gnu libtool 
if which glibtoolize; then
    alias libtoolize=glibtoolize
fi

aclocal -I m4 && \
autoheader && \
autoconf && \
libtoolize -ic && \
automake -ac 
