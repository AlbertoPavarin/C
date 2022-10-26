#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define DIM 512
#define SERVERPORT 1313


int main()
{
    struct sockaddr_in servizio, addr_remoto;// record con i dati del server e del client
    int socketfd, soa, fromlen=sizeof(servizio);
    char str[DIM];
    // definizione dei dati del socket 
    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT);
    // impostazione del transport endpoint del server
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    // leghiamo l'indirizzo al transport endpoint
    bind(socketfd,(struct sockaddr*)&servizio,sizeof(servizio));
    // poniamo il server in ascolto delle richieste dei client 
    listen(socketfd,10);// può attendere fino a 10 client
    // ciclo infinito
    while (1)
    {
        printf("\n\nServer in ascolto...");

        fflush(stdout); // pulisce buffer comunicazione

        soa=accept(socketfd,(struct sockaddr*)&addr_remoto,&fromlen);
        // Legge dal client
        read(soa,str,sizeof(str));
        for (int i = 0; i < strlen(str); i++)
        {
            str[i] = toupper(str[i]);
        }
        
        printf("Stringa ricevuta: %s\n",str);

        write(soa, str, sizeof(str));
        
        close(soa);

     }
      
   return 0;
    
}