#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#define MAX 80
#define PORT 8080
//#include "WTFclient.h"
//#include <openssl/sha.h>
//Global Variables
struct sockaddr_in cliaddr, servaddr;
struct addrinfo hints, *infoptr;
struct hostent * hp;
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}


void mySending(int sockfd, char* sending){
  sleep(10);
  char* sizer=malloc(100);
  sprintf(sizer,"%d",strlen(sending));
  printf("%s\n", sizer);
  write(sockfd,sizer,5);
  sleep(2);
  write(sockfd, sending, strlen(sending));
}

char* myRecieving(int sockfd){
  char* length=malloc(5);
  read(sockfd,length,5);
  int strLength= atoi(length);
  char* recieving=malloc(100);
  sleep(2);
  read(sockfd, recieving,strLength);
  return recieving;
}

int clienting( char * hostname) {
    /* code */

    int socketDescriptor;
    socketDescriptor=socket(AF_INET,SOCK_STREAM,0);
    if(socketDescriptor<0){
        printf("Error Level One: Unable to create Socket\n");
    }

    bzero(&cliaddr, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons( 9090 );
    hints.ai_family = AF_INET; // AF_INET means IPv4 only addresses

    hp = gethostbyname( hostname);
    if ( hp == NULL )
    {
        perror( "Unknown host" );
        return EXIT_FAILURE;
    }
    char * IPbuffer = inet_ntoa(*((struct in_addr*)hp->h_addr_list[0]));
    printf("Hostname: %s\n", IPbuffer);
    cliaddr.sin_addr.s_addr = inet_addr(IPbuffer);
    //int flags = fcntl(socketDescriptor, F_GETFL, 0);
  //  fcntl(socketDescriptor, F_SETFL, flags | O_NONBLOCK);

    printf("trying to connect\n");
    while(1){

      if (connect(socketDescriptor, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0){
        printf("Connection Failed \n");
        sleep(3);
     } else {

       return socketDescriptor;
     }
   }
    return -1;
}

int main(int argc, char *argv[]) {
//mySending(clienting(argv[1]),argv[2]);
printf("Socket descriptor: %d\n", clienting(argv[1]));

  return 0;
}
