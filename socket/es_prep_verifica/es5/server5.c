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

int checkDouble(char str[], char car)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (car == str[i])
        {
            return 1;
        }
    }
    return 0;
}

void checkCommon(char str1[], char str2[], char commChar[])
{
    for (int i = 0; i < strlen(str1); i++)
    {
        for (int j = 0; j < strlen(str2); j++)
        {
            if (str1[i] == str2[j])
            {
                if (checkDouble(commChar, str1[i]) == 0)
                {
                    strncat(commChar, &str1[i], 1);
                }
            }
        }
    }
}


int main()
{
    struct sockaddr_in servizio, addr_remoto;
    char str1[DIM], str2[DIM], commChar[DIM];
    int socketfd, soa, fromlen = sizeof(servizio);

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

        read(soa, str1, DIM);
        read(soa, str2, DIM);

        checkCommon(str1, str2, commChar);

        write(soa, commChar, strlen(commChar));

        printf("\n\n");

        clearBuffer(str1);
        clearBuffer(str2);
        clearBuffer(commChar);

        close(soa);
    }
    
    return 0;
}