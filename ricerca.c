#include <stdio.h>
#include <stdlib.h>

int ricerca_numero(int numero, int numeri[], int dim);

int main(int argc, char *argv[])
{
    int numero;
    if (argc == 1) // Se gli argomenti sono 1 cioe' solo ./<nome del file> allora viene stampato l'uso del programma  
    {
        printf("Inserisci dei numeri dalla Console:\n Uso: ./<nome file> 1 2 3 ecc.\n");
        return 1;
    }
    int numeri[argc]; // array per contenere i numeri passati all'esecuzione 
    for (int i = 1; i < argc; i++) // ciclo for per popolare l'array numeri
    {
        numeri[i] = atoi(argv[i]); 
    }
    printf("\nInserisci un numero che vuoi cercare tra quelli inseriti precedentemente\n");
    scanf("%i", &numero); // viene chiesto il numero da cercare
    
    int posizione = ricerca_numero(numero, numeri, argc); // viene salvato nella variabile posizione il numero ritornato dalla funzione ricerca_numero
    if (posizione == -1) // se posizione e' uguale a -1 allora viene stampato a schermo che il numero non e' presente nell'array
    {
        printf("\nNumero non presente\n");
        return 1;
    }
    printf("\nIl numero %i si trova nella posizione %i\n", numero, posizione); // se nell'array e' presente il numero allora viene stampata la posizione del numero
}

int ricerca_numero(int numero, int numeri[], int dim)
{
    for (int i = 0; i < dim; i++)
    {
        if (numero == numeri[i]) // Viene controllato se il numero e' presente nell'array
            return i - 1;      
    }
    return -1;
}
