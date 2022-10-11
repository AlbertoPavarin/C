#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void eliminaSpazi(char stringa[], char str[])
{
    int k = 0; 
    for (int i = 0; i < strlen(stringa)-1; i++)
    {
        if (stringa[i] != ' ')
        {
           str[k++] = stringa[i];
        }
    }
}

int palindromo(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != str[strlen(str) - 1 - i])
        {
            return -1;
        }
    }

    return 1;
}

int main()
{
    char stringa[50], str[50];
    printf("Inserisci una stringa\n");
    fgets(stringa, sizeof(stringa), stdin);

    eliminaSpazi(stringa, str);

    if (palindromo(str) > 0)
    {
        printf("La stringa e' palindroma\n");
    }
    else
    {
        printf("La stringa non e' palindroma\n");
    }
}