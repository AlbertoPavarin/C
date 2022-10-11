#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main()
{
    char alpha[21] = {"abcdefghilmnopqrstuvz"}, parola[21], vocali[5], consonanti[16], cntVoc = 0, cntCons = 0;
    int rmd;
    srand(time(NULL));

    for (int i = 0; i < strlen(alpha)+1; i++)
    {
        rmd = rand() % 21;
        for (int j = 0; j < i; j++)
        {
            if (alpha[rmd] == parola[j])
            {
                i--;
                break;
            }
            parola[i] = alpha[rmd];
        }
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (parola[j] > parola[j+1])
            {
                int tmp = parola[j];
                parola[j] = parola[j+1];
                parola[j+1] = tmp;
            }
        }
    }

    for (int i = 0; i < 22; i++)
    {
        if (tolower(parola[i]) == 'a' || tolower(parola[i]) == 'e' || tolower(parola[i]) == 'i' || tolower(parola[i]) == 'o' || tolower(parola[i]) == 'u')
        {
            vocali[cntVoc] = parola[i];
            cntVoc++;
        }
        else
        {
            consonanti[cntCons] = parola[i];
            cntCons++;
        }
    }

    for (int i = 0; i < cntCons; i++)
    {
        printf("%c", consonanti[i]);
    }
    printf("%s\n", vocali);

    printf("\n");
}