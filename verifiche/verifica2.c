#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 15
// Alberto Pavarin

typedef struct
{
    char nome[MAX];
    char cognome[MAX];
    char ruolo[MAX];
} Calciatore_T;

int contaRighe(FILE *stream, char *nomeFile)
{   
    int righe = 1;
    if ((stream = fopen(nomeFile, "r")) == NULL)
    {
        printf("File inesistente\n");
        exit(1);
    }
    char str[1];
    while (fscanf(stream, "%c", str) != EOF)
    {
        if (strcmp(str, "\n") == 0)
            righe++;
    }
    fclose(stream);
    return righe;
}

void lettura(FILE *stream, Calciatore_T calciatori[], char *nomeFile)
{
    int lung = 0;
    if ((stream = fopen(nomeFile, "r")) == NULL)
    {
        printf("File inesistente\n");
        exit(2);
    }

    while (fscanf(stream, "%s %s %s", calciatori[lung].nome, calciatori[lung].cognome, calciatori[lung].ruolo) != EOF)
    {
        lung++;
    }
    
}

void mostraAttacanti(Calciatore_T calciatori[], int righe)
{
    for (int i = 0; i < righe; i++)
    {
        if (strcmp("Attaccante", calciatori[i].ruolo) == 0)
            printf("%s %s %s\n", calciatori[i].nome, calciatori[i].cognome, calciatori[i].ruolo);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Errore nei parametri\n");
        exit(0);
    }

    FILE *stream;
    int righe = contaRighe(stream, argv[1]);
    Calciatore_T calciatori[righe];
    lettura(stream, calciatori, argv[1]);
    int pid = fork();
    if (pid == 0)
    {
        mostraAttacanti(calciatori, righe);
        exit(3);
    }
    else
    {
        wait(&pid);
    }

    return 0;
}