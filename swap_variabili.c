#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int x, y;
    printf("Inserisci il valore di X:\n");
    scanf("%i", &x);
    printf("\nInserisci il valore di Y:\n");
    scanf("%i", &y);
    printf("\n\nVariabili prima dello swap:\n");
    printf("X: %i\nY: %i\n\n", x, y);
    swap(&x, &y);
    printf("Variabili dopo lo swap:\n");
    printf("X: %i\nY: %i\n", x, y);
    return 0;
}