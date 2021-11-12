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
    printf("La tua rubrica e':\n");
    for (int i = 1; i <= lung; i++)
    {
        printf("%s ", contenutoFile[i - 1]);       
        if (i%3 == 0)
            printf("\n");
    }
    printf("\n");
}

void aggiuntaContatto(FILE *rubrica, char contenutoFile[100][100], int lung)
{
    int cont;
    char numeri[100][100];
    printf("Numeri gia' esistenti:\n");
    for (int i = 1; i <= lung; i++)
    {
        if (i % 3 == 0)
        {
            strcpy(numeri[i-1], contenutoFile[i-1]);
            printf("%s\n", numeri[i - 1]);
            cont += 3;
        }
    }
    Persona_T persona;
    printf("\nInserisci il nome della persona che desideri inserire nella rubrica\n");
    scanf("%s", persona.nome);

    printf("Inserisci il cognome di %s\n", persona.nome);
    scanf("%s", persona.cognome);

    do
    {
        printf("Inserisci il numero di %s %s\n", persona.nome, persona.cognome);
        scanf("%s", persona.numero);
    }
    while (strlen(persona.numero) != 10);
    
    for (int i = 0; i <= cont; i++)
    {
        if (strcmp(numeri[i+2], persona.numero) == 0)
        {
            printf("Numero gia' esistente\n");
            exit(2);
        }
    }
    fprintf(rubrica, "\n%s %s %s", persona.nome, persona.cognome, persona.numero);
}

void eliminaContatto(FILE *input, char contenutoFile[100][100], int lung)
{
    //Da implemantare
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
    FILE *rubrica = fopen(argv[1], "r+");
    if (rubrica == NULL)
    {
        printf("Il file in input non esiste\n");
        exit(1);
    }

    char contenutoFile[100][100];
    while(fscanf(rubrica, "%s", contenutoFile[lunghezza]) != EOF)
    {
        lunghezza++;
    }

    printf("Premi 1 per mostrare la rubrica a video\nPremi 2 per aggiungere un contatto alla rubrica\nPremi 3 per eliminare un contatto dalla rubrica dopo averlo ricercato con il suo numero di telefono\n\n");
    scanf("%d", &scelta);
    printf("\n");
    switch (scelta)
    {
        case 1:
            mostraRubrica(contenutoFile, lunghezza);
            break;
        case 2:
            // Implementare scrittura su nuovo file
            aggiuntaContatto(rubrica, contenutoFile, lunghezza);
            break;
        case 3: 
            // Implementare completamente
            eliminaContatto(rubrica, contenutoFile, lunghezza);
            break;
        default:
            printf("Errore\n");
            break;
    }
    fclose(rubrica);
}