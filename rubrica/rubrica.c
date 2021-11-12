#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char cognome[50];
    char numero[50];
} Persona_T;


void mostraRubrica(char contenutoFile[100][100], int lung)
{
    for (int i = 0; i < lung; i++)
    {
        printf("%s", contenutoFile[i]);        
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int lunghezza = 0;
    int scelta;
    if (argc != 2 && argc != 4)
    {
        printf("Errore negli argomenti\n");
        exit(0);
    }
    FILE *input = fopen(argv[1], "r+");
    if (input == NULL)
    {
        printf("Il file in input non esiste\n");
        exit(1);
    }

    char contenutoFile[100][100];
    Persona_T persona[100];
    while(fscanf(input, "%s", contenutoFile[lunghezza]) != EOF)
    {
        lunghezza++;
    }
    fclose(input);

    printf("Premi 1 per mostrare la rubrica a video\nPremi 2 per aggiungere un contatto alla rubrica\nPremi 3 per eliminare un contatto dalla rubrica dopo averlo ricercato con il suo numero di telefono\n\n");
    scanf("%d", &scelta);
    switch (scelta)
    {
        case 1:
            mostraRubrica(contenutoFile, sizeof(input));
            break;
        case 2:
            printf("sus2\n");
            break;
        case 3:
            printf("sus3\n");
            break;
        default:
            printf("Errore\n");
            break;
    }
}