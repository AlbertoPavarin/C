#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore negli argomenti\n");
        exit(1);
    }

    int p1p2[2], p2p0[2];
    float totale = 0;
    char buff[1], importo[50];

    if (pipe(p1p2) < 0)
    {
        printf("Errore creazione pipe\n");
        exit(1);
    }

    if (fork() == 0)
    {
        close(p1p2[0]);
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        execl("/bin/cat", "cat", argv[1], NULL);
        return -1;
    }

    if (pipe(p2p0) < 0)
    {
        printf("Errore creazione pipe\n");
        exit(1);
    }

    if (fork() == 0)
    {
        close(p1p2[1]);
        close(p2p0[0]);

        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);

        close(1);
        dup(p2p0[1]);
        close(p2p0[1]);
        execl("/bin/awk", "awk", "{print $3}", NULL);
        return -1;
    }

    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p0[1]);

    while(read(p2p0[0], buff, sizeof(buff)) > 0)
    {
        strncat(importo, &buff[0], sizeof(buff[0]));
        if (buff[0] == '\n')
        {
            totale += atof(importo);
            importo[0] = '\0';
        }
    }
    printf("Il totale e': %.2f\n", totale);
    close(p2p0[0]);
    return 0;
}