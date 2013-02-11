---
layout: default
title: riemann-c-client Debian building
---
# Debian Install

## Installing dependencies 

I've installed this packages. If there is someting missing please do a
pull request fixing it.

    apt-get install automake autoconf make git libprotobuf-c0-dev protobuf-c-compiler

## Clone the repo

    git clone https://github.com/gkos/riemann-c-client.git
    cd riemann-c-client

## Cofigure, Compile and Install

    ./configure
    make
    make install

## Testing
### Sending an event
    riemannc send --server 192.168.1.14 --port 5555 --host "debian" --service test
    sent

### Quering
    riemannc query --server 192.168.1.14 --port 5555
    1360536976,debian,test,(null),(null),,,,300.000000,,

