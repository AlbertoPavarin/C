/// @file       es3_libro.c
/// @brief      file dell'esercizio 3 del libro
/// @date       19/11/2021
/// @author     Alberto Pavarin

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
* @fn           int main()
* @brief        funzione principale che crea tre processi figli, i quali stamperanno "Ciao sono Qui", "Ciao sono Quo", "Ciao sono Qua"
*/

int main()
{
    int pid1, pid2, pid3, status;
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("Ciao sono Qui\n");
        exit(0);
    }
    else
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("Ciao sono Quo\n");
            exit(1);
        }
        else
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                printf("Ciao sono Qua\n");
                exit(2);
            }
            else
            {
                waitpid(pid3, &status, 0);
                return 0;
            }
        }
    }
}