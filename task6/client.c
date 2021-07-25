// client code for UDP socket programming 
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
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <netdb.h> 

#define IP_PROTOCOL 0                                                                           //-----PORT NO
#define NET_BUF_SIZE 512 
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
	for (i = 0; i < s; i++) { 
		ch = buf[i]; 
		ch = Cipher(ch); 
		if (ch == EOF) 
			return 1; 
		else
			printf("%c", ch); 
	} 
	return 0; 
} 

// driver code 
int main(int argc, char *argv[]) 
{ 
	int sockfd, nBytes,portno;
	int z=0; 
	struct sockaddr_in addr_con; 
	struct hostent *server;  
	portno = atoi(argv[2]);    
	server = gethostbyname(argv[1]);  
	if (server == NULL) {                                                                                            //serverAdd
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	int addrlen = sizeof(addr_con);  
	 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(portno);     
	bcopy((char *)server->h_addr,                                                                                             //serverAdd
         (char *)&addr_con.sin_addr.s_addr,
         server->h_length);                                                                                      //-----PORT NO
         char net_buf[NET_BUF_SIZE]; 
	FILE* fp; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, 
					IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nFile descriptor not received!!\n"); 
	else
		printf("\nFile descriptor %d received\n", sockfd); 
        
	while (1) { 
		printf("\n*Enter file name to be received ::"); 
		scanf("%s", net_buf); 
		sendto(sockfd, net_buf, NET_BUF_SIZE, 
			sendrecvflag, (struct sockaddr*)&addr_con, 
			addrlen); 

		printf("\n---------DATA RECEIVED---------\n"); 

		while (1) { 
			// receive 
			clearBuf(net_buf); 
			nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 
							sendrecvflag, (struct sockaddr*)&addr_con, 
							&addrlen); 
			printf("\n\nFrom server==> Buffer Size :: %d ; seq no[%d]\n\n",(int)NET_BUF_SIZE,z);				
                         z++;
			// process 
			if (recvFile(net_buf, NET_BUF_SIZE)) { 
				break; 
			} 
		} 
		printf("\n-------------EOF--------------\n"); 
		z=0;
	} 
	return 0; 
} 

