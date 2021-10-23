#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int contatore = 0;
    char *indicatore = "";
    if (argc != 5 || strcmp(argv[3], "-c") != 0 && strcmp(argv[3], "-p") != 0)
    {
        printf("Uso: $ ./prg.out input.txt output.txt modalita'(-c, -p) cosa cercare\n\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if (input == NULL)
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
    stat(argv[1], &sb);
    char *contenutoFile = malloc(sb.st_size);
    char ch[sb.st_size];
    if (contenutoFile == NULL)
    {
        printf("Error\n\n");
        return 1;
    }

    while (fscanf(input, "%s", contenutoFile) != EOF)
    {
        if (strcmp(argv[3], "-c") == 0)
        {
            if (strlen(argv[4]) == 1)
            {
                for (int i = 0; i < sb.st_size; i++)
                {
                    sprintf(ch ,"%c", contenutoFile[i]);
                    if (strcmp(ch, argv[4]) == 0)                             
                        contatore++;
                }
            }
            else
            {
                printf("Errore, inserisci un solo carattere\n\n");
                return 1;
            }
            indicatore = "Il carattere";
        }
        else if (strcmp(argv[3], "-p") == 0)
        {
            if (strlen(argv[4]) > 1)
            {
                if (strcmp(contenutoFile, argv[4]) == 0)           
                    contatore++;
            }        
            else
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
    free(contenutoFile);
    return 0;
}