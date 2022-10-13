#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ordina(char str[])
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

int main()
{
    //es1
    char str[50], carattere[1], caratteriEsaminati[50];
    int cnt = 0, piuAlto = 0;

    printf("Inserisci stringa\n");
    scanf("%s", str);

    for (int i = 0; i < strlen(str); i++)
    {
        cnt = 0;
        for (int j = 0; j < strlen(str); j++)
        {
            if (str[i] == str[j] && caratteriEsaminati[j] != str[i])
            {
                cnt++;
            }
        }
        if (cnt > piuAlto)
        {
            carattere[0] = str[i];
            piuAlto = cnt;
            printf("La lettera %c compare %d volte\n", carattere[0], cnt);
        }
        caratteriEsaminati[i] = str[i];
    }


    //es2
    int cntLett = 0, cntNum = 0, cntCS = 0, k = 0;

    char numeri[50], caratteriSpec[50], lettere[50];

    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]) > 0) // isalpha returna un numero > 0 se il carattere è dell'alfabeto
        {
            lettere[cntLett++] = str[i]; // salvo le lettere in vettore dedicato
        }
        
        else if(isdigit(str[i]) > 0) // isdigit return un numero > 0 se il carattere è un numero
        {
            numeri[cntNum++] = str[i]; // salvo i numeri in un array deidicato
        }
        else 
        {
            caratteriSpec[cntCS++] = str[i]; // salvo i caratteri speciali in un array dedicato
        }
    }

    if (cntNum > 0)
    {
        ordina(numeri);
    }
    if (cntLett > 0)
    {
        ordina(lettere);
    }
    if (cntCS > 0)
    {
        ordina(caratteriSpec);
    } 

    // Metto nelle posizione corrette i caratteri speciali, poi i numeri e poi le lettere
    for (int i = 0; i < cntCS; i++)
    {
        str[i] = caratteriSpec[k++];
    }
    k = 0;
    for (int i = cntCS; i < cntCS+cntNum; i++)
    {
        str[i] = numeri[k++];
    }
    k = 0;
    for (int i = cntCS+cntNum; i < strlen(str); i++)
    {
        str[i] = lettere[k++];
    }

    printf("Stringa ordinata: %s\n", str);

    return 0;
}