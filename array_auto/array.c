#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int inserimentoNumero(int array[], int dim)
{
    array = realloc(array, (dim + 1)*sizeof(int));
    printf("Inserisci un numero\n");
    scanf("%d", &array[dim + 1]);
    printf("\nNumeri: ");
    for (int i = 1; i <= dim; i++)
    {
        printf("%d ", array[i]);
    }
    printf("%d\n", array[dim + 1]);
    return dim + 1;
}

int verificaNumero(int array[], int dim)
{
    int nDaCerc = 0;
    printf("Inserisci il numero da cercare\n\n");
    scanf("%d", &nDaCerc);
    for (int i = 1; i <= dim; i++)
    {
        if (array[i] == nDaCerc)
        {
            return i;
        }
    }

    return -1;
}

int eliminaNumero(int array[], int dim)
{
    int k = 0, nDaElim;
    printf("Inserisci il numero da eliminare\n");
    scanf("%d", &nDaElim);

    for (int i = 1; i <= dim; i++)
    {
        if (nDaElim != array[i])
        {
            array[k++] = array[i];
        }
    }
    printf("Numeri: ");
    for (int i = 0; i < k; i++)
    {
        printf("%d ", array[i]);
    }

    return k;
}

void riodina(int array[], int dim)
{
    for (int i = 1; i <= dim; i++)
    {
        for (int j = 1; j <= dim; j++)
        {
            if (array[j] > array[j + 1])
            {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }

    printf("\nNumeri: ");
    for (int i = 1; i <= dim; i++)
    {
        printf("%d ", array[i+1]);
    }
    printf("\n");
}

int main()
{
    int scelta = 0;
    int dim = 0, pos;
    int *array = malloc(sizeof(int));
    do 
    {
        printf("Premi 0 per uscire\n");
        printf("Premi 1 per inserire un numero\n");
        printf("Premi 2 per verificare un numero\n");
        printf("Premi 3 per eliminare un numero\n");
        printf("Premi 4 per ordinare l'array\n");

        scanf("%d", &scelta);

        switch(scelta)
        {
            case 0:
                break;
            case 1:
                dim = inserimentoNumero(array, dim);
                break;
            case 2:
                pos = verificaNumero(array, dim);
                printf("Numero trovato in posizione %d\n\n", pos);
                break;
            case 3:
                dim = eliminaNumero(array, dim);
                printf("\nNumero eliminato\n\n");
                break;
            case 4:
                riodina(array, dim);
                break;
        }
    }
    while (scelta != 0);

    free(array);
}