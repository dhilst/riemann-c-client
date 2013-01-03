# riemann-c-client-lib

O client library to rieman writen in C

# @TODO
- Improve TCP code
  - Implement timeout (select)
- Improve error signaling, return kind of errno
- Improve UDP code
  - Does riemann responds UDP?
- Implement an alternative to getaddrinfo(), (gethostbyname!?)
  at compile time, using config.h
- Autotools
  - Start using config.h
  - Write INSTALL and README 
  - Improve checks (I haven't take a look on this yet)
- Provide tarball downloads
- Implement locking system configurable at compile time. (./configure --with-thread_safe)
- Doxygen?
- Improve installation instructions
- Git log ChangeLog's.
- Test on this enviroments
  - AIX
  - Solaris
  - FreeBSD
  - CygWin
  
  

** next


# Instalation

WARNING: This is in really early stages, and was not fully tested.

1. Clone
```
git clone https://github.com/gkos/riemann-c-client-lib.git
```

2. Build<br/>
You need protobuf-c installed and on your path to do this. You can find it at http://code.google.com/p/protobuf-c/
Also you will need autotools to run build.sh
```
./build.sh
./configure --prefix=${HOME}
make
```

3. Install!?<br/>
```
make install
```

# Usage
Check examples directory for usage hints

- Compiling

When compiling you will need to link your code against libriemann_client.so
```
gcc -o your_bin your_code.c -lriemann_client        
```

