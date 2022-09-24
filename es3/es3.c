#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 5

void stampaElementi(int numeri[])
{
    for (int i = 0; i < DIM; i++)
    {
        printf("%d ", numeri[i]);
    }
    printf("\n");
}

void stampaElementiInversi(int numeri[])
{
    for (int i = DIM - 1; i >= 0; i--)
    {
        printf("%d ", numeri[i]);
    }
    printf("\n");
}

void sommaMedia(int numeri[], int *somma, float *media)
{
    for (int i = 0; i < DIM; i++)
    {
        
        (*somma) += numeri[i];
    }

    (*media) = (*somma) / DIM;
}

void stampareNumeriPari(int numeri[])
{
    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i] % 2) == 0)
        {
            printf("%d ", numeri[i]);
        }
    }
    printf("\n");
}

void stampareNumeriDispari(int numeri[])
{
    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i] % 2) != 0)
        {
            printf("%d ", numeri[i]);
        }
    }
    printf("\n");
}

int ricercaNumero(int numeri[], int numeroCercare)
{
    int cnt;

    for (int i = 0; i < DIM; i++)
    {
        if (numeri[i] == numeroCercare)
        {
            cnt++;
        }
    }

    return cnt;
}

int eliminaElemento(int numeri[], int numeroDaEliminare)
{
    int trovato = 0;
    int j = 0;
    for (int i = 0; i < DIM; i++)
    {
        if (numeri[i] != numeroDaEliminare)
        {
            numeri[j++] = numeri[i];
        }
    }

    return j;
}

void scambiaPosizioni(int numeri[])
{
    int tmp = 0, i = 1;
    while (i < DIM)
    {
        tmp = numeri[i];
        numeri[i] = numeri[i - 1];
        numeri[i - 1] = tmp;
        i += 2;
    }
}

void riodina(int numeri[])
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if (numeri[j] > numeri[j + 1])
            {
                int tmp = numeri[j];
                numeri[j] = numeri[j + 1];
                numeri[j + 1] = tmp;
            }
        }
    }
}

int main()
{
    int scelta, numeri[DIM], nDaCerc, nDaElim, somma = 0;
    float media = 0;

    for (int i = 0; i < DIM; i++)
    {
        printf("Inserisci numero\n");
        scanf("%d", &numeri[i]);
    }

    printf("\n");

    do 
    {
        printf("Premi 1 per Stampare gli elementi dell'array\n");
        printf("Premi 2 per Stampare gli elementi dell'array in modo inverso\n");
        printf("Premi 3 per fare la somma e media degli elementi degli array\n");
        printf("Premi 4 per Stmapare gli elementi pari\n");
        printf("Premi 5 per Stampare gli elementi dispari\n");
        printf("Premi 6 per Ricercare un numero nell'array\n");
        printf("Premi 7 per Eliminare un elemento dell'array\n");
        printf("Premi 8 per Alternare a due a due le posizioni dell'array\n");
        printf("Premi 9 per Ordinare l'array\n");
        scanf("%d", &scelta);
        printf("\n");
    } while (scelta < 1 || scelta > 8);

    switch (scelta)
    {
        case 1:
            stampaElementi(numeri);
            break;
        case 2:
            stampaElementiInversi(numeri);
            break;
        case 3:
            sommaMedia(numeri, &somma, &media);
            printf("La somma è : %d\nLa media è: %.2f\n", somma, media);
            break;
        case 4:
            stampareNumeriPari(numeri);
            break;
        case 5:
            stampareNumeriDispari(numeri);
            break;
        case 6:
            printf("Inserisci un numero da cercare\n");
            scanf("%d", &nDaCerc);
            printf("Il numero %d compare %d volte\n", nDaCerc, ricercaNumero(numeri, nDaCerc));
            break;
        case 7:
            printf("Inserisci un numero da eliminare\n");
            scanf("%d", &nDaElim);
            int n = eliminaElemento(numeri, nDaElim);
            for (int i = 0; i < n; i++)
            {
                //if (numeri[i] != 0)
                //{
                    printf("%d ", numeri[i]);
                //}
            }
            printf("\n");
            break;
        case 8:
            scambiaPosizioni(numeri);
            stampaElementi(numeri);
            break;
        case 9:
            riodina(numeri);
            stampaElementi(numeri);
            break;
        default:
            break;
    }
}