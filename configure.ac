#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Autoconf init
AC_PREREQ([2.68])
AC_INIT([libriemann_client], [3.0.0], [danielhilst@gmail.com])

# Automake init
AM_INIT_AUTOMAKE 
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Libtool init
LT_INIT
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([src/tcp.c])
AC_CONFIG_HEADERS([config.h])
AX_PREFIX_CONFIG_H([src/riemann/_config.h], [RIEMANN])

# Checks for programs.
AC_PROG_CC
AC_CHECK_PROG([HAS_PROTOC_C], [protoc-c], [yes])
if test x$HAS_PROTOC_C != x"yes" ; then
   AC_MSG_ERROR([You need protoc-c installed and on your path to proceed. You can find it at http://code.google.com/p/protobuf-c/])
fi

# Checks for libraries.

AC_ARG_ENABLE(lock, AC_HELP_STRING([--enable-lock], [Use lock system]), 
[
        AC_CHECK_HEADERS([pthread.h], 
                         [AC_DEFINE([WITH_LOCK], [1], [Use lock system])],
                         [AC_ERROR([--enable-lock passed but no pthread.h header found])])
        AC_SUBST([WITH_LOCK_LDFLAGS], [-lpthread])
])

# Check for protobuf-c
AC_ARG_WITH(protobuf-c-dir, AC_HELP_STRING([--with-protobuf-c-dir], [Path to protobuf-c]), 
[
	if test "x$withval" != "xno" && test "x$withval" != "xyes"; then
                AC_SUBST(PROTOBUF_C_LDFLAGS, [-L${withval}/lib])
                AC_SUBST(PROTOBUF_C_CFLAGS, [-I${withval}/include])
                PROTOBUF_C_LDFLAGS="-L$withval/lib"
                PROTOBUF_C_CFLAGS="-I$withval/include"
        fi
])

( # New shell to mask CFLAGS and LDFLAGS
        LDFLAGS="$PROTOBUF_C_LDFLAGS $LDFLAGS"
        AC_CHECK_LIB(protobuf-c, protobuf_c_message_init, [], 
        [
                AC_MSG_ERROR([Can't link against protobuf-c lib, use --with-protobuf-c-dir= for non-standard directories])
        ])
) || exit 1

AC_ARG_ENABLE(timeout, AC_HELP_STRING([--enable-timeout], [Enable timeout system]), 
[
        WITH_TIMEOUT=no
        if test "x$enableval" !=  "xno"; then
                WITH_TIMEOUT=yes
                AC_CHECK_HEADERS([sys/types.h sys/socket.h], [],
                [
                	AC_MSG_ERROR([sys/types.h or sys/socket.h  not found])
                ])
        fi
],
[
        WITH_TIMEOUT=yes
])
if test "x$WITH_TIMEOUT" = "xyes"; then
        AC_DEFINE([WITH_TIMEOUT], [1], [Use timeout system])
fi

# Checks for header files.
( # New shell to mask CFLAGS and LDFLAGS
        CFLAGS="$PROTOBUF_C_CFLAGS $CFLAGS"
        AC_CHECK_HEADERS([google/protobuf-c/protobuf-c.h], [],
        [
                AC_MSG_ERROR([google/protobuf-c/protobuf-c.h not found, use --with-protobuf-c-dir= for non-standard directories])
        ])
) || exit 1 





AC_CHECK_HEADERS([assert.h arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

AC_CHECK_TYPES([struct addrinfo], [], [], [[#include <netdb.h>]])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset socket strdup strerror getaddrinfo])


AC_CONFIG_FILES([Makefile 
                 src/Makefile 
                 src/examples/Makefile])

AC_OUTPUT

