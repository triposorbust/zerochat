CC = gcc
CCFLAGS = -Wall -I/usr/local/include -L/usr/local/lib
CCLIBS = -lzmq -pthread

all: server client version

server: zerochat-server.c zerochat.h
	@ $(CC) -o $@ $(CCFLAGS) $< $(CCLIBS)

client: zerochat-client.c zerochat.h
	@ $(CC) -o $@ $(CCFLAGS) $< $(CCLIBS)

version: zmq-version.c
	@ $(CC) -o $@ $(CCFLAGS) $^ $(CCLIBS)

.PHONY: clean
clean:
	@ rm -f server client version
