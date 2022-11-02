# Non-Blocking Sockets

This non-blocking socket implementation consists of a server (server.c) and two sample client processes (blockingclient.c and client.c). client.c communicates with the server immediately, while blockingclient.c waits for user input before sending and recieving communication to/from the server. This is accomplished using fork(). 
