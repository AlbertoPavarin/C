#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/// @file   fork2.c
/// @date   17/11/2021
/// @brief  programma che genera due figli, i quali genereranno aloro volta altri due figli
/// @author Alberto Pavarin

/**
* @fn       int main()
* @brief    funzione pricipale che crea due figli, che generano a loro volta altri due figli
*/

int main()
{
    int pid, pid1, pid2, pid3, pid4, pid5, pid6;
    int status;

    pid1 = fork();
    if (pid1 == 0)
    {
        printf("F1\n");
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("G1\n");
            sleep(1);
            exit(0);
        }
        else
        {
            pid3 = fork();
            {
                if (pid3 == 0)
                {
                    printf("H1\n");
                    sleep(2);
                    exit(1);
                }
            }
        }
    }
    else
    {
        pid = waitpid(pid3, &status, 0);
        sleep(1);
        printf("Padre\n\n");
        pid4 = fork();
        if (pid4 == 0)
        {
            printf("F2\n");
            pid5 = fork();
            if (pid5 == 0)
            {
                printf("G2\n");
                sleep(1);
                exit(2);
            }
            else
            {
                pid6 = fork();
                if (pid6 == 0)
                {
                    printf("H2\n");
                    sleep(2);
                    exit(3);
                }
            }
        }
        else
        {
            waitpid(pid5, &status, 0);
            sleep(1);
            printf("Padre\n");
            return 0;
        }
    }
}