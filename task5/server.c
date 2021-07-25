/*
AU1841131 : Mansi Dobariya 
A simple server in the internet domain using TCP  The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include<string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<time.h>
#include<sys/stat.h>

 /*reverse  the string */
void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
 /*convert   int n to ascii in s[] */
void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)                               /* record sign */
         n = -n;                                               /* make n positive */
     i = 0;
     do {                                                       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';                   /* get next digit */
     } while ((n /= 10) > 0);                    /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     time_t ticks; 
     struct sockaddr_in serv_addr, cli_addr;
     int n;
    // variables to store date and time components
    int hours, minutes, seconds, day, month, year;
    // time_t is arithmetic time type
    time_t now;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
    /*binding*/
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
      /*listening*/        
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
      /*accepting request*/
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          //error("ERROR on accept");
	printf("error");
      /*read and write operation with client*/
     while(1){
	     bzero(buffer,256);
	     n = read(newsockfd,buffer,255);
	     if (n < 0) error("ERROR reading from socket");
	     if (buffer[0]=='1'){             //time request
				printf("\n--------->The Entered choice: %s",buffer);
				n = write(newsockfd,"Entered  1\n",10);
				// Obtain current time
				// time() returns the current time of the system as a time_t value
				time(&now);
				// localtime converts a time_t value to calendar time and
				// returns a pointer to a tm structure with its members
				// filled with the corresponding values
				struct tm *local = localtime(&now);

				hours = local->tm_hour;	  	// get hours since midnight (0-23)
				minutes = local->tm_min;	 	// get minutes passed after the hour (0-59)
				seconds = local->tm_sec;	 	// get seconds passed after minute (0-59)

				// print local time
				if (hours < 12)	{// before midday
					printf("->Current Time is : %02d:%02d:%02d am\n", hours, minutes, seconds);
					snprintf(buffer, sizeof(buffer), " %02d:%02d:%02d pm\n", hours , minutes, seconds);
				}

				else{	// after midday
					printf("->Current Time is : %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);
					snprintf(buffer, sizeof(buffer), " %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);
				}
				n=write(newsockfd, buffer, strlen(buffer)); 
	       }
	      else if (buffer[0]=='2'){	  //date request
				printf("\n--------->The Entered choice: %s",buffer);
				n = write(newsockfd,"Entered  2",10);
			     	// Obtain current time
				// time() returns the current time of the system as a time_t value
				time(&now);
				// localtime converts a time_t value to calendar time and
				// returns a pointer to a tm structure with its members
				// filled with the corresponding values
				struct tm *local = localtime(&now);

				day = local->tm_mday;			// get day of month (1 to 31)
				month = local->tm_mon + 1;   	// get month of year (0 to 11)
				year = local->tm_year + 1900;	// get year since 1900

				// print current date
				printf("->Current Date is : %02d/%02d/%d\n", day, month, year);
				snprintf(buffer, sizeof(buffer), "%02d/%02d/%d\n", day, month, year);
				n=write(newsockfd, buffer, strlen(buffer)); 
	     	}
		else if (buffer[0]=='3') {       //calc request
			     printf("\n--------->The Entered choice: %s",buffer);
			     n = write(newsockfd,"Entered  3",10);    	  
			     bzero(buffer,256);
			     n = read(newsockfd,buffer,255);
			     printf("Client sent message : %s\n",buffer);
			     //separate from buffer i.e"2 + 3"
			     //stored in to buffer
			    	int i=0;				
				//The first call to strtok must pass the C string to tokenize
				char *p;
				char op1[5];
				char op2[5];
				char op[5];
				char ssum[5]="Error";
				p=strtok(buffer," ");
				strcpy(op1,p);
				//Until there are no tokens left to retrieve, strtok returns NULL, meaning that the string has been fully tokenized, tokenize the string.
				printf("\nOperand1: %s", op1);
				
				//subsequent calls must specify NULL as the first argument, which tells the function to continue tokenizing the string you passed in first
				p=strtok(NULL," ");
				strcpy(op,p);
				printf("\nOperation: %s", op);
				
				p=strtok(NULL," ");
				strcpy(op2,p);
				printf("\nOperand2: %s",op2);
				//covert ascii to int
				int operand1 = atoi(op1);
				int operand2 = atoi(op2);
				
				char addition_sign = '+';
				char sub_sign = '-';
				char mul_sign = '*';
				char div_sign = '/';
				int cal=0;
				//itoa -covert int to ascii for char array
				if(addition_sign == op[0]){
					//printf("\n\nAdding operation...");
					cal = operand1 + operand2;
					itoa(cal, ssum);
				}     else if(sub_sign == op[0]){
					//printf("\n\nSubtraction operation...");
					cal = operand1 - operand2;
					itoa(cal, ssum);
				}         else if(mul_sign == op[0]){
					//printf("\n\nMultiplication operation...");
					cal = operand1 * operand2;
					itoa(cal, ssum);
				}    else if(div_sign == op[0]){
					//printf("\n\nDivision operation...");
					cal = operand1 / operand2;
					itoa(cal, ssum);
				}     
			     printf("Sending calculated message :%s\n",ssum);
			     n=write(newsockfd, ssum, strlen(ssum)); 
	       }
	     else if (buffer[0]=='4') {            //exit request
			     printf("\nClient requested to exit,Entered Choice: %s .",buffer);
			     n = write(newsockfd,"Exiting...",10);
	       }
	     else {                                                //invalid input   
	     	     	     n = write(newsockfd,"INVALID INPUT,Enter valid input",35);
	     	}    
	    
     }
     return 0; 
}
