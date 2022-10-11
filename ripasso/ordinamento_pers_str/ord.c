#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

void ordina(char parola[], int inizio,  int fine)
{
    for (int i = inizio; i < fine; i++)
    {
        for (int j = inizio; j < fine; j++)
        {
            if (parola[j] > parola[j+1])
            {
                int tmp = parola[j];
                parola[j] = parola[j+1];
                parola[j+1] = tmp;
            }
        }
    }
}

int main()
{
    char alpha[21] = {"abcdefghilmnopqrstuvz"}, parola[21] = "", vocali[5], consonanti[16];
    int rmd, cntCons, cntVoc, k = 0;
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
            if (j == i-1)
            {
                parola[i] = alpha[rmd];
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

    ordina(vocali, 0, strlen(vocali)-1);
    ordina(consonanti, 0, cntCons-1);

    printf("%s", vocali);
    for (int i = 0; i < cntCons; i++)
    {
        printf("%c", consonanti[i]);
    }
    printf("\n\n");

    for (int i = 3; i < 5; i++)
    {
        parola[8+k] = vocali[i];
        k++;
    }

    for (int i = 6; i < 17; i++)
    {
        parola[8+k] = consonanti[i];
    }
}