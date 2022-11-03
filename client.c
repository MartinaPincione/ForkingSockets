#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include <sys/wait.h>



void checkError(int status,int line)
{
   if (status < 0) 
    {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
    }
}

int createClient(int portNum,char* hostVar);


int main(int argc, char* argv[])
 {
    int sid = createClient(9000, "localhost");

    //client sending to server 
    char* buf = "Hey Server!";
    int bufSize = strlen(buf) + 1, sent = 0;
    int rem = bufSize;
    int wc = write(sid, &bufSize, sizeof(bufSize)); //sending the size of the buffer it will send
    checkError(wc,__LINE__);
    while (rem > 0) //sending the buffer
     {
        int wc = write(sid, buf + sent, rem);
        checkError(wc,__LINE__);
        rem -= wc;
        sent += wc;
     }
    printf("Client wrote [%s] to the server.\n", buf);

    int mesSize;
    int rc = read(sid, &mesSize, sizeof(mesSize)); //reading the size of the buffer it will read
    checkError(rc,__LINE__);
    char* mes = malloc(sizeof(char) *mesSize);
    rem = mesSize;
    int rec =0;
    while(rem > 0) //reading the buffer
     {
        int rc = read(sid, mes+rec, rem);
        checkError(rc,__LINE__);
        rem -= rc;
        rec += rc;
     }
    printf("Client read [%s] from the server.\n", mes);
    free(mes);

    
    return 0;
 }

int createClient(int portNum,char* hostVar)
 {
    int sid = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in srv;
    struct hostent *server = gethostbyname("localhost");
    srv.sin_family = AF_INET;
    srv.sin_port = htons(9000);
    memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
    int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
    checkError(status,__LINE__);
    return sid;
 }
