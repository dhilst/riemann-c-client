#!/bin/sh

if test "x" = "x$LIBTOOLIZE"; then
    LIBTOOLIZE=libtoolize
fi

aclocal -I m4 && \
autoheader && \
autoconf && \
${LIBTOOLIZE} -ic && \
automake -ac 
