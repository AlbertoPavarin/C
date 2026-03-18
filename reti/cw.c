#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>

struct sockaddr_in server;

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

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        printf("Errore nella creazione della socket\n");
        return -1;
   }
    
    int addr = 0; // 142.251.140.110
    unsigned char *p = (unsigned char *)&addr;
    p[0]=142; p[1]=251; p[2]=140; p[3]=110;
  

    server.sin_family = AF_INET;
    server.sin_port = network_order(80);
    server.sin_addr.s_addr = addr;
       
    if (connect(s, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) == -1) { 
        printf("Errore nella connessione della socket\n");
        perror("asd");
        return -1;
    }

    printf("Socket connessa\n");
    return 0;
}
