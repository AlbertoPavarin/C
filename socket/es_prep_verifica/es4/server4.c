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

int eliminaSpec(char str[], int len, char newStr[])
{
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]) > 0)
        {
            newStr[k++] = str[i];
        }
    }

    printf("%s\n", newStr);

    return k;
}

void ordina(char str[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (str[j] > str[j+1])
            {
                int tmp = str[j];
                str[j] = str[j+1];
                str[j+1] = tmp;
            }
        }
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    char str[DIM], newStr[DIM];
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

        read(soa, str, DIM);

        printf("Stringa: %s\n", str);

        int len = eliminaSpec(str, strlen(str), newStr);

        ordina(newStr, len);

        write(soa, newStr, len);

        printf("\n\n");

        clearBuffer(str);
        clearBuffer(newStr);

        close(soa);
    }
    
    return 0;
}