#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define DIM 256
#define SERVER_PORT 55555

int main()
{
    struct sockaddr_in servizio;
    int socketfd;
    char str[DIM], str_in[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVER_PORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci stringa:\n");
    scanf("%s", str);

    write(socketfd, str, sizeof(str));

    read(socketfd, str_in, sizeof(str_in));

    printf("Stringa ricevuta dal server: %s\n", str_in);
    
    close(socketfd);

    return 0;
}