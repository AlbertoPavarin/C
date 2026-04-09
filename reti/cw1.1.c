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

int stringatoint(char *s){
    int tot = 0;
    for(int i = 0; ((s[i] <= '9') && (s[i] >= '0')); i++)
        tot = tot*10 + s[i] - '0';

    return tot;
}

int htoi(char *s){
    int tot = 0;
    for(int i = 0; s[i]; i++) {
        if (s[i]<='9' && s[i]>='0')
            tot = tot * (16) + (s[i]-'0');
        else if (s[i]<='f' && s[i]>='a')
            tot = tot * 16 + (s[i]-'a'+10);
        else if (s[i]<='F' && s[i]>='A')    
            tot = tot * 16 + (s[i]-'A'+10);
    }
    return tot;
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
    int csize = 0;
    //int bsize = 0;
    char *request = "GET / HTTP/1.1\r\n\r\n";
    char headerbuffer[10000];
    char chunkbuffer[6];
    char body[1000000];
    char *pchunksize = NULL;

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
    
    for (i = 0; h[i].name[0]; i++) {
        printf("%s: %s\n", h[i].name, h[i].value);
    }
   while (1) {
            for(int i = 0; read(s, chunkbuffer+i, 1); i++) {
                if (chunkbuffer[i] == '\n' && chunkbuffer[i-1] == '\r') {
                    chunkbuffer[i-1] = 0;
                    break;
            }
        }

        csize = htoi(chunkbuffer);
        
        if (csize == 0) break;       
        int letti = 0;
        while((t = read(s, body+counter, csize-letti))){
            counter += t;
            letti += t;
        }
        char padding[2];       
        read(s, padding, 2);
    }

    printf("%s\n", body);

    return 0;
}
