#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define BUFLEN 1024
#define LENGTH_MSG 200
#define LENGTH_SEND 200
/// COLOR
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m" // example  printf("This is " RED "red" RESET " and this is " BLU "blue" RESET "\n");

struct addrinfo hints, *infoptr; 


int main() {
    char receiveMessage[200];
char message[200];  
    char str1[50];
    int  port;
    
    printf("\n""input "RED "DDNS"RESET " or "RED "ipv4"RESET "(example 255.255.255.255)\n"GRN "let's go:"RESET);
    scanf("%s",&str1);
    printf("\ninput "RED"PORT"RESET GRN "\nlet's go:"RESET);
    scanf("%d",&port);
    printf("\033[0m;");   
    hints.ai_family = AF_INET; 
    int result = getaddrinfo(str1, NULL, &hints, &infoptr);
    if (result) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        exit(1);
    }

    struct addrinfo *p;
    char host[256];

    for (p = infoptr; p != NULL; p = p->ai_next) {

        getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof (host), NULL, 0, NI_NUMERICHOST);
    }

    puts(host);
    freeaddrinfo(infoptr);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int sockfd;
int num;
char buffer[BUFLEN];
struct sockaddr_in servaddr;
    
//Обнуляем буффер
bzero(buffer,BUFLEN);

//Создаем сокет
if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
{
    perror("socket");
    exit(1);
}

//Заполняем структуру sockaddr
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(port);
inet_aton(host, &servaddr.sin_addr);

//Пытаемся приконнектится
if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
{
    perror("connect");
    close(sockfd);
    exit(1);
}

while (1)
{
fgets(message, 100, stdin);
send(sockfd, message, LENGTH_MSG, 0);
int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);
    if (receive > 0) {
        printf("\r%s\n", receive);
    }
}
//Запрашиваем строку у пользователя и посылаем ее серверу
// fgets(buffer,BUFLEN,stdin);
// if((num=write(sockfd,buffer,strlen(buffer)+1))<0)
// {
    // perror("write");
    // close(sockfd);
    // exit(1);
// }
//Получаем и печатаем ответ
// if((num=read(sockfd,buffer,BUFLEN-1))<0)
// {
    // perror("Can\'t read\n");
    // close(sockfd);
    // exit(1);
// }
// printf("%s",buffer);
    
//Закрываем соединение
//close(sockfd);
//return 0;

    

}
