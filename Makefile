CC = gcc
CCFLAGS = -Wall -I/usr/local/include -L/usr/local/lib
CCLIBS = -lzmq -pthread

all: server client version

server: zerochat-server.c zerochat.h
	@ $(CC) $(CCFLAGS) $< $(CCLIBS) -o $@

client: zerochat-client.c zerochat.h
	@ $(CC) $(CCFLAGS) $< $(CCLIBS) -o $@

version: zmq-version.c
	@ $(CC) $(CCFLAGS) $^ $(CCLIBS) -o $@

.PHONY: clean
clean:
	@ rm -f server client version
