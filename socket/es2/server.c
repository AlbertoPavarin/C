#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define DIM 256
#define SERVER_PORT 55555

void inverti(char str[], int len, char new_str[])
{
    int j = 0;
    for (int i = len; i >=0; i--)
    {
        new_str[j++] = str[i];
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soafd, fromlen = sizeof(servizio); 
    char str[DIM], new_str[DIM];

    // dati socket
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVER_PORT);

    // transport endpoint, creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    listen(socketfd, 10);

    while(1)
    {
        printf("Server in ascolto\n");

        fflush(stdout);

        soafd = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);

        read(soafd, str, sizeof(str));

        inverti(str, strlen(str) - 1, new_str);

        printf("Messaggio ricevuto: %s\n\n\n", str);

        write(soafd, new_str, strlen(new_str));

        close(soafd);
    }

    return 0;
}