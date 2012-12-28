# riemann-c-client-lib

O client library to rieman writen in C

# @TODO
- For God sake, create some solid standard
this is messy like a @#$%
- Improve TCP code
  - Implement timeout
- Improve query code, 
  - riemann_query_tcp_send makes impossible to free received msg data;
- Improve error signaling, return kind of errno
  instead of fprintfing everthing to stderr
- Implement UDP code
- Port to libtools
- Doxygen?
- Improve installation instructions



# Instalation

WARNING: This is in really early stages, and was not fully tested.

1. Clone
```
git clone https://github.com/gkos/riemann-c-client-lib.git
```

2. Build<br/>
You need protobuf-c installed and on your path to do this. You can find it at http://code.google.com/p/protobuf-c/
```
make
```
This will create the libriemann_client.so. Also will create examples on example directory

3. Install!?<br/>
This is not yet implemented, but you can move libriemann_client.so to your /usr/local/lib and use it from there.

# Usage
Check examples directory

- Compiling

When compiling you will need to link your code against libriemann_client.so
```
gcc -o your_bin your_code.c -lriemann_client        
```

