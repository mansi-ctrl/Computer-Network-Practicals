/*
AU1841131 : Mansi Dobariya
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    //connection to server
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
        while(1){
		    printf("-----------------------------------------------------\n 1.Time \n 2.Date \n 3.Calc\n 4.Exit\n---------------------------------------------------\n");   
		    printf("Please enter choice: ");
		    bzero(buffer,256);
		    fgets(buffer,255,stdin);
		    if (buffer[0]=='1'){                          //time request
					  n = write(sockfd,buffer,strlen(buffer));
				     if (n < 0) 
				           //error("ERROR writing to socket");
					    printf("ERROR writing to socket");
				    bzero(buffer,256);
				     n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("%s\n",buffer);
				     bzero(buffer,256);
				      n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("->Current Time is :%s\n",buffer);
				     bzero(buffer,256);
					    /* while ( (n = read(sockfd, buffer, sizeof(buffer)-1)) > 0)
					    {
						buffer[n] = 0;
						if(fputs(buffer, stdout) == EOF)
						{
						    printf("\n Error : Fputs error\n");
						}
				    	   } */
		    }
		    else if (buffer[0]=='2'){                          //date request
				    n = write(sockfd,buffer,strlen(buffer));
				     if (n < 0) 
				           //error("ERROR writing to socket");
					    printf("ERROR writing to socket");
				    bzero(buffer,256);
				     n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("%s\n",buffer);
				     bzero(buffer,256);
				      n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("->Current Date is :%s\n",buffer);
				     bzero(buffer,256);
					    /* while ( (n = read(sockfd, buffer, sizeof(buffer)-1)) > 0)
					    {
						buffer[n] = 0;
						if(fputs(buffer, stdout) == EOF)
						{
						    printf("\n Error : Fputs error\n");
						}
				    	   } */
		    }
		    else if(buffer[0]=='3'){                          //calc request
				    n = write(sockfd,buffer,strlen(buffer));
				    if (n < 0) 
				           //error("ERROR writing to socket");
					    printf("ERROR writing to socket");
				    bzero(buffer,256);
				     n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("%s\n",buffer);
				     bzero(buffer,256);
					//do      {
						/* Ask user for message to send to server */
						printf("Please enter the message to the server('operator1 oprand operator2'): ");
						bzero(buffer,256);
						fgets(buffer,255-1,stdin);
						
						/* Write to server */
						n = write(sockfd,buffer,strlen(buffer));
						if (n < 0) 
						  {
						    fprintf(stderr, "ERROR writing to socket\n");
						    exit(1);
						  }
						
						/* Read reply */
						bzero(buffer,256);
						n = read(sockfd,buffer,255);
						if (n < 0) 
						  {
						    fprintf(stderr, "ERROR reading from socket\n");
						    exit(1);
						  }
						printf("Server replied: %s\n",buffer);
				                
					      //} while(1);
		    }
		     else if(buffer[0]=='4'){                          //Exit request
				     n = write(sockfd,buffer,strlen(buffer));
				     if (n < 0) 
				           //error("ERROR writing to socket");
					    printf("ERROR writing to socket");
				     bzero(buffer,256);
				     n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("%s\n",buffer);
				     bzero(buffer,256);
				     sleep(5);
					 exit(0) ;
		     }
		     else {                          //incalid input
				     n = write(sockfd,buffer,strlen(buffer));
				     if (n < 0) 
				           //error("ERROR writing to socket");
					    printf("ERROR writing to socket");
				      bzero(buffer,256);
				     n = read(sockfd,buffer,255);
				     if (n < 0) 
				           //error("ERROR reading from socket");
					    printf("ERROR reading from socket");
				     printf("%s\n",buffer);
				     bzero(buffer,256);
		     }

    }
     
    return 0;
}
