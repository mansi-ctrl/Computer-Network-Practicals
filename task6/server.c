/*
1. The server starts and waits for filename.
2. The client sends a filename.
3. The server receives filename.
   If file is present,
   server starts reading file 
   and continues to send a buffer filled with
   file contents encrypted until file-end is reached.
4. End is marked by EOF.
5. File is received as buffers until EOF is 
received. Then it is decrypted.
6. If Not present, a file not found is sent.
*/

// server code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define IP_PROTOCOL 0                                                                                                       //-------IP
#define NET_BUF_SIZE 512 
#define cipherKey 'S' 
#define sendrecvflag 0 
#define nofile "File Not Found!" 

// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
} 

// function to encrypt 
char Cipher(char ch) 
{ 
	return ch ^ cipherKey; 
} 

// function sending file 
int sendFile(FILE* fp, char* buf, int s) 
{ 
	int i, len; 
	if (fp == NULL) { 
		strcpy(buf, nofile); 
		len = strlen(nofile); 
		buf[len] = EOF; 
		for (i = 0; i <= len; i++) 
			buf[i] = Cipher(buf[i]); 
		return 1; 
	} 

	char ch, ch2; 
	for (i = 0; i < s; i++) { 
		ch = fgetc(fp); 
		ch2 = Cipher(ch); 
		buf[i] = ch2; 
		if (ch == EOF) 
			return 1; 
	} 
	return 0; 
} 

// driver code 
int main(int argc, char *argv[]) 
{ 
	int sockfd, nBytes,portno; 
	int z=0;
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	portno = atoi(argv[1]);
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(portno);                                                                         //-----PORT NO
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	char net_buf[NET_BUF_SIZE]; 
	FILE* fp; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);                                   //-----IP

	if (sockfd < 0) 
		printf("\n------File descriptor not received!!\n"); 
	else
		printf("\n------File descriptor %d received\n", sockfd); 
        
	// bind() 
	if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0) 
		printf("\n------Successfully binded!\n"); 
	else
		printf("\n------Binding Failed!\n"); 

	while (1) { 
		printf("\nWAITING FOR FILENAME....\n"); 

		// receive file name 
		clearBuf(net_buf); 

		nBytes = recvfrom(sockfd, net_buf, 
						NET_BUF_SIZE, sendrecvflag, 
						(struct sockaddr*)&addr_con, &addrlen); 

		fp = fopen(net_buf, "r"); 
		printf("\nFile Name Received :: %s\n", net_buf); 
		if (fp == NULL) 
			printf("\nFile open failed!\n"); 
		else
			printf("\nFile Successfully opened!\n"); 

		while (1) { 
                          printf("\n\nTo client==> Buffer Size :: %d ; seq no[%d]\n\n",(int)NET_BUF_SIZE,z);				
                         z++;
			
			// process 
			if (sendFile(fp, net_buf, NET_BUF_SIZE)) { 
				sendto(sockfd, net_buf, NET_BUF_SIZE, 
					sendrecvflag, 
					(struct sockaddr*)&addr_con, addrlen); 
				break; 
			} 
                       // send 
			sendto(sockfd, net_buf, NET_BUF_SIZE, 
				sendrecvflag, 
				(struct sockaddr*)&addr_con, addrlen); 
			clearBuf(net_buf); 
		} 
		z=0;
		if (fp != NULL) 
			fclose(fp); 
	} 
	return 0; 
} 


