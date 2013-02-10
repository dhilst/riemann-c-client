#!/bin/sh

LIBTOOLIZE=""
if hash glibtoolize > /dev/null 2>&1; then
	LIBTOOLIZE=glibtoolize
elif hash libtoolize > /dev/null 2>&1; then
	LIBTOOLIZE=libtoolize
else
	echo "libtoolize not found!"
	exit 1
fi
	

aclocal -I m4 && \
autoheader && \
autoconf && \
${LIBTOOLIZE} -ic && \
automake -ac 
