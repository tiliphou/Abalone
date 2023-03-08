
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


SOCKET TCP_Create_Client(char* serverName,short service){

    struct protoent *ppe = getprotobyname("tcp");;
    if (ppe == NULL) exit(1);

    SOCKET s = socket(AF_INET,SOCK_STREAM,ppe->p_proto);
    if (s == INVALID_SOCKET) exit(1);

    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverName);
    sin.sin_port = htons(service);

    if (connect(s,(struct sockaddr*) &sin,sizeof(sin)) == SOCKET_ERROR) exit(1);

    return s;
}

SOCKET TCP_Create_Server(short service){
    struct protoent *ppe = getprotobyname("tcp");
    if (ppe==NULL) exit(1);

    SOCKET s = socket (AF_INET,SOCK_STREAM,ppe->p_proto);
    if (s==INVALID_SOCKET) exit(1);

    struct sockaddr_in sin;
    memset (&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(service);

    if(bind(s,(struct sockaddr*)&sin,sizeof(sin))==SOCKET_ERROR) exit(1);

    if(listen(s,5) == SOCKET_ERROR) exit(1);
    return s;
}


int TCP_String_Writer(SOCKET s,char* output){
    int bytes_sent = write(s,output,sizeof(output));
    if (bytes_sent == SOCKET_ERROR) exit(1);
    return bytes_sent;
}

int TCP_String_Reader(SOCKET s,char* input){
    char buffer[6];
    char *tmp = buffer;
    int bufferlen = sizeof(buffer);
    int len;
    do{
        len=recv(s,tmp,bufferlen,0);
        tmp+=len;
        bufferlen-=len;
    }while(len!=SOCKET_ERROR && len!=0 && bufferlen != 0);
    printf("%s , %d\n",buffer,len);
    if (len == SOCKET_ERROR) exit(1);

    memcpy(input,buffer,tmp-buffer);
    input[tmp-buffer]='\0';

    return tmp-buffer;
}


void receive_message(SOCKET s,char* message){
    TCP_String_Reader(s,message);
    printf("I received : %s\n ", message);
}

void send_message(SOCKET s,char* message){
    TCP_String_Writer(s,message);
    printf("I Send : %s\n ", message);
}


int main(int argc,char** argv){
    int joueur=1;
    int p=1234;
    SOCKET master = TCP_Create_Server(p);
    if (master==INVALID_SOCKET) exit(1);
    SOCKET slave = accept(master,NULL,0);
    char *input =malloc(sizeof(char)*6);
    while(1){
        if(joueur==1){
            recv(slave,input,sizeof(input),0);
            printf("%s\n",input);
            joueur--;
        }
        else{
            printf("select and move your coins : ");
            scanf("%s",input);
            write(slave,input,sizeof(input));
            joueur++;
        }
        bzero(input,6);
    }
    shutdown(slave,2);
    shutdown(master,2);
}
