#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char parola[50];
    printf("Inserisci parola\n");
    scanf("%s", parola);

    for (int i = 0; i < strlen(parola) - 1; i++)
    {
        for (int j = 0; j < strlen(parola) - 1; j++)
        {
            if (parola[j] > parola[j+1])
            {
                int tmp = parola[j];
                parola[j] = parola[j+1];
                parola[j+1] = tmp;
            }
        }
    }

    printf("Parola in ordine alfabetico: %s \n", parola);
}