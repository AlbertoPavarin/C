/// @file   fork1.c
/// @brief  file su l'eserczio 1 delle fork
/// @date   16/11/2021
/// @author Alberto Pavarin

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
* @fn       int main()
* @brief    funzione principale, al suo interno vengono generati tre processi figli, che scrivono delle parole in un file. Successivamente il processo padre va a leggere cio' che c'e' nel file per poi stamparlo a video
*/

int main()
{
    int pid, pid1, pid2, pid3, status;
    int parole = 0;
    char contenuto[10][10];
    FILE *stream = fopen("output.txt", "w+");
    if (stream == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(0);
    }
    pid1 = fork();
    if (pid1 == 0)
    {
        fprintf(stream, "Ciao ");
        sleep(1);
        exit(1);
    }
    else 
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            fprintf(stream, "siamo ");
            sleep(2);
            exit(2);
        }
        else
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                fprintf(stream, "i figli.");
                sleep(3);
                exit(3);
            }
            else
            {
                pid = waitpid(pid3, &status, 0);
                printf("Fatto\n");
                fclose(stream);

                FILE *stream = fopen("output.txt", "r");
                if (stream == NULL)
                {
                    printf("File non esistente\n");
                    exit(4);
                }

                while (fscanf(stream, "%s", contenuto[parole]) != EOF)
                {
                    parole++;
                }

                fclose(stream);

                for (int i = 0; i < parole; i++)
                {
                    printf("%s ", contenuto[i]);
                }
                printf("\n");
                exit(5);
            }
        }
    }
    return 0;
}