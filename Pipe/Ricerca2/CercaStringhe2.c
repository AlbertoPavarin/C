#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <strings.h>
#include <fcntl.h>

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
    int p3p0[2];

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
                   
            pid1 = fork(); // instanziato P1
            if (pid1 == 0) // se e' il figlio
            {
                close(p1p2[0]);
                close(1); // chiude STDOUT
                dup(p1p2[1]); // duplica il canale di scrittura della pipe che va dal processo 1 al processo 2
                close(p1p2[1]); // chiude il canale originale

                execlp("/bin/cat", "cat", argv[1], NULL); // Chiamata di sistema cat
                return -1;
            }
            else
            {   
                if (pipe(p2p3) < 0)
                {
                    printf("Errore nella creazione della pipe");
                    exit(1);
                }
                pid2 = fork(); // istanziato P2
                if (pid2 == 0) // se e' il figlio
                {
                    close(0); // chiude STDIN
                    dup(p1p2[0]); // duplica il canale di lettura della pipe della pipe p1p2
                    close(p1p2[0]); // chiude il canale originale
                    close(1); // chiude STDOUT
                    dup(p2p3[1]); // duplica il canale di scrittura della pipe che va da P2 a P3
                    close(p2p3[1]); // chiude il canale originale della pipe
                    
                    // chiude canali che non servono
                    close(p2p3[0]);
                    close(p1p2[1]);

                    execlp("/bin/grep", "grep", "-o", str, NULL); // chiamata di sistema grep -o sul file passato dalla pipe
                    return -1;
                }
                else
                {
                    if (pipe(p3p0))
                    {
                        printf("Errore nella creazione della pipe\n");
                        exit(2);
                    }
                    
                    pid3 = fork(); // instanziato P3
                    if (pid3 == 0) // se e' il figlio
                    {
                        close(0); // chiude STDIN
                        dup(p2p3[0]); // duplica il canale di lettura della pipe che va da P2 a P3
                        close(p2p3[0]); // chiude il canale originale
                        close(1); // chiude STDOUT
                        dup(p3p0[1]); // duplica il canale di scrittura della pipe che va da P3 a P0

                        // Chiude i canali superflui
                        close(p3p0[1]);
                        close(p3p0[0]);
                        close(p1p2[0]);
                        close(p1p2[1]);
                        close(p2p3[1]);
                        close(p3p0[1]);

                        execlp("/usr/bin/wc", "wc", "-l", NULL); // chiamata di sistema wc -l per contare quante volte si e' ripetuta la stringa inserita in input
                        return -1;
                    }

                    // chiude i canali superflui
                    close(p3p0[1]);
                    close(p1p2[0]);
                    close(p1p2[1]);
                    close(p2p3[1]);
                    close(p2p3[0]);

                    read(p3p0[0], ris, sizeof(ris)); // legge il risultato delle chiamate precedenti tramite il canale di lettura della pipe P3 P0
                    printf("\nLa stringa %s e' comparsa %d volte\n\n", str, atoi(ris));
                    tot += atoi(ris);                 
                }
            }
        }
    } while (strcasecmp(str, "Fine") != 0);

    close(p3p0[0]);    
    printf("\nSono state trovate %i stringhe\n", tot);
    
    return 0;
}