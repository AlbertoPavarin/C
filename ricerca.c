#include <stdio.h>
#include <stdlib.h>

int ricerca_numero(int numero, int numeri[], int dim);

int main(int argc, char *argv[])
{
    int numero;
    if (argc == 1)
    {
        printf("Inserisci dei numeri dalla Console:\n Uso: ./<nome file> 1 2 3 ecc.\n");
        return 1;
    }
    int numeri[argc];
    for (int i = 1; i < argc; i++)
    {
        numeri[i] = atoi(argv[i]);
    }
        printf("\nInserisci un numero che vuoi cercare tra quelli inseriti precedentemente\n");
        scanf("%i", &numero);
    
    int posizione = ricerca_numero(numero, numeri, argc);
    if (posizione == -1)
    {
        printf("\nNumero non presente\n");
        return 1;
    }
    printf("\nIl numero %i si trova nella posizione %i\n", numero, posizione);
}

int ricerca_numero(int numero, int numeri[], int dim)
{
    for (int i = 0; i < dim; i++)
    {
        if (numero == numeri[i])
            return i - 1;      
    }
    return -1;
}
