#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: ./ControlloFatture file.txt");
        exit(0);
    }

    int p1, p2;
    char ris[1024], controllo[1024], cod[50];
    int p1p0[2], p2p0[2];
    int tot = 0;

    if (pipe(p1p0) < 0)
    {
        printf("Errore nella creazione della pipe\n");
        exit(1);
    }
    
    do
    {
        printf("Inserisci il codice del cliente\n");
        scanf("%s", cod);   
        if (strcasecmp(cod, "esci") != 0)
        {
            p1 = fork();
            if (p1 == 0)
            {
                close(p1p0[0]);
                close(1);
                dup(p1p0[1]);
                close(p1p0[1]);
                execlp("/bin/grep", "grep", "-w", "-c", cod, argv[1], NULL); // chiamata grep per cercare il codice del cliente
                return -1;
            }
            else
            {
                read(p1p0[0], controllo, sizeof(controllo)); // viene letto il risultato della grep
                if (atoi(controllo) == 0)
                {
                    printf("Il cliente non esiste\n");
                }
                else
                {
                    if (pipe(p2p0) < 0)
                    {
                        printf("Errore nella creazione della pipe\n");
                        exit(2); 
                    }
                    
                    p2 = fork();
                    if (p2 == 0)
                    {
                        close(p2p0[0]);
                        close(p1p0[1]);
                        close(p1p0[0]);
                        close(1);
                        dup(p2p0[1]);
                        close(p2p0[1]);
                        strcat(cod, " insoluto");
                        execlp("/bin/grep", "grep", "-w", "-c", cod, argv[1], NULL); // chimata grep per cercare se un cliente non ha pagato una fattura ... es. grep -w -c cod, argv[1], dove (ES): cod = AF123 insoluto
                        return -1;
                    }
                                    
                    read(p2p0[0], ris, sizeof(ris)); // viene letto il risultato della seconda grep
                    printf("Sono state trovate %d fatture non pagate da %s\n\n", atoi(ris), cod);
                    tot += atoi(ris);
                }
            }
        }     
    } while (strcasecmp(cod, "esci") != 0);
    close(p1p0[0]);
    close(p1p0[1]);
    close(p2p0[1]);
    close(p2p0[0]);
    printf("Sono state trovate %d fatture non pagate\n", tot);
    return 0;
}