

#include "network.h"


SOCKET TCP_Create_Client(char* serverName,short service){
    //struct protoent *ppe = getprotobyname("tcp");
    //if (ppe == NULL) exit(1);

    SOCKET s = socket(AF_INET,SOCK_STREAM,0);
    if (s == INVALID_SOCKET){
        printf("Invalid socket...\n");
        exit(1);
    } 
    

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverName);
    sin.sin_port = htons(service);

    if (connect(s,(struct sockaddr*) &sin,sizeof(sin)) == SOCKET_ERROR){
        printf("Could not connect to server: %s\n",strerror(errno));
        exit(1);
    } 

    printf("[+]Connected to : %s\n",serverName);

    return s;
}


SOCKET TCP_Create_Server(short service){
    //struct protoent *ppe = getprotobyname("tcp");
    //if (ppe==NULL) exit(1);

    SOCKET s = socket (AF_INET,SOCK_STREAM,0);
    if (s==INVALID_SOCKET){
        printf("Invalid socket...\n");
        exit(1);
    } 

    struct sockaddr_in sin;

    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(service);

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt,1 );

    if(bind(s,(struct sockaddr*)&sin,sizeof(sin))==SOCKET_ERROR){
        printf("Cant bind ... \n");
        exit(1);
    }

    if(listen(s,5) == SOCKET_ERROR){
        printf("Cannot listen...\n");
        exit(1);
    } 

    printf("[+]Currently listening...\n");

    return s;
}




/*
int main(int argc,char** argv){
    return 0;
}
*/
