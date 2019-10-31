## Pre-requisites
GCC buld environment and gRPC v1.20.0 with protobuf 3.7.0 installed.

## Compile

    $ make
## Run Server

    $ ./calc_server
## Client examples

    $ ./calc_client 1 2 +
    Result: 3
    
    $ ./calc_client 1 2 /
    Result: 0.5
    
    $ ./calc_client 1 2 \*
    Result: 2
