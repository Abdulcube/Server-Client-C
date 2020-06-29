#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
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
#include <ifaddrs.h>
#include <ctype.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
struct sockaddr_in cliaddr, servaddr;
struct addrinfo hints, *infoptr;
struct hostent * hp;

char* portName;

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
  char* sizer=malloc(100);
  sprintf(sizer,"%lu",strlen(sending));
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

int serverImplementer(int wow) {
    int socketDescriptor;
    int bindFail;
    socklen_t addrlen;
    socketDescriptor=socket(AF_INET,SOCK_STREAM,0);
    if(socketDescriptor<0){
        printf("Error Level One: Unable to create Socket\n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons( 9090 );
    addrlen = sizeof(servaddr);
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEPORT , &servaddr, sizeof(servaddr))){
        printf("Error Level Two: Unable to set the socket to reusable\n");
    }
      //int flags = fcntl(socketDescriptor, F_GETFL, 0);
     //fcntl(socketDescriptor, F_SETFL, flags | O_NONBLOCK);

    bindFail=bind(socketDescriptor, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(bindFail<0){
        printf("Error Level Three: Unable to bind address to server\n");
    }

    listen(socketDescriptor, 20);
    int new_socket;
    printf("yuh");
    while (1) {
        printf("yuh2");
        new_socket=accept(socketDescriptor,(struct sockaddr*)&servaddr,&addrlen);
        if (new_socket < 0) {

            printf("server acccept failed...\n");
            sleep(3);
            //exit(0);
        } else{
            printf("server acccept the client...\n");
            return new_socket;
        }
        // Function for chatting between client and server

    }
    return 0;
}



int main(int argc, char const *argv[]) {

  //printf("%s\n",myRecieving(serverImplementer()));
  printf("Socket descriptor: %d\n", serverImplementer(0));
  return 0;
}
