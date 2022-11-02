#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <ctype.h>

#define DIM 256
#define SERVERPORT 6565

void assegnaVett(char str[], char vocali[], char consonanti[], char caratteri[])
{
    int vocC = 0, consC = 0, carC = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (toupper(str[i]) == 'A' || toupper(str[i]) == 'E' || toupper(str[i]) == 'I' || toupper(str[i]) == 'O' || toupper(str[i]) == 'U')
        {
            vocali[vocC++] = str[i];
        }
        else if (isalpha(str[i]))
        {
            consonanti[consC++] = str[i];
        }
        else 
        {
            caratteri[carC++] = str[i];
        }
    }

    printf("%s\n%s\n%s\n\n", vocali, consonanti, caratteri);
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soafd, sizeFrom = sizeof(servizio), cnt = 0;
    char str[DIM], ricercare[1], vocali[DIM], consonanti[DIM], caratteriSpec[DIM];

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

        assegnaVett(str, vocali, consonanti, caratteriSpec);

        printf("%s\n%s\n%s\n\n", vocali, consonanti, caratteriSpec);

        //write(soafd, &cnt, sizeof(int));

        printf("\n\n");

        close(soafd);
    }

    close(socketfd);

    return 0;

}