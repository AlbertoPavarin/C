/// @file       es2_libro.c
/// @brief      file dell'esercizio 2 del libro
/// @date       19/11/2021
/// @author     Alberto Pavarin

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
* @fn           int main()
* @brief        funzione principale che chiede in input un numero e poi crea un processo figlio, successivamente il processo padre somma 10 al numero e il processo figlio somma 15. Fatte le operazioni vengono stampate le due somme
*/

int main()
{
    float numero;
    float somma;
    printf("Inserisci un numero\n");
    scanf("%f", &numero);
    int pid = fork();
    if (pid == 0)
    {
        somma = numero + 15;
        printf("La somma tra il numero inserito e 15 è: %f\n", somma);
        exit(0);
    }
    else
    {
        wait(&pid);
        somma = numero + 10;
        printf("La somma tra il numero inserito e 10 è: %f\n", somma);
        return 0;
    }
}