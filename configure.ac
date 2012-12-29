#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libriemann_client], [0.1], [danielhilst@gmail.com])
AM_INIT_AUTOMAKE 
LT_INIT
AC_CONFIG_SRCDIR([src/tcp.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_CHECK_PROG([HAS_PROTOC_C], [protoc-c], [yes])
if test x$HAS_PROTO_C != x"yes" ; then
   AC_MSG_ERROR([You need protoc-c installed and on your path to proceed. You can find it at http://code.google.com/p/protobuf-c/])
fi
                
                          


# Checks for libraries.
AC_CHECK_LIB(protobuf-c, protobuf_c_message_init)

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset socket strdup strerror getaddrinfo])



AC_CONFIG_FILES([Makefile 
                 src/Makefile 
                 src/examples/Makefile])
AC_OUTPUT

