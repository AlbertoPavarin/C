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
    int socketfd, cnt = 0;
    char str[DIM], ricercare[1];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci stringa:\n");
    scanf("%s", str);

    write(socketfd, str, sizeof(str));

    printf("Inserisci carattere da ricercare: \n");
    scanf("%s", ricercare);

    write(socketfd, ricercare, sizeof(ricercare));

    read(socketfd, &cnt, sizeof(int));

    printf("Il carattere %c compare %d volte\n", ricercare[0], cnt);

    close(socketfd);

    return 0;
}