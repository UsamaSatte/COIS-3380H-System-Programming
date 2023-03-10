// -------------------------------------------------------------HEADER------------------------------------------------------------------------------//

// FILE NAME: server.c
// WRITTEN BY: Usama Mahmood (0710399)

// DESCRIPTION: This code is written in C programming language.
// This is the C program to implement the server side programming, in the code the socket programming has been implemented.
// There are two function in this code, one is "write_file" and  the other is main function.
// Overall this server code is making connection with client side using sockets and accepting file data and writing it.
// The further explanation about the code and implementation is below. Thank you.

// ------------------------------------------------------------------------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#define SIZE 1024 //fixed size for buffer
#define F_SIZE 32

//void file_name(int sockfd)
//{
// int p;
// char f_buffer[F_SIZE];
// while(1)
// {
 // p = recv(sockfd, f_buffer, F_SIZE, 0);
 // if(p <=0)
 // {
  // break;
  // return;
 // }
  //fprintf(fp, "%s", buffer);
  //bzero(buffer, SIZE);
 // fprintf("Filename: %s", f_buffer);
// }
// return;
//}

// -------------------------------------------------------------[write_file]FUNCTION-----------------------------------------------------------------------//

// DESCRIPTION: This is the function for recieving the file data into the buffer and writing it into the new file.
// In this function file data coming from the client side and saving it by opening the file using the fopen() system call and writing the data into the new file.

// --------------------------------------------------------------------------------------------------------------------------------------------------------//

void write_file(int sockfd)
{
 int n;
 FILE *fp; //file pointer
 char *filename = "mahmood_usama_lab06_sourcefile_local_clone"; //it is the file where the data has been copied or written.
 char buffer[SIZE];

 fp = fopen(filename, "w"); // opening the file and writing it.
 while (1)
 {
  n = recv(sockfd, buffer, SIZE, 0); // recieving buffer from the client
  if (n <= 0)// if file is empty then stop.
  {
   break;
   return;
   }
   fprintf(fp, "%s", buffer);
   bzero(buffer, SIZE);
 }
 return;
}

// -------------------------------------------------------------[main]FUNCTION-----------------------------------------------------------------------------//

// DESCRIPTION: In the main function of server side, there is alot happening, because the creation of socket is in the main function.
// Socket programming has been implemented in the function, socket has been created, binded and accepting data from the client.

// --------------------------------------------------------------------------------------------------------------------------------------------------------//
int main()
{
 int port = 50399; // this is the port number by which server can interact with client.
 int e;
 int sockfd, new_sock;
 struct sockaddr_in server_addr, new_addr; // in this structure there are all socket credentials by which socket can be implemented.
 socklen_t addr_size;
 char buffer[SIZE];

 sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket creation.
 if(sockfd < 0)
 {
  perror("[-]Error in socket");
  exit(1);
 }
 printf("[+]Server socket created successfully.\n");

 server_addr.sin_family = AF_INET; //socket type
 server_addr.sin_port = port; // defining port
 server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// deifining ip address, which is any.

 e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //binding  the socket
 if(e < 0)
 {
  perror("[-]Error in bind");
  exit(1);
 }
 printf("[+]Binding successfull.\n");

 if(listen(sockfd, 10) == 0) //socket is listening for the client.
 {
  printf("[+]Listening....\n");
 }
 else
 {
  perror("[-]Error in listening");
  exit(1);
 }

 addr_size = sizeof(new_addr);
 new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size); // socket is accepting from the client.
 write_file(new_sock); // calling function.
 printf("[+]Data written in the file successfully.\n");

 return 0;
}

