#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ordinaDec(char str[])
{
    int tmp;
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        for (int j = 0; j < strlen(str) - 1; j++)
        {
            if (str[j] < str[j+1])
            {
                tmp = str[j];
                str[j] = str[j+1];
                str[j+1] = tmp;
            }
        }
    }
}

void ordinaCres(char str[])
{
    int tmp;
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        for (int j = 0; j < strlen(str) - 1; j++)
        {
            if (str[j] > str[j+1])
            {
                tmp = str[j];
                str[j] = str[j+1];
                str[j+1] = tmp;
            }
        }
    }
}


int main()
{
    char str[50], pari[50], dispari[50], lettere[50];
    int cntDisp = 0, cntPari = 0, k = 0;

    printf("Inserisci stringa\n");
    scanf("%s", str);

    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]) > 0)
        {
            lettere[k++] = str[i];
            if ((str[i]%2) == 0)
            {
                pari[cntPari++] = str[i]; // salvo i numeri pari su un array
            }
            else
            {
                dispari[cntDisp++] = str[i];// salvo i numeri dispari su un array
            }
        }
    }

    if (cntPari > 0)
    {
        ordinaDec(pari);
    }
    
    if (cntDisp > 0)
    {
        ordinaCres(dispari);
    }

    // metto nelle posizioni corrette prima le lettere dispari e poi le lettere pari 
    for (int i = 0; i < cntPari; i++)
    {
        lettere[i] = pari[i];
    }

    k = 0;

    for (int i = cntPari; i < strlen(lettere); i++)
    {
        lettere[i] = dispari[k++];
    }

    printf("\n\n%s\n", lettere);

    return 0;
}