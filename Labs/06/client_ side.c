// -------------------------------------------------------------HEADER------------------------------------------------------------------------------//

// FILE NAME: client.c
// WRITTEN BY: Usama Mahmood (0710399)

// DESCRIPTION: This code is written in C programming language.
// This is the C program to implement the client side programming, in the code the socket programming has been implemented.
// There are two function in this code, one is "send_file" and  the other is main function.
// Overall this client code is making connection with server side using sockets and sending file data to the server.
// The further explanation about the code and implementation is below. Thank you.

// ------------------------------------------------------------------------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#define SIZE 1024

//void send_filename(FILE *fp, int sockfd)
//{
// send(sockfd, argv[1], 0, 0);
//}

// -------------------------------------------------------------[send_file]FUNCTION-----------------------------------------------------------------------//

// DESCRIPTION: This is the function for sending the file data in the form of  buffer to the server.
// The size of the data is defined, in this function the content of the file is taken from the target file and sended to the server.

// --------------------------------------------------------------------------------------------------------------------------------------------------------//
void send_file(FILE *fp, int sockfd)
{

 int n;
 char data[SIZE] = {0};

 while(fgets(data, SIZE, fp) != NULL) //getting the content of the file.
 {
  if (send(sockfd, data, sizeof(data), 0) == -1) // sending the content of the file to the server side.
  {
   perror("[-]Error in sending file.");
   exit(1);
  }
  bzero(data, SIZE);
 }
}

// -------------------------------------------------------------[main]FUNCTION-----------------------------------------------------------------------------//

// DESCRIPTION: In the main function of client side, there is alot happening, because the creation of socket is in the main function.
// In the main function I am taking the target file name as a command line parameter and reading that file and sending its content.
// Socket programming has been implemented in the function, socket has been created, binded and connecting to the server in order to send  data.

// --------------------------------------------------------------------------------------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
 int port = 50399;//port number is defined.
 int e;
 int sockfd;
 struct sockaddr_in server_addr; //structure for the socket credentials.
 FILE *fp; //file pointer.

 sockfd = socket(AF_INET, SOCK_STREAM, 0);//socket creation.
 if(sockfd < 0)
 {
  perror("[-]Error in socket");
  exit(1);
 }
 printf("[+]Server socket created successfully.\n");
//assigning socket type, ip address and port.
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = port;
 server_addr.sin_addr.s_addr = INADDR_ANY;

 e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));// connecting the socket to the server.
 if(e == -1)
 {
  perror("[-]Error in socket");
  exit(1);
 }
 printf("[+]Connected to Server.\n");

 if (argv[1] == NULL)// getting command line argument.
 {
  perror("[-]ERROR: File not found.");
  exit(1);
 }
 else if(argv[1] != NULL)
 {
  fp = fopen(argv[1], "r");// opening and reading the file.
 }

 send_file(fp, sockfd);// calling function.
 printf("[+]File data sent successfully.\n");
 printf("[+]Closing the connection.\n");
 close(sockfd);//closing channel.

 return 0;
}
