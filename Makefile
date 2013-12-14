CC = gcc
CCFLAGS = -Wall -I/usr/local/include -L/usr/local/lib -lzmq

all: server client version

server: zerochat-server.c zerochat.h
	@ $(CC) $(CCFLAGS) -o $@ $<

client: zerochat-client.c zerochat.h
	@ $(CC) $(CCFLAGS) -o $@ $<

version: zeromq-version.c
	@ $(CC) $(CCFLAGS) -o $@ $^

.PHONY: clean
clean: server client version
	@ rm -f $?
