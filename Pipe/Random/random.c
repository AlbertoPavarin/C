/// @file       random.c 
/// @brief      programma che permette, istanziando un processo ed una pipe, di sommare dei numeri randomici e sommarli
/// @date       15/12/2021
/// @author     Pavarin Alberto   

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/// @param MAX: numeri da generare
#define MAX 10

/**
* @fn           int main()
* @brief        funzione principale che crea una pipe, successivamente istanzia un processo figlio. Il processo padre genera 10 numeri casuali e li passa al figlio utilizzando la pipe. Successivamente il processo figlio li somma e passa la somma al padre, il quale stampera' il risultato
*/ 
int main()
{
    int fd[2];
    int numeri[MAX];
    int somma = 0;
    srand(time(0));
    if (pipe(fd) < 0)
    {
        printf("Errore nella creazione della pipe\n");
        exit(0);
    }
    
    int pid = fork();
    if (pid == 0)
    {
        for (int i = 0; i < MAX; i++)
        {
            read(fd[0], &numeri[i], MAX);
            somma += numeri[i];
        }  
        write(fd[1], &somma, sizeof(int));    
        close(fd[0]);
        close(fd[1]);
        exit(1);
    }
    else
    {    
        printf("Numeri Generati:   ");
        for (int i = 0; i < MAX; i++)
        {
            numeri[i] = rand() % 10;
            printf("%i ", numeri[i]);
            write(fd[1], &numeri[i], MAX);
        }
        
        wait(&pid);

        read(fd[0], &somma, sizeof(int));
        printf("\nLa somma dei numeri randomici e': %i\n", somma);
        close(fd[0]);
        close(fd[1]);
    }
    return 0;
}