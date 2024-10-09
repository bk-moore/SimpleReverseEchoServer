#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
using namespace std;



int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char input[256];
    portno = atoi(argv[2]); //convert string to int
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    server = gethostbyname(argv[1]); //get ip from host name
	
    bzero((char *) &serv_addr, sizeof(serv_addr)); //set buffer to zero
	
    serv_addr.sin_family = AF_INET; //set family 
	
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //set serv_addr, using bcopy for type issues
	
    serv_addr.sin_port = htons(portno); //set portnumber
	
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)  //light error checking 
        printf("connection failed");
	
    printf("To exit type fin, otherwise; Please enter the string to be reversed: "); //ask user for input
	
    cin>>input; //read in input
	
    n = write(sockfd,input,strlen(input));
	
    bzero(input,256); //clear input for response
	
    n = read(sockfd,input,255); //get response
	
    printf("%s\n",input); //display response
	
	
    return 0;
}