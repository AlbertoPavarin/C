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

short int network_order(short int x) {
    if (endian() == 0)
        return x;
   
    char *pc = (char *) &x;
    char tmp = *pc;
    *pc = *(pc+1);
    *(pc+1) = tmp;

    return x;
}

int stringatoint(char *s) {
    int tot = 0;
    for(int i = 0; ((s[i] <= '9') && (s[i] >= '0')); i++)
        tot = tot*10 + s[i] - '0';

    return tot;
}

int htoi(char *s) {
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

int sonouguali(char *s1, char *s2) {
    for(int i = 0; s1[i] != 0 || s2[i] != 0; i++){
        if (s1[i] != s2[i]) return 0;
    }

    return 1;
}

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        printf("Errore nella creazione della socket\n");
        return -1;
   }
    
    int s2 = 0;
    int t, counter = 0;
    int j = 0;
    int i = 0;
    int n = 0;
    int rlcnt = 0;
    int yes = 1;
    int csize = 0;
    char fixed = 0;
    int contentlenght = 0;
    char headerbuffer[10000];
    int lunghezza;
    char chunkbuffer[6];
    char body[1000000];
    char fcontent[5000];
    char *pchunksize = NULL;
    struct sockaddr_in remote;
    int remotesz = sizeof(remote);
    FILE * f = NULL;
    int opt = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (opt == -1)
        perror("Set option failed\n"); 

    server.sin_family = AF_INET;
    server.sin_port = network_order(80);
    server.sin_addr.s_addr = 0;
       
    if (bind(s, (struct sockaddr*)&server, sizeof(server)) == -1){
        perror("Errore binding");
        return -1; 
    }
    if (listen(s, 5) == -1){
       perror("Errore listen");
       return -1;
    }

    while (1) {
        if ((s2 = accept(s, (struct sockaddr*)&remote, (socklen_t *)&remotesz)) == -1){
           perror("Errore accept");
           return -1;
        }
        
        h[0].name = headerbuffer;
        char separator = 0;
        for (i = 0; read(s2, headerbuffer+i, 1); i++) {
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
           if(sonouguali(h[i].name,"Content-Length"))
               lunghezza = stringatoint(h[i].value+1);
               printf("%s: %s\n", h[i].name, h[i].value);
        }
        char * rl = h[0].name;
        char * method = rl;
        for (rlcnt = 0; rl[rlcnt] != ' '; rlcnt++); 
        rl[rlcnt++] = 0;
        char * url = rl+rlcnt;
        for (;rl[rlcnt] != ' '; rlcnt++); 
        rl[rlcnt++] = 0;
        char * version = rl+rlcnt;
        for (;rl[rlcnt] != ':'; rlcnt++); 
        rl[rlcnt++] = 0;

        printf("Richiesta: %s %s %s\n", method, url, version);
        char * response_200 = "HTTP/1.1 200 OK\r\n\r\n";
        char * response_404 = "HTTP/1.1 404 File not found\r\n\r\n";
        char * response_500 = "HTTP/1.1 500 Internal Server Error\r\n\r\n";

        f = fopen(url+1, "r");
        if (f == NULL)
            write(s2, response_404, strlen(response_404));
        else {
            write(s2, response_200, strlen(response_200));
            do {
                n = fread(fcontent, 1, 5000, f);
            } while (n == 5000);
            write(s2, fcontent, n);
        }
        // if (!fixed) {
        //     while (1) {
        //     for(int i = 0; read(s, chunkbuffer+i, 1); i++) {
        //         if (chunkbuffer[i] == '\n' && chunkbuffer[i-1] == '\r') {
        //             chunkbuffer[i-1] = 0;
        //             break;
        //         }
        //     }
        //     csize = htoi(chunkbuffer);
    
        //     if (csize == 0) break;       
        //     int bread = 0;
        //     while((t = read(s, body+counter, csize-bread))){
        //         counter += t;
        //         bread += t;
        //     }
           
        //     read(s, chunkbuffer, 2);
        //     }
        // } else {
        //     for(counter = 0; (t = read(s, body+counter, contentlenght-counter)); counter+=t); 
        // }
        close(s2);  
    }
    return 0;
}
