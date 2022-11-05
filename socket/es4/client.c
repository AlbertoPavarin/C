#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

#define DIM 256
#define SERVERPORT 6565

int main()
{
    struct sockaddr_in servizio;
    int socketfd;
    char str[DIM], vocali[DIM], consonanti[DIM], caratteriSpec[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if ((connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio))) < 0)
    {
        printf("Scemo non c'è er servero");
        exit(EXIT_FAILURE);
    }

    printf("Inserisci stringa:\n");
    scanf("%s", str);

    write(socketfd, str, sizeof(str));

    read(socketfd, vocali, sizeof(vocali));
    read(socketfd, consonanti, sizeof(consonanti));
    read(socketfd, caratteriSpec, sizeof(caratteriSpec));

    printf("\n\nVocali: %s\nConsonanti: %s\nCaratteri e Numeri: %s\n", vocali, consonanti, caratteriSpec);

    close(socketfd);

    return 0;
}