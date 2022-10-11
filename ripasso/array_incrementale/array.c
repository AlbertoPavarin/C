#include <stdio.h>
#include <stdlib.h>

int inserimento(int array[], int dim)
{
    array = realloc(array, (dim + 1)*sizeof(int));
    printf("Inserisci numero\n");
    scanf("%d", &array[dim]);
    return dim + 1;
}

int main()
{
    int *numeri, dim = 0;
    numeri = malloc(sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        dim = inserimento(numeri, dim);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", numeri[i]);
    }

    printf("\n");
}