#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Uso: $ ./prg.out input.txt output.txt -c p\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if (input == NULL)
    {
        printf("File inesistente\n");
        return 1;
    }

    if (output == NULL)
    {
        printf("Errore\n");
        return 1;
    }

    while (fscanf() != EOF)
    {

    }
    fprintf(output, "Me");
    fclose(input);
    fclose(output);
    
}