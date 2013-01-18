#!/bin/sh

aclocal -I m4 && \
autoheader && \
autoconf && \
libtoolize -ic && \
automake -ac 
