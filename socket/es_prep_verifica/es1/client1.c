#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#define DIM 512
#define SERVERPORT 1515

int main()
{
    struct sockaddr_in servizio;
    int socketfd;
    char str[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci la stringa\n");
    scanf("%s", str);
    write(socketfd, str, sizeof(str));
    read(socketfd, str, sizeof(str));
    printf("Stringa ricevuta: %s\n\n", str);
    
    close(socketfd);

    return 0;
}