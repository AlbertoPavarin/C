#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

#define DIM 256
#define SERVERPORT 6565

int ricerca(char str[], char carattere[])
{
    int cnt = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == carattere[0])
        {
            cnt++;
        }
    }
    
    return cnt;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soafd, sizeFrom = sizeof(servizio), cnt = 0;
    char str[DIM], ricercare[1];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    listen(socketfd, 10);

    while (1)
    {
        printf("Server in ascolto\n\n");

        fflush(stdout);

        soafd = accept(socketfd, (struct sockaddr*)&servizio, &sizeFrom);
        
        read(soafd, str, sizeof(str));

        printf("Stringa ricevuta: %s\n", str);

        read(soafd, ricercare, sizeof(ricercare));

        printf("Carattere da ricercare: %c", ricercare[0]);

        cnt = ricerca(str, ricercare);

        write(soafd, &cnt, sizeof(int));

        printf("\n\n");

        close(soafd);
    }

    close(socketfd);

    return 0;

}