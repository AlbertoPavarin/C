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
    int socketfd, cntVocali, cntCons;
    char str[DIM], commChar[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci la stringa1\n");
    scanf("%s", str);
    write(socketfd, str, sizeof(str));

    printf("Inserisci la stringa1\n");
    scanf("%s", str);
    write(socketfd, str, sizeof(str));

    read(socketfd, commChar, sizeof(str));
    printf("Caratteri comuni nella stringa: %s\n", commChar);
    
    close(socketfd);

    return 0;
}