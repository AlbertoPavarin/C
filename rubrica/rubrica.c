/// @file    rubrica.c
/// @brief   Programma di gestione di una rubrica, permette di visualizzare la rubrica e modificarla, eliminando o aggiungedo contatti
/// @date    14/11/2021   

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
* @brief    struct Persona_T, formata da un nome, cognome e numero
* @param    char nome: il nome della persona
* @param    char cognome: cognome della persona
* @param    char numero: numero di telefono della persona
*/

typedef struct  
{
    char nome[50];
    char cognome[50];
    char numero[10];
} Persona_T;

/**
* @fn       void mostraRubrica(char contenutoFile[100][100], int lunghezza)
* @brief    funzione che stampa il contenuto della rubrica
* @param    char ContenutoFile[100][100]: contenuto del file passato in input
* @param    char lunghezza: numero che contiene il numero di parole lette dal file
*/

void mostraRubrica(char contenutoFile[100][100], int lung)
{
    printf("\nLa tua rubrica e':\n");
    for (int i = 1; i <= lung; i++)
    {
        printf("%s ", contenutoFile[i - 1]);       
        if (i%3 == 0)
            printf("\n");
    }
    printf("\n");
}

/**
* @fn       Persona_T creazioneContatto(char numeri[100][100], int cont)
* @brief    funzione che permette di creare una nuova persona inserendo il nome, il cognome e il numero di telefono
* @param    char numeri[100][100]: contiene tutti i numeri presenti nella rubrica data in input
* @param    int cont: contiene il numero di parole lette dal file
* @return   Persona_T: la funzione ritorna la persona che si desidera inserire nella rubrica
*/

Persona_T creazioneContatto(char numeri[100][100], int cont)
{
    Persona_T persona;
    do 
    {
        printf("\nInserisci il nome della persona che desideri inserire nella rubrica\n");
        scanf("%s", persona.nome);
    } while (persona.nome == "");

    do
    {
        printf("Inserisci il cognome di %s\n", persona.nome);
        scanf("%s", persona.cognome);
    } while (persona.cognome == "");

    do
    {
        printf("Inserisci il numero di %s %s\n", persona.nome, persona.cognome);
        scanf("%s", persona.numero);
    }
    while (strlen(persona.numero) != 10);
    
    for (int i = 0; i <= cont; i++)
    {
        if (strcmp(numeri[i + 2], persona.numero) == 0)
        {
            printf("Numero gia' esistente\n");
            exit(2);
        }
    }

    return persona;
}

/**
* @fn       void aggiuntaContattoSov(FILE *rubrica, char contenutoFile[100][100], int lung, char numeri[100][100])
* @brief    funzione che permette di sovrascrive nella rubrica il nome della persona inserite tramite la funzione creazioneContatto
* @param    FILE *rubrica: puntatore file 
* @param    char contenutoFile[100][100]: contiene il contenuto del file passato in input
* @param    int lunghezza: numero che indica quante parole sono state lette dal file
* @param    char numeri[100][100]: contiene tutti i numeri della rubrica
*/

void aggiuntaContattoSov(FILE *rubrica, char contenutoFile[100][100], int lung, char numeri[100][100])
{
    Persona_T contatto = creazioneContatto(numeri, lung);
    fprintf(rubrica, "\n%s %s %s", contatto.nome, contatto.cognome, contatto.numero);
}

/**
* @fn       void aggiuntaContattoNF(FILE *rubrica, char contenutoFile[100][100], int lung, char numeri[100][100], char* nuovoFile)
* @brief    funzione che permette di scrivere in una nuova rubrica il contenuto della rubrica passata in input e il nome della persona inserite tramite la funzione creazioneContatto
* @param    FILE *rubrica: puntatore file 
* @param    char contenutoFile[100][100]: contiene il contenuto del file passato in input
* @param    int lunghezza: numero che indica quante parole sono state lette dal file
* @param    char numeri[100][100]: contiene tutti i numeri della rubrica
*/

