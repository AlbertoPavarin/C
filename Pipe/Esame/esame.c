#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore negli argomenti\n");
        exit(0);
    }

    int p1p2[2];
    char nomi[1024], temp[50];
    
    if (pipe(p1p2) < 0)
    {
        printf("Errore\n");
        exit(0);
    }

    int pid = fork();
    if (pid == 0)
    {
        close(p1p2[0]);
        while(1)
        {
            printf("\nInserisci un nome\n");
            scanf("%s", temp);

            if (strcasecmp(temp, "esci") == 0)
                break;

            strcat(nomi, temp);
            strcat(nomi, "\n");
        }
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        printf("%s", nomi);
        exit(0);
    }

    pid = fork();
    if (pid == 0)
    {
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);
        close(p1p2[1]);

        int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
        close(1);
        dup(fd);
        close(fd);
        execl("/bin/sort", "sort", NULL);
        return -1;
    }
    close(p1p2[1]);
    close(p1p2[0]);
    wait(&pid);
    printf("\nNomi salvati e ordinati correttamente\n");
    return 0;
}