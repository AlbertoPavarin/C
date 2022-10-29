#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 512
#define SERVERPORT 1313

int main(int argc,char** argv)
{   
    struct sockaddr_in servizio;
    int socketfd;
    char str1[DIM], str_in[DIM];

    // Aggiunta dati socket
    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT);

    // impostazione del transport endpoint del server
    socketfd=socket(AF_INET,SOCK_STREAM,0);

    // Connessione al server
    connect(socketfd,(struct sockaddr*)&servizio,sizeof(servizio));
    printf("Inserisci la stringa\n");
    scanf("%s",str1);
    // Scrittura stringa sulla socket
    write(socketfd,str1,sizeof(str1));

    read(socketfd, str_in, sizeof(str_in));

    printf("Stringa ricevuta dal server: %s\n", str_in);
    
    close(socketfd);

    return 0;
}