#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <ctype.h>

#define DIM 512
#define SERVERPORT 1515

void clearBuffer(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = 0;
    }
    
}

void contaVocCons(char str[], int *cntVocali, int *cntCons)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]) > 0)
        {
            if (toupper(str[i]) == 'A' || toupper(str[i]) == 'E' || toupper(str[i]) == 'I' || toupper(str[i]) == 'O' || toupper(str[i]) == 'U')
            {
                printf("%c\n", str[i]);
                (*cntVocali)++;
            }
            else
            {
                //printf("%c\n", str[i]);
                (*cntCons)++;
            }
        }
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    char str[DIM];
    int socketfd, soa, fromlen = sizeof(servizio), cntVocali = 0, cntCons = 0;

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

        contaVocCons(str, &cntVocali, &cntCons);

        write(soa, &cntVocali, sizeof(int));
        write(soa, &cntCons, sizeof(int));

        printf("\n\n");

        clearBuffer(str);
        cntVocali = 0;
        cntCons = 0;

        close(soa);
    }
    
    return 0;
}