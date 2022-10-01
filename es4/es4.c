#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DIM 100

int controllaLettere(char stringa[])
{

    for (int i = 0; i < strlen(stringa); i++)
    {
        if (isalpha(stringa[i]) == 0)
        {
            return -1;
        }
    }

    return 1;
}

int contaVocali(char stringa[])
{
    int cnt = 0;
    for (int i = 0; i < strlen(stringa); i++)
    {
        if (tolower(stringa[i]) == 'a' || tolower(stringa[i]) == 'i' || tolower(stringa[i]) == 'e' || tolower(stringa[i]) == 'o' || tolower(stringa[i]) == 'u')
        {
            cnt++;
        }
    }

    return cnt;
}

int contaConsonanti(char stringa[])
{
    int cnt = 0;
    for (int i = 0; i < strlen(stringa); i++)
    {
        if (tolower(stringa[i]) != 'a' && tolower(stringa[i]) != 'i' && tolower(stringa[i]) != 'e' && tolower(stringa[i]) != 'o' && tolower(stringa[i]) != 'u')
        {
            cnt++;
        }
    }

    return cnt;
}

int contaLettera(char stringa[])
{
    char lettera[1];
    int cnt = 0;
    printf("Inserisci la lettera che vuoi cercare\n");
    scanf("%s", lettera);

    for (int i = 0; i < strlen(stringa); i++)
    {
        if (lettera[0] == stringa[i])
        {
            cnt++;
        }
    }

    return cnt;
}

void creaNuoveStringhe(char stringa[], char str1[], char str2[])
{
    for (int i = 0; i < strlen(stringa); i++)
    {
        if ((i % 2) == 0)
        {
            strncat(str1, &stringa[i], 1);
        }
        else
        {
            strncat(str2, &stringa[i], 1);
        }
    }
}

int controllaDoppie(char stringa[])
{
    for (int i = 0; i < strlen(stringa); i++)
    {
        for (int j = i + 1; j < strlen(stringa); j++)
        {
            if (stringa[i] == stringa[j])
            {
                return -1;
            }
        }
    }

    return 1;
}

int controllaLunghezza(char stringa1[], char stringa2[])
{
    if (strlen(stringa1) > strlen(stringa2))
    {
        return 1;
    }
    else if (strlen(stringa1) < strlen(stringa2))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void contaLettereEntrambe(char str1[], char str2[])
{
    printf("Lettere contenute in entrambe:\n");
    for (int i = 0; i < strlen(str1); i++)
    {
        for (int j = 0; j < strlen(str2); j++)
        {
            if (str1[i] == str2[j])
            {
                printf("%c\n", str1[i]);
            }
        }
    }
}

int main()
{
    char str1[DIM], str2[DIM], strPari[DIM], strDispari[DIM];
    int scelta, piuLung, voc1, voc2, con1, con2;

    printf("Inserisci stringa\n");
    scanf("%s", str1);

    printf("Premi 1 per verificare che la stringa contenga solo lettere\n");
    printf("Premi 2 per contare le vocali nella stringa\n");
    printf("Premi 3 per contare il numero di consonanti\n");
    printf("Premi 4 per contare una lettera scelta dell'utente\n");
    printf("Premi 5 per creare 2 nuove stringhe che contengono 1 le lettere di posizione pari; la 2° le lettere di posizione dispari\n");
    printf("Premi 6 per verificare la presenza di lettere doppie\n");
    scanf("%d", &scelta);

    printf("\n\n");

    switch (scelta)
    {
        case 1:
            if (controllaLettere(str1) == -1)
            {
                printf("Non sono presenti solo lettere\n");
            }
            else
            {
                printf("Sono presenti solo lettere\n");
            }
            break;
        case 2:
            printf("Vocali presenti: %d\n", contaVocali(str1));
            break;
        case 3:
            printf("Consonanti presenti: %d\n", contaConsonanti(str1));
            break;
        case 4:
            printf("La lettera compare %d volte\n", contaLettera(str1));
            break;
        case 5:
            creaNuoveStringhe(str1, strPari, strDispari);
            printf("Stringa che contengono le lettere in posizione pari: %s\n", strPari);
            printf("Stringa che contengono le lettere in posizione dispari: %s\n", strDispari);
            break;
        case 6:
            if (controllaDoppie(str1) == 1)
            {
                printf("Non sono presenti doppie lettere\n");
            }
            else
            {
                printf("Sono presenti doppie lettere\n");
            }
            break;
    }

    printf("\n\n");

    printf("Inserisci una seconda stringa\n");
    scanf("%s", str2);

    printf("Premi 1 per verificare quale delle due stringhe è la più lunga\n");
    printf("Premi 2 per verifica quali lettere sono presenti in entrambe le stringhe\n");
    printf("Premi 3 per verificare quale stringa contentiene più vocali\n");
    printf("Premi 4 per verificare quale stringa contentiene più consonanti\n");
    scanf("%d", &scelta);

    printf("\n\n");

    switch (scelta)
    {
        case 1:
            if ((piuLung = controllaLunghezza(str1, str2)) > 0)
            {
                printf("La stringa più lunga è la: %d\n", piuLung);
            }
            else
            {
                printf("Le stringhe hanno la stessa lunghezza\n");
            }
            break;
        case 2:
            contaLettereEntrambe(str1, str2);
            break;
        case 3:
            if ((voc1 = contaVocali(str1)) > (voc2 = contaVocali(str2)))
            {
                printf("La prima stringa contiene più vocali\n");
            }
            else if (voc1 < voc2)
            {
                printf("La seconda stringa contiene più vocali\n");
            }
            else
            {
                printf("Le stringhe contengono lo stesso numero di vocali\n");
            }
            break;
        case 4:
            if ((con1 = contaConsonanti(str1)) > (con2 = contaConsonanti(str2)))
            {
                printf("La prima stringa contiene più consonanti\n");
            }
            else if (con1 < con2)
            {
                printf("La seconda stringa contiene più consonanti\n");
            }
            else
            {
                printf("Le stringhe contengono lo stesso numero di consonanti\n");
            }
            break;
    }

    return 0;
}