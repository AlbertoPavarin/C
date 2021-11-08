#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int contatore = 0;
    char *indicatore = "";
    if (argc != 5 || strcmp(argv[3], "-c") != 0 && strcmp(argv[3], "-p") != 0) // Viene controllato se i parametri d'ingresso sono 5 e sono validi
    {
        printf("Uso: $ ./prg.out input.txt output.txt modalita'(-c, -p) cosa cercare\n\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r"); // viene aperto il file che e' stato passato come file di input (argv[1]) in modalita' di lettura
    FILE *output = fopen(argv[2], "w"); // viene aperto il file che e' stato passato come file di output (argv[2]) in modalita' di scritture
    if (input == NULL) // Se il file di input non esiste il programma termina con un messaggio di errore
    {
        printf("File inesistente\n\n");
        return 1;
    }

    if (output == NULL)
    {
        printf("Errore\n\n");
        return 1;
    }

    struct stat sb;
    stat(argv[1], &sb); // prende le informazioni del file di input come ad esempio la grandezza del file in bytes
    char *contenutoFile = malloc(sb.st_size); // Viene allocata la memoria della dimenzione del file di input per memorizzare il flusso di lettura 
    char ch[sb.st_size];
    if (contenutoFile == NULL) // Se non riesce ad allocare il programma termina con un messaggio di errore
    {
        printf("Error\n\n");
        return 1;
    }

    while (fscanf(input, "%s", contenutoFile) != EOF) // Finche' il file di input non finisce
    {
        if (strcmp(argv[3], "-c") == 0) // Se l'elemento da cercare e' un char, modalita' definita in argv[3]
        {
            if (strlen(argv[4]) == 1) // Se la lunghezza dell'elemento da cercare e' uguale ad 1 quindi e' un carattere
            {
                for (int i = 0; i < sb.st_size; i++)
                {
                    sprintf(ch ,"%c", contenutoFile[i]); // Viene convertito in stringa il valore di contenutoFile[i]
                    if (strcmp(ch, argv[4]) == 0) // Se il carattere letto e' uguale al carattere da cercare, allora viene aumentato la variabile contatore,
                        contatore++;              // cioe' la variabile che tiene conto di quanti caratteri ugualiu sono stati trovati
                }
            }
            else // Se la lunghezza dall'elemento e' diverso da 1 allora il programma termina con un messaggio d'errore
            {
                printf("Errore, inserisci un solo carattere\n\n");
                return 1;
            }
            indicatore = "Il carattere";
        }
        else if (strcmp(argv[3], "-p") == 0) // Se l'elemento da cercare e' una stringa, modalita' definita in argv[3]
        {
            if (strlen(argv[4]) > 1) // Se la lunghezza dell'elemento da cercare e' maggiore di uno, quindi e' una stringa
            {
                if (strcmp(contenutoFile, argv[4]) == 0) // Se la stringa letta e' uguale alla stringa da cercare, allora viene aumentata la variabile contatore
                    contatore++;
            }        
            else // Se la lunghezza di cio' che bisogna cercare e' minore di 1 allora il programma termina con un messaggio d'errore
            {
                printf("Errore inserisci una stringa\n\n");
                return 1;
            }
            indicatore = "La stringa";           
        }
    }

    fprintf(output, "%s %s compare: %d volte", indicatore, argv[4], contatore);
    printf("Valore salvato nel file %s\n\n", argv[2]);
    fclose(input);
    fclose(output);
    free(contenutoFile); // Viene liberata la memoria allocata
    return 0;
}