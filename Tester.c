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

				char bugName[20];
				int bugIdSequence;
				char bugIdSequenceStirng[20];
				char bugId[4];
				char reportingDate[30];
				char reportingTesterId[10];
				char assignedToDeveloperId[]="null";
				char bugStatus[]="new";


				printf("\nPlease enter bug details:\n"); 
				scanf("%s", bugName); 

				//creating bug info stroing format
				strcpy(net_buf,bugStatus);
				strcat(net_buf,"      ");

				srand((unsigned int)time(NULL));

				strcpy(bugId,"B");
				bugIdSequence=rand()%900+100;
				sprintf(bugIdSequenceStirng, "%d", bugIdSequence);
				strcat(bugId,bugIdSequenceStirng);

				strcat(net_buf,bugId);
				strcat(net_buf,"      ");
				
				strcat(net_buf,bugName);
				strcat(net_buf,"      ");

				//getting current date
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				char yearString[10];
				char monthString[10];
				char dayString[10];
				sprintf(dayString, "%d", tm.tm_mday);
				strcpy(reportingDate,dayString);
				strcat(reportingDate,"/");
				sprintf(monthString, "%d", tm.tm_mon + 1);
				strcat(reportingDate,monthString);
				strcat(reportingDate,"/");
				sprintf(yearString, "%d", tm.tm_year + 1900);
				strcat(reportingDate,yearString);
				strcat(net_buf,reportingDate);
				strcat(net_buf,"      ");

				strcpy(reportingTesterId,res);
				strcat(net_buf,reportingTesterId);
				strcat(net_buf,"      ");
				
				strcat(net_buf,assignedToDeveloperId);
				
				sendto(sockfd, net_buf, NET_BUF_SIZE, 
					sendrecvflag, (struct sockaddr*)&addr_con, 
					addrlen); 
				
				
				//for clearing the values
				strcpy(net_buf,"");
				strcpy(bugIdSequenceStirng,"");
				strcpy(bugId,"");
				
				printf("\nBug reported\n");
			}
	}
	else{
		printf("Invalid credentials");
		}
		return 0; 
} 

