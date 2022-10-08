#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 100

void ordina(int array[], int inizio, int fine)
{
    for (int i = inizio; i < fine - 1; i++)
    {
        for (int j = inizio; j < fine - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

int main()
{
    int numeri[DIM], rdm = 0, pariCnt = 0, dispCnt = 0, controlloDispari = 0, controlloPari = 0, cntNum2 = 0, k = 0;
    srand(time(NULL));

    for (int i = 0; i < DIM; i++)
    {
        rdm =  1 + rand() % 233;
        for (int j = 0; j <= i; j++)
        {
            if (rdm == numeri[j])
            {
                i--;
                break;
            }
            if (j == i)
            {
                if ((rdm % 2) == 0)
                {
                    pariCnt++;
                }
                else
                {
                    dispCnt++;
                }
                numeri[i] = rdm;
            }
        }
    }

    int dispari[dispCnt];
    int pari[pariCnt];

    pariCnt = (pariCnt > 20) ? 20 : pariCnt;

    dispCnt = (dispCnt > 20) ? 20 : dispCnt;

    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i]%2) == 0)
        {
            pari[controlloPari] = numeri[i];
            controlloPari++;
        }
        else if ((numeri[i]%2) != 0)
        {
            dispari[controlloDispari] = numeri[i];
            controlloDispari++;
        }
    }

    ordina(pari, 0, controlloPari);
    ordina(dispari, 0, controlloDispari);

    for (int i = pariCnt; i < controlloPari; i++)
    {
        numeri[pariCnt + dispCnt + k] = pari[i];
        k++;
    }

    for (int i = dispCnt; i < controlloDispari; i++)
    {
        numeri[pariCnt + dispCnt + k] = dispari[i];
        k++;
    }


    for (int i = 0; i < pariCnt; i++)
    {
        numeri[i] = pari[i];
    }

    for (int i = 0; i < dispCnt; i++)
    {
        numeri[dispCnt+i] = dispari[i];
    }

    ordina(numeri, dispCnt+pariCnt, DIM);

    for (int i = 0; i < DIM; i++)
    {
        printf("%d ", numeri[i]);
    }

    printf("\n");

    return 0;
}