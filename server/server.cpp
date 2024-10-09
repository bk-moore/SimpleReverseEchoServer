#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;





bool isOn;

int main(int argc, char *argv[])
{
	//declare variables
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char input[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 
     if (argc < 2) //light error checking
	 {
         fprintf(stderr,"error, no port \n");
         exit(1);
     }
	 
	 
     sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	 
     if (sockfd < 0) 
        printf("error opening socket"); //light error checking
	
     bzero((char *) &serv_addr, sizeof(serv_addr)); //clear buffer
	 
     portno = atoi(argv[1]); //convert port number from string to int
	 
     serv_addr.sin_family = AF_INET; //set family
	 
     serv_addr.sin_addr.s_addr = INADDR_ANY; //set ip of host
	 
     serv_addr.sin_port = htons(portno);//set port 
	 
	 
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //check for bind
              printf("error on binding");
			  
	 listen(sockfd,5);//listen for connections, max of 5 not needed for this application
	 
     clilen = sizeof(cli_addr); //get len of client address
	 
	 isOn = 1; //initiate while loop
	 
	 while(isOn == 1) //keep connection open until fin entered
	 {
		 newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		 
		 if (newsockfd < 0) 
			  printf("error on accept");
		  
		 bzero(input,256);
		 
		 n = read(newsockfd,input,255);
		 
		 if (n < 0) 
			 printf("error reading from socket");
		 
		 printf("Here is the message: %s\n",input);
		 
		 //declare variables
		 int i;
		 int j;
		 int temp;
		 int l = strlen(input);
		 
		 
		 //reverse the string
		 for(i = 0, j = l - 1; i<j; i++, j--)
		 {
			 temp = input[i];
			 input[i] = input[j];
			 input[j] = temp;
		 }
		 
		 //set string to check against
		 string s = "nif";
		 
		 //dealing with type conversions 
		 const char* str1 = input;
		 
		 const char* str2 = s.c_str();
		 
		 //using strcmp to compare two constant chars, result of 0 means they are equal
		 int result;
		 result = strcmp(str1,str2);
		 
		
		 
		 if(result == 0) //if equal send echo message and close sockets, set isOn to zero to exit loop
		 {
			send(newsockfd,input,sizeof(input),0);
			close(sockfd);
			close(newsockfd);
			isOn = 0;
			
		 }
		 
		 else //send message and close new sock allowing for newone to open on next call
		 {
			send(newsockfd,input,sizeof(input),0);
			close(newsockfd);
			
		 }
		 
	 }
	 close(sockfd); //cleanup
     return 0; 
}