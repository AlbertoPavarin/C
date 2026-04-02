#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

struct sockaddr_in server;

struct header {
    char *name;
    char *value;
} h[100]; 

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
    int t, counter = 0;
    int j = 0;
    int i = 0;
    char *request = "GET / HTTP/1.0\r\n\r\n";
    char headerbuffer[10000];
    char response[1000000];
    
    server.sin_family = AF_INET;
    server.sin_port = network_order(80);
    server.sin_addr.s_addr = addr;
       
    if (connect(s, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) == -1) { 
        perror("Errore nella connessione della socket\n");
        return -1;
    }

    printf("Socket connessa\n");
    write(s, request, strlen(request));
    
    h[0].name = headerbuffer;
    int separator = 0;
    for (i = 0; read(s, headerbuffer+i, 1); i++) {
       if (headerbuffer[i] == ':' && !separator){
           separator = 1;
           headerbuffer[i] = 0;
           h[j].value = headerbuffer+i+1;
        }

        if (headerbuffer[i] == '\n' && headerbuffer[i-1] == '\r'){
            headerbuffer[i-1] = 0;
            if (h[j].name[0] == 0) break;
            j++;
            h[j].name = headerbuffer+i+1;
            separator = 0;
        }
    }
    
    for (i = 0; h[i].name[0]; i++)
    {
        printf("%s: %s\n", h[i].name, h[i].value);
    }

    while((t = read(s, response+counter, 100000-counter))) {
        counter += t;
    }

    response[1000] = 0;
    printf("%s\n", response);

    return 0;
}
