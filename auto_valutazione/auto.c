#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 5

void ordinaDec(int num[], int dim)
{
    int tmp;
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            if (num[j] < num[j+1])
            {
                tmp = num[j];
                num[j] = num[j+1];
                num[j+1] = tmp;
            }
        }
    }
}

void ordinaCres(int num[], int dim)
{
    int tmp;
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            if (num[j] > num[j+1])
            {
                tmp = num[j];
                num[j] = num[j+1];
                num[j+1] = tmp;
            }
        }
    }
}


int main()
{
    int numeri[DIM], cnt = 0, numeriEsaminati[DIM], dispari[DIM], pari[DIM], cntPari = 0, cntDispari = 0, k = 0, dim = DIM, c = 0, controllo = 0, num[DIM], ne = 0;
    for (int i = 0; i < DIM; i++)
    {
        printf("Inserisci %d° numero\n", i + 1);
        scanf("%d", &numeri[i]);
    }

    printf("\n\n");

    for (int i = 0; i < DIM; i++)
    {
        cnt = 0;
        for (int j = 0; j < DIM; j++)
        {
            if (numeriEsaminati[j] == numeri[i])
            {
                break;
            }
            else if (numeri[i] == numeri[j])
            {
                cnt++;
            }
            if (j == DIM - 1)
            {
                printf("%d cnt: %d\n", numeri[i], cnt);
            }
        }
        numeriEsaminati[ne++] = numeri[i];
    }

    for (int i = 0; i < dim; i++)
    {
        controllo = 0;
        for (int j = 0; j < c; j++)
        {
            if (i != j)
            {
                if (numeri[i] == num[j])
                {
                    controllo = 1;
                    break;
                }
            }
        }
        if (controllo == 0)
        {
            num[c] = numeri[i];
            c++;
        }
    }

    for (int i = 0; i < DIM; i++)
    {
        if ((numeri[i]%2) == 0)
        {
            pari[cntPari++] = numeri[i];
        }
        else
        {
            dispari[cntDispari++] = numeri[i];
        }
    }    

    ordinaCres(pari, cntPari);
    ordinaDec(dispari, cntDispari);

    for (int i = 0; i < cntPari; i++)
    {
        numeri[i] = pari[i];
    }   

    for (int i = cntPari; i < DIM; i++)
    {
        numeri[i] = dispari[k++];
    } 

    printf("\n\n");

    for (int i = 0; i < DIM; i++)
    {
        printf("%d\n", numeri[i]);
    } 

    printf("\n\n");

    for (int i = 0; i < c; i++)
    {
        printf("%d\n", num[i]);
    } 

    return 0;
}