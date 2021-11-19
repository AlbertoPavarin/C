/// @file       es4_libro.c
/// @brief      file dell'esercizio 4 del libro
/// @date       19/11/2021
/// @author     Alberto Pavarin

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

/// @param MAX: lunghezza massima del nome e del cognome
#define MAX 15

/**
* @brief    struct Persona_T: struct formata da un nome e un cognome
* @param    char nome[MAX]: nome della persona
* @param    char cognome[MAX]: cognome della persona
*/
typedef struct
{
    char nome[MAX];
    char cognome[MAX];
} Persona_T;

/**
* @fn       void capitalize(char stringa[MAX])
* @brief    funzione che permette di trasformare la prima lettara in maiuscolo e tutte le altre in minuscolo
* @param    char stringa[MAX]: stringa da convertire
*/
void capitalize(char stringa[MAX])
{
    for (int i = 0; i < strlen(stringa); i++)
    {
        if (i == 0)
        {
            stringa[i] = toupper(stringa[i]);
        }
        else
        {
            stringa[i] = tolower(stringa[i]);
        }
    }
}

/**
* @fn       void upper(char stringa[MAX])
* @brief    funzione che permette di convertite tutta la stringa in maiuscolo
* @param    char stringa[MAX]: stringa da convertire
*/
void upper(char stringa[MAX])
{
    for (int i = 0; i < strlen(stringa); i++)
    {
        stringa[i] = toupper(stringa[i]);
    }
}

/**
* @fn       int main(int argc, char *argv[])
* @brief    funzione principale, istanzia un processo figlio e il padre permette di leggere un nome ed un cognome, che verranno poi convertiti con la funzione capitalize e scritti in un file. Il file verra' poi eliminato. Il figlio contemporaneamente legge quello che c'e' dentro il file e lo stampa a schermo, solo dopo aver convertito il nome e il cognome usando la funzione upper
* @param    int argc: contatore degli argomenti inseriti da riga di comando. dovranno essere 2, il nome del programma e il nome del file da creare (es: ./a.out input.txt)
* @param    char *argv[]: contiene tutti gli argomenti passati da riga di comando (argv[0] == a.out, argv[1] == input.txt)
*/
int main(int argc, char *argv[])
{
    int pid;
    Persona_T persona;
    if (argc != 2)
    {
        printf("Errore negli argomenti\n");
        exit(0);
    }

    FILE *stream = fopen(argv[1], "w+");
    if (stream == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(1);
    }

    pid = fork();
    if (pid == 0)
    {
        sleep(5);
        rewind(stream);
        fscanf(stream, "%s %s", persona.nome, persona.cognome);
        upper(persona.nome);
        upper(persona.cognome);
        printf("\n%s %s\n", persona.nome, persona.cognome);
        exit(2);
    }
    else
    {
        printf("Inserisci il nome della persona\n");
        scanf("%s", persona.nome);

        printf("Inserisci il cognome della persona\n");
        scanf("%s", persona.cognome);

        capitalize(persona.nome);
        capitalize(persona.cognome);

        fprintf(stream, "%s %s", persona.nome, persona.cognome);
        fclose(stream);
        remove(argv[1]);
        wait(&pid);
        return 0;
    }
}