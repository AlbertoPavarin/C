#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

void ToUpper(char *stringa)
{
    for (int i = 0; i < strlen(stringa); i++)
    {
        stringa[i] = toupper(stringa[i]); // Ogni carattere della stringa passata come parametro viene convertita in maiuscolo grazie alla funzione toupper()
    }  
    printf("La stringa inserita in maiuscolo e' %s\n", stringa);
}

int main(int argc, char *argv[])
{
    int pid;
    if (argc != 2) // Se gli argomenti inseriti non sono uguali a 2 allora il programma termina con un errore 
    {
        printf("Errore nei parametri\n");
        exit(0);
    }

    char *str = argv[1];
    pid = fork(); // Viene creato un proceso figlio
    if (pid == 0) // se il pid == 0, questo pezzo di codice sara' eseguito dal figlio
    {
        ToUpper(str);
        exit(2);
    }
    else
    {
        wait(&pid);
    }
   return 0;
}