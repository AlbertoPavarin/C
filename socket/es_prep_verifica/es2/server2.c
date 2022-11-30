#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#define DIM 512
#define SERVERPORT 1515

void clearBuffer(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = 0;
    }
    
}

int contaOccorrenze(char str[], char cerca[])
{
    int cnt = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == cerca[0])
        {
            cnt++;
        }
    }

    return cnt;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    char str[DIM], cerca[1];
    int socketfd, soa, fromlen = sizeof(servizio), cnt;

    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(SERVERPORT);
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    listen(socketfd, 10);

    while (1)
    {
        printf("Server in ascolto\n\n");

        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);

        read(soa, str, DIM);

        printf("Stringa: %s\n", str);

        read(soa, cerca, 1);

        printf("Carattere da cercare: %c", cerca[0]);

        cnt = contaOccorrenze(str, cerca);

        write(soa, &cnt, sizeof(int));

        printf("\n\n");

        clearBuffer(str);

        close(soa);
    }
    
    return 0;
}