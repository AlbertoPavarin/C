/// @file       es1_libro.c
/// @brief      file dell'esercizio 1 del libro
/// @date       19/11/2021
/// @author     Alberto Pavarin

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
* @fn           int main()
* @brief        funzione principale, che crea un processo figlio, e successivamente stampa a schermo i pid del figlio e del padre   
*/

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        printf("Sono il figlio con pid: %i\n", getpid());
        exit(0);
    }
    else
    {
        printf("Sono il padre con pid: %i\n", getpid());
        wait(&pid);
        return 0;
    }
}