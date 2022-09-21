#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 6

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
    int n = DIM;
    for (int i = 0; i < DIM; i++)
    {
        if (numeri[i] == numeroDaEliminare)
        {
            numeri[i] = numeri[i + 1];
            trovato = 1;
            n--;
        }
        if (trovato == 1)
        {
            numeri[i] = numeri[i + 1];
        }
    }

    return n;
}

int main()
{
    int scelta, numeri[DIM], nDaCerc, nDaElim;

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
        printf("Premi 3 per Stmapare gli elementi pari\n");
        printf("Premi 4 per Stampare gli elementi dispari\n");
        printf("Premi 5 per Ricercare un numero nell'array\n");
        printf("Premi 6 per Eliminare un elemento dell'array\n");
        printf("Premi 7 per Alternare a due a due le posizioni dell'array\n");
        printf("Premi 8 per Ordinare l'array\n");
        scanf("%d", &scelta);
        printf("\n");
    } while (scelta < 1 || scelta > 7);

    switch (scelta)
    {
        case 1:
            stampaElementi(numeri);
            break;
        case 2:
            stampaElementiInversi(numeri);
            break;
        case 3:
            stampareNumeriPari(numeri);
            break;
        case 4:
            stampareNumeriDispari(numeri);
            break;
        case 5:
            printf("Inserisci un numero da cercare\n");
            scanf("%d", &nDaCerc);
            printf("Il numero %d compare %d volte\n", nDaCerc, ricercaNumero(numeri, nDaCerc));
            break;
        case 6:
            printf("Inserisci un numero da eliminare\n");
            scanf("%d", &nDaElim);
            int n = eliminaElemento(numeri, nDaElim);
            for (int i = 0; i < n; i++)
            {
                printf("%d ", numeri[i]);
            }
            printf("\n");
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
    }
}