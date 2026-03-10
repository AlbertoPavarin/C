#include <stdio.h>
#include <stdlib.h>

short int endian();
short int network_order(short int);

int main(){
    printf("Il numero 1 in network order vista l'architettura del pc è: %d\n", network_order(1)); 
    return 0;
}

short int endian() {
    short int nmb = 1;
    char *pc = (char *) &nmb;
  
    if (*pc == 1) 
        return 1;
    else
        return 0;
}

short int network_order(short int x){
    if (endian() == 0)
        return x;
   
    char *pc = (char *) &x;
    char tmp = *pc;
    *pc = *(pc+1);
    *(pc+1) = tmp;

    return x;
}
