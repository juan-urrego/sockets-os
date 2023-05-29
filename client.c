#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>


int main() {
    char cadena[100];
    int sockfd;
    struct sockaddr_in servaddr;
    time_t t;
    struct tm *tm;
    char hora[100];
    char *tmp;
    char sendline[100] = "Usando el puerto 22000\n";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);

    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    printf("\n\n\t\t-----------Se inicio el chat-------\n\n");

    while(!strstr(cadena, "adios") && !strstr(sendline, "adios")) {
        bzero(cadena,100);
        t = time(NULL);
        tm = localtime(&t);
        strftime(hora,100, "\n yo (%H:%M) -> ", tm);
        printf("%s", hora);
        gets(sendline);
        tmp = strcat(hora, sendline);
        write(sockfd, sendline, strlen(sendline)+1);
        
        if (!strstr(cadena, "adios")) {
            strftime(hora,100, "\n otro usuario (%H:%M) -> ", tm);
            read(sockfd, cadena, 100);
            tmp = strcat(hora, cadena);
            printf("%s ", tmp);
        }
    }
    printf("\n\n Conversacion finalizada \n");
    return 0;
}