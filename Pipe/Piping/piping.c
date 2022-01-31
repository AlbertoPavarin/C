#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int status;
    int pid1, pid2;
    int fd[2];
    if (pipe(fd) < 0) // Crea una pipe
    {
        printf("Errore nella creazione della pipe\n");
        exit(0);
    } 

    pid1 = fork(); // crea un processo figlio
    if (pid1 == 0)
    {
        close(1); // chiude STDIN
        dup(fd[1]); // duplica il canale di scrittura della pipe
        close(fd[1]); // chiude il canale originale
        close(fd[0]); // chiude il canale di lettura
        execlp("cat", "cat", "file.txt", NULL); // exec per chiamare il comando cat per file.txt
    }
    else
    {
        pid2 = fork(); // crea un secondo processo figlio
        if (pid2 == 0)
        {
            close(0); // chiude STDOUT
            dup(fd[0]);
            close(fd[0]);
            close(fd[1]);
            execlp("wc", "wc", NULL); // exec per chiamare il comando wc (conta righe, parole e caratteri) sul file.txt
        }
        else
        {
            wait(&status);
            return 0;
        }
    }
}