void aggiuntaContattoNF(FILE *rubrica, char contenutoFile[100][100], int lung, char numeri[100][100], char* nuovoFile)
{
    Persona_T contatto = creazioneContatto(numeri, lung);
    FILE *nuovoOutput = fopen(nuovoFile, "a");
    if (nuovoOutput == NULL)
    {
        printf("Errore\n");
        exit(3);
    }
    for (int i = 0; i < lung; i++)
    {
        fprintf(nuovoOutput, "%s ", contenutoFile[i]);
        if ((i+1)%3 == 0 && i != lung - 1)
            fprintf(nuovoOutput, "\n");
    }
    fprintf(nuovoOutput, "\n%s %s %s", contatto.nome, contatto.cognome, contatto.numero);
    fclose(nuovoOutput);
}
 /**
 * @fn      void eliminaContatto(FILE *rubrica, char contenutoFile[100][100], int lung, char numeri[100][100], char *nomeFile)
 * @brief   funzione che permette di eliminare un contatto dalla rubrica
 * @param   char contenutoFile[100][100]: contiene il contenuto del file passato in input
 * @param   int lunghezza: numero che indica quante parole sono state lette dal file
 * @param   char numeri[100][100]: contiene tutti i numeri della rubrica
 * @param   char *nomeFile: nome del file passato in input
 */

void eliminaContatto(char contenutoFile[100][100], int lung, char numeri[100][100], char *nomeFile)
{
    bool trovato = false;
    int ind = -1;
    char numeroDaEl[10];
    printf("Inserisci il numero della persona che vuoi eliminare\n");
    scanf("%s", numeroDaEl);
    FILE *copia = fopen("copia.txt", "a");
    if (copia == NULL)
    {
        printf("Errore\n");
        exit(4);
    }
    for (int i = 0; i < lung; i++)
    {
        if (strcmp(numeroDaEl, contenutoFile[i]) == 0 && !trovato)
        {
            ind = i;
            trovato = true;
            i = -1;
        }
        else if (trovato && strcmp(numeroDaEl, contenutoFile[i]) != 0 && i != ind && i != ind - 1 && i != ind - 2)
        { 
            fprintf(copia, "%s ", contenutoFile[i]);
            if ((i+1)%3 == 0)
                fprintf(copia, "\n");
        }
    }
    fclose(copia);
    if (trovato)
    {
        printf("Numero trovato ed eliminato\n");
        remove(nomeFile);
        rename("copia.txt", nomeFile);
        exit(6);
    }
    else
    {
        printf("Numero non trovato\n");
        remove("copia.txt");
        exit(7);
    }
}

/**
* @fn       int main(int argc, char *argv[])
* @brief    funzione principale
* @param    int argc: contatore degli argomenti dati al momento dell'esecuzione
* @param    char *argv[]: contiene tutti gli argomenti inseriti
* @return   ritorna come si e' concluso il programma
*/

int main(int argc, char *argv[])
{
    int lunghezza = 0;
    int scelta;
    if (argc != 2 && argc != 4)
    {
        printf("Uso: ./rubrica.out rubrica.txt o ./rubrica.out rubrica.txt -f output.txt\n");
        exit(0);
    }
    if (argc == 4 && strcmp(argv[2], "-f") != 0)
    {
        printf("./rubrica.out rubrica.txt -f output.txt\n");
        exit(5);
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
    int cont;
    char numeri[100][100];
    printf("Numeri gia' esistenti nella rubrica originaria:\n");
    for (int i = 1; i <= lunghezza; i++)
    {
        if (i % 3 == 0)
        {
            strcpy(numeri[i-1], contenutoFile[i-1]);
            printf("%s\n", numeri[i - 1]);
            cont += 3;
        }
    }
    switch (scelta)
    {
        case 1:
            mostraRubrica(contenutoFile, lunghezza);
            break;
        case 2:
            if (argc == 2)
            {
                aggiuntaContattoSov(rubrica, contenutoFile, lunghezza, numeri);
            }
            else if(argc == 4)
            {
                aggiuntaContattoNF(rubrica, contenutoFile, lunghezza, numeri, argv[3]);
            }
            break;
        case 3: 
            eliminaContatto(contenutoFile, lunghezza, numeri, argv[1]);
            break;
        default:
            printf("Errore\n");
            break;
    }
    fclose(rubrica);
}