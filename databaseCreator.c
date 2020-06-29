#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

char* pathName(char* diry, char* fileName){
  char* name=malloc(100);
  DIR *dirp;
	dirp=opendir(diry);
	if(dirp==NULL){
		//printf("Not a directory: %s\n", diry);
		return NULL;
  }

  	struct dirent *dp;
  	while ((dp= readdir(dirp)) !=NULL) {
  		struct stat path_stat;
  		stat(dp->d_name, &path_stat);

      if((strcmp(dp->d_name, fileName)==0)){

          strcpy(name,diry);
          strcat(name, "/");
          strcat(name,dp->d_name);
          return name;
      }
		  if(S_ISDIR(path_stat.st_mode)==1){

			if( (strcmp(dp->d_name, ".")) == 0 || (strcmp(dp->d_name, "..")) == 0) {

  			} else {
             strcpy(name,diry);
             strcat(name, "/");
             strcat(name,dp->d_name);


             if (pathName(name,fileName)!=NULL){
               return pathName(name,fileName);
             }
  			}
  		}
  }
  return NULL;
}

void searchNumber(char* phoneNumber) {
  char * ticketContents= malloc(1000);
  char * pathington = pathName(".", phoneNumber);
  FILE * fp;
  printf("Pathington: '%s'\n", pathington);
  fp = fopen(pathington,"r");
  if(fp == NULL){
        printf("Unable to open or create configure File!\n");
      }
  char c;
  int counter = 0;
  if (fp) {
    while ((c = getc(fp)) != EOF){
      counter ++;
      putchar(c);
    }
  }
  printf("%d\n", counter);
}

int createTicket() {
  char* ticketString = malloc(1000);

  char* phoneNumber = malloc (11);
  printf("Enter phone number:\n");
  scanf("%s", phoneNumber);

  char* email = malloc (40);
  printf("Enter Email:\n");
  scanf("%s", email);

  char* type = malloc (20);
  printf("Enter Type:\n");
  scanf("%s", type);

  char* subject = malloc (60);
  char* subjectWords = malloc (45);
  int subjectCounter;
  printf("Enter Subject in a sentence:\n");
  for(subjectCounter = 0; subjectCounter <=300 ; subjectCounter++){
    scanf("%s", subjectWords);


    if(subjectWords[strlen(subjectWords)-1] == '.'){
      strcat(subject,subjectWords);
      break;
    }

    strcat(subject,subjectWords);
    strcat(subject," ");
  }


  int numOfSentences = 0;
  printf("Enter description (in 3 sentences):\n");
  char* description = malloc (300);
  char* words = malloc(45);
  int counter;
  for(counter = 0; counter <=300 ; counter++){
    scanf("%s", words);

    if(words[strlen(words)-1] == '.'){
      numOfSentences++;
      if (numOfSentences>=3) {
        strcat(description,words);
        break;
      }
    }

    strcat(description,words);
    strcat(description," ");
  }



  sprintf(ticketString,"%s\n%s\n%s\n%s\n%s\n", phoneNumber, email, type, subject, description);


  FILE * fp;
  fp = fopen(phoneNumber,"w");
      if(fp == NULL){
        printf("Unable to open or create configure File!\n");
      }
      fprintf(fp,"%s",ticketString);

  return 0;
}

int main(int argc, char *argv[]) {

  if(argv[1]==NULL){
    printf("\nInsufficient Number of Arguments, Shutting Down...\n\n");
    exit(0);
  }

  if(strcmp(argv[1], "create") == 0){
    createTicket();
    return 0;
  }

  if(strcmp(argv[1],"search") == 0){
    searchNumber(argv[2]);
    return 0;
  }

  if(strcmp(argv[1], "order") == 0){
  //  createOrder();
    return 0;
  }

  printf("Fall through error!\n");
  return 0;
}
