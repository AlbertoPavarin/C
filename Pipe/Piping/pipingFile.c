#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int status;
    int pid1, pid2;
    int p1p2[2];
    if (pipe(p1p2) < 0) // Crea una pipe
    {
        printf("Errore nella creazione della pipe\n");
        exit(0);
    } 

    pid1 = fork(); // crea un processo figlio
    if (pid1 == 0)
    {
        close(1); // chiude STDOUT
        dup(p1p2[1]); // duplica il canale di scrittura della pipe
        close(p1p2[1]); // chiude il canale originale
        close(p1p2[0]); // chiude il canale di lettura
        execlp("/bin/cat", "cat", "file.txt", NULL); // exec per chiamare il comando cat per file.txt
        printf("Errore\n");
        exit(1);
    }
    else
    {
        int p2p0[2];
        if (pipe(p2p0) < 0)
        {
            printf("Errore nella creazione della pipe\n");
            exit(2);
        }

        pid2 = fork(); // crea un secondo processo figlio
        if (pid2 == 0)
        {
            close(0); // chiude STDIN
            dup(p1p2[0]);
            close(1); // chiude STDOUT
            dup(p2p0[1]); // duplica il lato scrittura della pipe tra p0 e p2
            close(p2p0[0]);
            close(p2p0[1]);
            close(p1p2[0]);
            close(p1p2[1]);
            execlp("/bin/wc", "wc", NULL); // exec per chiamare il comando wc (conta righe, parole e caratteri) sul file.txt
            printf("Errore\n");
            exit(3);    
        }
        else
        {
            wait(&status);
            close(0); // chiude STDIN
            dup(p2p0[0]); // duplica il lato di lettura della pipe
            close(p2p0[0]);
            close(p2p0[1]);
            close(p1p2[0]);
            close(p1p2[1]);
            close(1);
            int fd = open("output.txt", O_RDWR | O_CREAT, 0644); // 0644 utente: rd+wr(4+2), gruppo: rd(4), ever: rd(4)
            if (fd < 0) 
            {
                printf("Errore nell'apertura del file\n");
                exit(4);
            }
            execlp("/bin/tee", "tee", NULL);
            return 0;
        }
    }
}