#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char parola[50], str[50];
    int k = 0;

    printf("Inserisci una parola\n");
    scanf("%s", parola);

    for (int i = 0; i < strlen(parola); i++)
    {
        if (isalpha(parola[i]) > 0) // returna un valore maggiore di 0 se e' una lettera
        {
            str[k++] = parola[i];
        }
    }

    printf("Parola con solo lettere %s\n", str);
}