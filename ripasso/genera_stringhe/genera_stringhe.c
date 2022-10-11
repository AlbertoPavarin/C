#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int rmd_index, rmd_length;
    char alpha[21] = {"abcdefghilmnopqrstuvz"}, parola[5][6];
    srand(time(NULL));

    for (int i = 0; i < 5; i++)
    {
        rmd_length = rand() % 5 + 1;
        for (int j = 0; j < rmd_length; j++)
        {
            rmd_index = rand() % 21;
            parola[i][j] = alpha[rmd_index];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", parola[i]);
    } 
}