#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <strings.h>

int main(int argc, char *argv[])
{
        
    char str[50];
    int pid, tot = 0;
    char ris[10];
    if (argc != 2)
    {
        printf("Uso: ./CercaStringhe file.txt\n");
        exit(0);
    }

    int tubbo[2];

    if (pipe(tubbo) < 0)
    {
        printf("Errore nella creazione della pipe\n");
        exit(1);
    }

    do
    {
        printf("Inserisci la stringa che vuoi cercare\n");
        scanf("%s", str);
        pid = fork(); // istanziato P1
        if (pid == 0) // se e' il figlio
        {
            close(0); // chiude STDIN
            dup(tubbo[0]); // duplica il canale di lettura della pipe
            close(tubbo[0]); // chiude il canale originale
            close(1); // chiude STDOUT
            dup(tubbo[1]); // duplica il canale di scrittura della pipe
            close(tubbo[1]); // chiude il canale originale della pipe
            execlp("/bin/grep", "grep", "-c", str, argv[1], NULL); // chiamata di sistema grep, con -c serve per contare quante volte la stringa inserita 
                                                                   // in input (str) si ripete nel file inserito in argv[1]
        }
        read(tubbo[0], ris, sizeof(ris)); // legge il risultato della chiamata grep
        printf("La stringa %s e' comparsa %d volte\n\n", str, atoi(ris));
        tot += atoi(ris);
    } while (strcasecmp(str, "Fine") != 0);
    
    close(tubbo[1]);
    close(tubbo[0]);

    printf("Sono state trovate %i stringhe\n", tot);
    
    return 0;
}