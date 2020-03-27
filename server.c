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

int main()
{
int  port;
  int sockfd,newsockfd;
  int clilen;
  int n;
  char buffer[BUFLEN];
  struct sockaddr_in servaddr,cliaddr;
  char receiveMessage[200];
  char message[200];  
  printf("\nspecify "RED"port"RESET" to listen\n"GRN "\nlet's go:"RESET);
  scanf("%d",&port);

  //Создаем сокет
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
  {
      perror("socket");
      exit(1);
  }
  
  //Заполняем структуру
  servaddr.sin_family= AF_INET;
  servaddr.sin_port=htons(port);
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //Принимаем соединения с любого адреса

  //Биндим сокет к адресу
  if(bind(sockfd, (struct sockaddr *) &servaddr, 
  sizeof(servaddr)) < 0){
      perror("bind");
      close(sockfd);
      exit(1);
  }
  //Переводим сокет в слушающее состояние
  if(listen(sockfd, 5) < 0){
      perror("listen");
      close(sockfd);
      exit(1);
  }
  
  //Принимаем соединение
  
  //clilen=sizeof(cliaddr);
  //if((newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clilen))<0)
  //{
  //    perror("accept");
  //    close(sockfd);
  //    exit(1);
  //}
  
  printf("Client %s connected\n",inet_ntoa(cliaddr.sin_addr));
      
  //while((n = read(newsockfd,buffer,BUFLEN-1))>0)
  while (1)
  {
      newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
    //  Отправляем обратно принятые данные
    //   if((n=write(newsockfd,buffer,strlen(buffer)+1))<0)
    //   {
        //   perror("write");
        //   close(sockfd);
        //   close(newsockfd);
        //   exit(1);
    //   }
    fgets(message, 100, stdin);
    send(sockfd, message, LENGTH_MSG, 0);
    int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);
        if (receive > 0) {
            printf("\r%s\n", receive);
        }

  }
  
  //if(n < 0) //При чтении произошла ошибка
  //{
  //    perror("read");
  //    close(sockfd);
  //    close(newsockfd);
  //    exit(1);
  //}
  //    
  //close(newsockfd);
  //close(sockfd);
  //return 0;    
}

