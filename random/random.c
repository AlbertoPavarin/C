#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 1000000

int main()
{
    int numeri[DIM], rdm = 0;
    FILE *file;
    srand(time(NULL));

    if ((file = fopen("numeri.txt", "w+")) == NULL)
    {
        printf("Errore apertura file\n");
        return -1;
    }

    for (int i = 0; i < DIM; i++)
    {
        rdm = rand() % DIM;
        for (int j = 0; j < i; j++)
        {
            if (rdm == numeri[j])
            {
                i--;
                break;
            }
            if (j == i - 1)
            {
                numeri[i] = rdm;
                fprintf(file, "%d\n", numeri[i]);
            }
        }

    }

    fclose(file);
    printf("Numeri stampati sul file numeri.txt\n");

    return 0;
}