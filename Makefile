all: server client blockingclient

server : server.c
	$(CC) $(CFLAGS) -o $@ $?

client : client.c
	$(CC) $(CFLAGS) -o $@ $?

blockingclient : blockingclient.c
	$(CC) $(CFLAGS) -o $@ $?

clean:
	rm -rf *.o client server blockingclient *~
