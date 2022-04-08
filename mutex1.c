#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TANTI1 30
#define TANTI2 20
int condivisa = 0;
pthread_mutex_t mutex;

void *cod_thread(void *arg)
{
    int x, dato;
    for (x = 0; x < TANTI1; x++)
    {
        pthread_mutex_lock(&mutex);
        dato = condivisa;
        dato++;
        condivisa = dato;
        printf(".");
        fflush(stdout);
        pthread_mutex_unlock(&mutex);
    }
}

int main(void)
{
    pthread_t tid1;
    int x, err;
    pthread_mutex_init(&mutex, NULL);
    if ((err = pthread_create(&tid1, NULL, cod_thread, NULL)) != 0)
    {
        printf("Errore nella creazione del thread %s\n", strerror(err));
        exit(1);
    }

    for (x = 0; x < TANTI2; x++)
    {
        pthread_mutex_lock(&mutex);
        condivisa++;
        printf("o");
        fflush(stdout);
        pthread_mutex_unlock(&mutex);
    }

    if (pthread_join(tid1, NULL))       
    {
        printf("errore: %s\n", strerror(err));
        exit(1);
    }
    printf("\nVariabile condivisa uguale a: %d\n", condivisa);
    exit(0);
}