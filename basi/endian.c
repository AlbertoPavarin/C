#include <stdio.h>
#include <stdlib.h>

int main(){
    short int nmb = 1;
    void *p = &nmb;
    char *pc = p;

    printf("Numero: %d\n", nmb);
    printf("Indirizzo p: %p\n",(void*)p);		
    printf("Numero pc: %d\n",*pc);	
	
    if (*pc == 1)
        printf("La convenzione utilizzata è Little Endian\n");
    else
        printf("La convenzione utilizzata è Big Endian\n");

	return 0;
}
