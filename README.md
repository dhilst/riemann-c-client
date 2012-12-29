# riemann-c-client-lib

O client library to rieman writen in C

# @TODO
- Improve TCP code
  - Implement timeout (select)
- Improve error signaling, return kind of errno
- Implement UDP code
- Create a install target 
- Improve configure.ac checks
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
This will create the libriemann_client.so on src dir. Also will create examples on example directory

3. Install!?<br/>
This is not yet implemented, but you can move libriemann_client.so to your /usr/local/lib and use it from there.

# Usage
Check examples directory for usage hints

- Compiling

When compiling you will need to link your code against libriemann_client.so
```
gcc -o your_bin your_code.c -lriemann_client        
```

