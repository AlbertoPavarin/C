#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <strings.h>

int main(int argc, char *argv[])
{
        
    char str[50];
    int pid1, pid2, pid3, tot = 0;
    char ris[1000];
    if (argc != 2)
    {
        printf("Uso: ./CercaStringhe file.txt\n");
        exit(0);
    }

    int p2p3[2];
    int p1p2[2];

    do
    {
        printf("Inserisci la stringa che vuoi cercare\n");
        scanf("%s", str);
        if (strcasecmp(str, "Fine") != 0)
        {      
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
                execlp("/bin/cat", "cat", argv[1], NULL);
                return -1;
            }
            else
            {   
                pid2 = fork(); // istanziato P2
                if (pid2 == 0) // se e' il figlio
                {
                    close(0);
                    dup(p1p2[0]);
                    close(p1p2[0]);
                    close(1); // chiude STDOUT
                    dup(p1p2[1]); // duplica il canale di scrittura della pipe
                    close(p1p2[1]); // chiude il canale originale della pipe
                    execlp("/bin/grep", "grep", "-c", str, NULL); // chiamata di sistema grep, con -c serve per contare quante volte la stringa inserita 
                                                                   // in input (str) si ripete nel file
                    return -1;
                }
                read(p1p2[0], ris, sizeof(ris)); // legge il risultato della chiamata grep
                printf("La stringa %s e' comparsa %d volte\n\n", str, atoi(ris));
                tot += atoi(ris);
            }
        }
    } while (strcasecmp(str, "Fine") != 0);
    
    close(p2p3[1]);
    close(p2p3[0]);

    printf("\nSono state trovate %i stringhe\n", tot);
    
    return 0;
}