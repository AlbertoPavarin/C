#include <stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>

struct sockaddr_in  server;

short int girashort (short int a){
	short int b = 1;
	char *p = (char*) &b;
    //printf("girashort %x\n",a);
    // printf("girashort %x\n",a<<8 &0xffff);
    // printf("girashort %x\n",(a>>8 & 0x00ff));
	if(*p) return (a<<8&0xffff) + (a>>8 & 0x00ff);
	return a;
}
struct header{ 
        char * n; 
        char * v;
        } h[100];

char hbuf[10000];
char entitybody[1000000];
int t,counter;

int sonouguali ( char * s1, char * s2 )
{
    int i = 0; 
    do if (s1[i] != s2[i]) return 0; while ((s1[i++]!=0)) ;
    return 1; 
}

int stringaintero ( char * s){
int tot=0;
for(int i =0; (s[i]>='0') && (s[i]<='9'); i++)
    tot = tot * 10 + s[i]-'0' ; 
return tot;
}

int main()
{
char response[5000];
FILE * f;
struct sockaddr_in client;
char primiDuePunti;
int i,j,lunghezza,lungh;
int s,s2 ;
int yes = 1;
int n;
unsigned char * p;
unsigned char * method, *url, *ver;
int x;
char * rl; // request_line
unsigned char req[1000000];
char * resp_500="HTTP/1.1 500 Internal Server Error\r\nContent-Length:39\r\n\r\n<html><H1>Torno Subito!</H1><br></html>";
char * resp_404="HTTP/1.1 404 File not found\r\n\r\n";
char * resp_200="HTTP/1.1 200 OK \r\nConnection: close\r\n\r\n";
if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket Fallita");
    return 0;
   }
t= setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
if (t==-1){perror("setsockopt Failed"); return 1;}
server.sin_family=AF_INET;
server.sin_port=girashort(8025);
server.sin_addr.s_addr=0;


if( -1 == bind(s, (struct sockaddr *) &server, sizeof(struct sockaddr_in))){
    perror("Bind Fallita");
    return 0;
}

if (-1 == listen(s, 5)){
    perror("Listen Fallita");
    return 0;
}
while (1){
    lunghezza = sizeof(struct sockaddr_in);
    if( -1 == (s2 = accept(s,(struct sockaddr *) &client, &lunghezza))){
         perror("Accept fallita");
         return 0;
    }

// h[0].n = hbuf+1;
// hbuf[0]=0;
// primiDuePunti=0;
// for (j=0,i=1; read(s2,hbuf+i,1);i++){
//    if (hbuf[i]==':' && !primiDuePunti){
//       hbuf[i]='\0';
//       h[j].v=hbuf+i+1;
//       primiDuePunti=1;
//    }
//    if (hbuf[i]=='\n' && hbuf[i-1]=='\r') {
//        hbuf[i-1]=0;
//        if(!h[j].n[0]) break;
//        h[++j].n=hbuf+i+1;
//        primiDuePunti=0;
//     }
// }

// lungh = 0;
// for(i=0;h[i].n[0];i++){
//     if(sonouguali(h[i].n,"Content-Length")){
//         lunghezza = stringaintero(h[i].v+1);
//         printf("lunghezza = %d\n", lunghezza);
//     }
//     printf("%s ---> %s\n",h[i].n,h[i].v);
// }
h[0].n = hbuf;
char separator = 0;
for (i = 0; read(s2, hbuf+i, 1); i++) {
        if (hbuf[i] == ':' && !separator){
            separator = 1;
            hbuf[i] = 0;
            h[j].v = hbuf+i+1;
        if (hbuf[i] == '\n' && hbuf[i-1] == '\r'){
            hbuf[i-1] = 0;
            if (h[j].n[0] == 0) break;
                j++;
                h[j].n = hbuf+i+1;
                separator = 0;
        }
}   
for (i = 0; h[i].n[0]; i++) {
       if(sonouguali(h[i].n,"Content-Length"))
           lunghezza = stringaintero(h[i].v+1);
           printf("%s: %s\n", h[i].n, h[i].v);
}

for(counter=0; t = read(s2,entitybody+counter,lungh-counter); counter+=t);
entitybody[counter]=0;
printf("Entity body : %d\n",counter );
printf("%s\n",entitybody);

int rlcnt = 0;
rl = h[0].n;
method = rl;
for (rlcnt = 0; rl[rlcnt] != ' '; rlcnt++); 
rl[rlcnt++] = 0;
url = rl+rlcnt;
for (;rl[rlcnt] != ' '; rlcnt++); 
rl[rlcnt++] = 0;
ver = rl+rlcnt;
for (;rl[rlcnt] != ':'; rlcnt++); 
rl[rlcnt++] = 0;

printf("method = %s, url=%s, ver =%s\n",method, url,ver);
if(0==strncmp(url,"/cgi/",5)){
    char cmd[200];
    sprintf(cmd, "%s > tmp\n",url+5);
    sprintf(url,"/tmp");    
    printf("Il comando è %s",cmd); 
    system(cmd);    
}
f = fopen(url+1, "r");
if (f==NULL){
    write(s2,resp_404,strlen(resp_404)); //Status line
    } else {
    write(s2,resp_200,strlen(resp_200));
    do {
        n= fread(response,1,5000,f); 
        write(s2,response,n);  
    }while ( n == 5000 );
    }
close(s2);
}
}