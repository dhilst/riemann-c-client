#!/bin/sh

aclocal && \
autoheader && \
autoconf && \
libtoolize -ic && \
automake -ac 
