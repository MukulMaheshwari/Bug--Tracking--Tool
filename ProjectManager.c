// client code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "login.h"
#include "replace.h"

#include <time.h>

#define IP_PROTOCOL 0 
#define IP_ADDRESS "127.0.0.1" // localhost 
#define PORT_NO 15050 
#define NET_BUF_SIZE 2048
#define cipherKey 'S' 
#define sendrecvflag 0 

// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
} 

// function for decryption 
char Cipher(char ch) 
{ 
	return ch ^ cipherKey; 
} 

// function to receive file 
int recvFile(char* buf, int s) 
{
	int i;
	char ch; 

	printf("\n");
	printf("Status   Bug ID   Bug Name   Date Reported   Created By   Assigned To\n");
	printf("---------------------------------------------------------------------\n");
	for (i = 0; i < s; i++) { 
		ch = buf[i]; 
		ch = Cipher(ch); 

		if (ch == EOF) 
			return 1; 
		else
			printf("%c",ch);
	} 
	
	return 0; 
} 

// driver code 
int main(int argc,char** argv) 
{ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
	char net_buf[NET_BUF_SIZE]; 
	FILE* fp;
	


	//user login	
	char *res=login();
	if(strlen(res)==6){ 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, 
					IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nConnection denied\n"); 
	else
	{
		sendto(sockfd, res, sizeof(res), 
			sendrecvflag, (struct sockaddr*)&addr_con, 
			addrlen);
	}
		
		
	if (strcmp(argv[1],"view")==0){
		strcpy(net_buf,"null");		 
		sendto(sockfd, net_buf, NET_BUF_SIZE, 
			sendrecvflag, (struct sockaddr*)&addr_con, 
			addrlen); 

		while (1) { 
			// receive 
			clearBuf(net_buf); 
			nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 
							sendrecvflag, (struct sockaddr*)&addr_con, 
							&addrlen); 

			// process 
			if (recvFile(net_buf, NET_BUF_SIZE)) {
					break; 
						}
					return 0;
					}
					}
	else
			{
                char var[100];
                char bugid[10],devId[10];	
                FILE* fp;
                FILE* fp2;
                int cur,len;
                char new_str[100];
                char* statusUpdate;
                char *result;
                printf("\nEnter bug id\n");
                scanf("%s",bugid);
                printf("\nEnter dev id\n");
                scanf("%s",devId);
                
                fp=fopen("bugs.txt","r+"); 
                FILE *file;
                file=fopen("temp1.txt","a");
                while(fgets(var, sizeof(var), fp)!=NULL)
                {
                len=strlen(var);
                if(strstr(var,bugid))
                                    {		
                                            strcpy(new_str,var);
                                            statusUpdate=str_replace("new", "assigned", new_str);
                                            result=str_replace("null", devId, statusUpdate);
                                            //printf("%s",result);

                                            fprintf(file,"%s",result);

                                        }
                    else
                        {
                            fprintf(file,"%s",var);
                        }						
                }
                fclose(file);
                fclose(fp);


                remove("bugs.txt");

                /* Rename temp file as original file */
                rename("temp1.txt", "bugs.txt");
			}
	}
	else{
		printf("Invalid credentials");
		}
		return 0; 
} 

