#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

char *login()
{
char id[20];
char login[40];
char* pass;
int flag=0;
printf("Enter username: ");
scanf("%s",id);
char* user_id=id;
pass=getpass("Enter password: ");
strcpy(login,id);
strcat(login,"-");
strcat(login,pass);
strcat(login,"\n");
//printf("%s",login);

  FILE *file;

  file= fopen ( "Credentials.txt", "r" );

  if (file != NULL) {
    char line [1000];
    while(fgets(line,sizeof line,file)!= NULL && flag!=1) {
        if(strcmp(login,line)==0) flag=1; 
        else  flag=0;
    } 
    fclose(file);	
    if(flag==1) return user_id;
    else return "f";
  }
  else {
    perror("Invalid");
  }
}