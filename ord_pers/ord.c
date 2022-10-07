#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 100

int main()
{
    int numeri[DIM], rdm = 0, pariCnt = 0, dispCnt = 0;
    srand(time(NULL));

    for (int i = 0; i < DIM; i++)
    {
        rdm =  1 + rand() % 200;
        for (int j = 0; j <= i; j++)
        {
            if (rdm == numeri[j])
            {
                i--;
                break;
            }
            if (j == i)
            {
                numeri[i] = rdm;
            }
        }
    }

    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i]%2) == 0)
            printf("%d ", numeri[i]);
    }

    printf("\n\n");

    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i]%2) != 0)
            printf("%d ", numeri[i]);
    }

    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i] % 2) == 0)
        {
            pariCnt++;
        }
        else
        {
            dispCnt++;
        }
    }

    int dispari[dispCnt];

    pariCnt = (pariCnt > 20) ? 20 : pariCnt;

    dispCnt = (dispCnt > 20) ? 20 : dispCnt;


    for (int i = 0; i < pariCnt; i++)
    {
        for (int j = i; j < DIM; j++)
        {
            if ((numeri[j] % 2) == 0)
            {
                int tmp = numeri[j];
                numeri[j] = numeri[i];
                numeri[i] = tmp;
                break;
            }
        }
    }

    for (int i = pariCnt; i < pariCnt + dispCnt; i++)
    {
        for (int j = pariCnt; j < pariCnt + dispCnt; j++)
        {
            if (numeri[j] > numeri[j+1])
            {
                int tmp = numeri[j];
                numeri[j] = numeri[j+1];
                numeri[j+1] = tmp;
            }
        }
    }

    /*for (int i = 0; i < DIM - 1; i++)
    {
        for (int j = 0; j < DIM - 1; j++)
        {
            if (numeri[j] > numeri[j+1])
            {
                int tmp = numeri[j];
                numeri[j] = numeri[j+1];
                numeri[j+1] = tmp;
            }
        }
    }*/


    printf("\n\n\n\n\n");

    for (int i = 0; i < pariCnt; i++)
    {
        printf("%d ", numeri[i]);
    }
printf("\n\n\n\n\n");
    for (int i = pariCnt; i < pariCnt + dispCnt; i++)
    {
        printf("%d ", numeri[i]);
    }

    return 0;
}