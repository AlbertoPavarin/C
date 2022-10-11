#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char parola[25], str[25];
    int k = 0;
    printf("Inserisci una parola\n");
    scanf("%s", parola);

    for (int i = 0; i < strlen(parola); i++)
    {
        if (isdigit(parola[i]) == 0)
        {
            str[k++] = parola[i];
        }
    }

    printf("Parola senza numeri: %s\n", str);
}