#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Errore negli argomenti\n");
        exit(5);
    }

    int pid1, pid2, pid3, p1p2[2], p2p3[2], p3p0[2];
    double totale = 0;
    char buff[1], *ptr, strSec[100];

    if (pipe(p1p2) < 0)
    {
        printf("Errore nella creazione della pipe\n");
        exit(0);
    }

    pid1 = fork();
    if (pid1 == 0)
    {
        close(p1p2[0]);
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        execl("/bin/traceroute", "traceroute", argv[1], NULL);
        return -1;
    }

    if (pipe(p2p3) < 0)
    {
        printf("Errore nella creazione della pipe\n");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0)  
    {
        close(p1p2[1]);
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);

        close(p2p3[0]);
        close(1);
        dup(p2p3[1]);
        close(p2p3[1]);
        execl("/bin/awk", "awk", "{print $4}", NULL);
        return -1;
    }

    if (pipe(p3p0) < 0)
    {
        printf("Errore nella creazione della pipe");
        exit(2);
    }

    pid3 = fork();
    if (pid3 == 0)
    {
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[1]);
        close(0);
        dup(p2p3[0]);
        close(p2p3[0]);

        close(p3p0[0]);
        close(1);
        dup(p3p0[1]),
        close(p3p0[1]);

        execl("/bin/tail", "tail", "-n", "+2", NULL);
        return -1;
    }

    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p3[0]);
    close(p2p3[1]);
    close(p3p0[1]);
    
    while (read(p3p0[0], buff, 1) > 0)
    {
        strncat(strSec, &buff[0], sizeof(buff[0]));
        if (buff[0] == '\n' || buff[0] == '*')
        {
            totale += strtod(strSec, &ptr);
            strSec[0] = '\0';
        }
    }

    close(p3p0[0]);
    printf("Totale: %.3lf ms\n", totale);
    return 0;
}