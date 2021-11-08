// @file    vecchio.c
// @brief   file per determinare chi e' piu' vecchio
// @date    file creato il 08/11/2021

/**
*   @fn         Persona_T Inserisci()
*   @brief      funzione che permette di inserire le persone
*   @return     Persona_T: la funzione ritorna la persona inserita      
*   @fn         Persona_T Vecchio(Persona_T persone[])
*   @brief      funzione che ritorna il valore della persone piu' vecchia
*   @param      Persona_T persone[]: array delle persone inserite
*   @return     Persona_t: la funzione ritorna la persona piu' vecchia
*   @date       08/11/2021
*   @author     Alberto Pavarin
*   @file       vecchio.c
*/

#include <stdio.h>
#include <stdlib.h>

#define DIM 4

typedef struct // Struct per le persone
{
    char nome[100];
    char cognome[100];
    int eta;
} Persona_T;

Persona_T Inserisci() // Funzione per inserire una persona
{
    Persona_T persona;
    do
    {
        printf("Inserisci il nome della persona\n");
        scanf("%s", persona.nome);
    } while (persona.nome == ""); // Viene chiesto finche' esso non e' vuoto

    do
    {
        printf("Inserisci il cognome di %s\n", persona.nome);
        scanf("%s", persona.cognome);
    } while (persona.cognome == ""); // Viene chiesto il cognome finche' esso non e' vuoto

    do{
        printf("Inserisci l'eta' di %s\n", persona.nome);
        scanf("%i", &persona.eta);
    } while (persona.eta <= 0); // Viene chiesto l'eta' finche' essa non e' minore o uguale di 0
    printf("\n");
    return persona;
}

Persona_T Vecchio(Persona_T persone[]) // Funzione che ritorna la persona piu' vecchia
{
    int max = persone[0].eta; // Viene inizializzata la variabile max all'eta' della persona all'indice 0 dell'array persone
    Persona_T persVec;
    for (int i = 0; i < DIM; i++) // Viene iterato dentro l'array persone
    {
        if (persone[i].eta > max) // Se l'eta' di persone[i] e' maggiore dell'eta' massima attuale
        {
            max = persone[i].eta; // Viene settata la variabile max all'eta' della persona che ha indice pari ad i
            persVec = persone[i]; // Viene settata la variabile persVecchia, cioe' la persona piu' vecchia a persona con indice di i
        }
    }
    return persVec; // Viene ritornata la persona puu' vecchia
}

int main()
{
    Persona_T persone[DIM]; // Array per contenere le persone
    for (int i = 0; i < DIM; i++)
    {
        persone[i] = Inserisci(); // Viene chiamata la funzione Inserisci() per inserire le persone
    }
    for (int i = 0; i < DIM; i++)
    {
        printf("%s %s, %i\n", persone[i].nome, persone[i].cognome, persone[i].eta); // Vengono stampate tutte le persone con il loro nome, cognome e eta'
    }

    Persona_T vecchio = Vecchio(persone); // Viene chiamata la funzione Vecchio e il valore ritornata da essa viene salvata nella variabile vecchio
    printf("\n\nLa persona piu' vecchia e' %s %s con ben %i anni\n", vecchio.nome, vecchio.cognome, vecchio.eta); // Viene stampatala persona piu' vecchia
    return 0;
}   