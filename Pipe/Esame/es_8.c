#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore negli argomenti\n");
        exit(1);
    }

    int p1p2[2];
    char nome[50];

    if (pipe(p1p2) < 0)
    {
        printf("Errore nella creazione della pipe\n");
        exit(1);
    }

    int pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            printf("Inserisci nome:\n");
            scanf("%s", nome);
            if (strcasecmp("esci", nome) == 0)
            {
                break;
            }
            strcat(nome, "\n");
            write(p1p2[1], nome, strlen(nome));
        }
        close(p1p2[1]);
    }

    if (fork() == 0)
    {
        close(p1p2[1]);
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);

        close(1);
        int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
        execl("/bin/sort", "sort", NULL);
        return -1;
    }
    close(p1p2[0]);
    close(p1p2[1]);
    wait(&pid);

    return 0;
}