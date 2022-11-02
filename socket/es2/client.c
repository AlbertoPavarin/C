#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>//definiscono la struttura degli indirizzi e funzione del tipo ntohl
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
{   //creazione di un elemento di tipo sockaddr vedi pagina 162
    struct sockaddr_in servizio;
    int socketfd;// identificatore della socket
    char str1[DIM];
    //inizializzazione dell'elemento di tipo sockaddr
    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT);
    //creazione e definizione del Socket di tipo stream tcp pg 163
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    //connessione al server
    connect(socketfd,(struct sockaddr*)&servizio,sizeof(servizio));
    
    printf("Inserisci la stringa\n");
    scanf("%s",str1);
    write(socketfd,str1,sizeof(str1));
    read(socketfd,str1,sizeof(str1));
    printf("Stringa ricevuta dal server invertita\n %s",str1);
    
    close(socketfd);

    return 0;
}