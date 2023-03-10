// -------------------------------------------------------------HEADER------------------------------------------------------------------------------//

// FILE NAME: process_creation.c
// WRITTEN BY: Usama Mahmood (0710399)

// DESCRIPTION: This code is written in C programming language.
// This is the C program to implement the process creation and do stuff in the processes.
// In this program, we created 3 process, 1 parent process and 2 of its child processes and 1 grandchild process.
// Name of the processes are; child1, child2 and grandchild_child1 which is the child of child1.
// Other information is in the code, thank you.

// ------------------------------------------------------------------------------------------------------------------------------------------------//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFSIZE 512

// Function prototypes
int child1_process();
int child2_process();
int grandchild_child1_process();

// -------------------------------------------------------------MAIN FUNCTION-----------------------------------------------------------------------//

// DESCRIPTION: In the main function I created two child processes using fork and implemented a if statement.
// I used wait function in the parent process to wait for its child process and display a process id which complete its process
// In the if statement, the program is refering the child process to their functions, where the actual functionality is

// ------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
   pid_t child1;
   pid_t child2;
   int status, exit_status;
   int completed_pid; // this variable is for the parent process to wait for its child processes


   printf("\n\nIn the main program, just before the fork() statement\n");
   printf("\tmy process ID is %d and my parent's process ID is %d\n\n",getpid(),getppid());

   //Cteating the two child processes
   child1 = fork();
   child2 = fork();
   //If statements is for the childs processes
   if(child1 < 0 && child2 < 0)
   {
        printf("error\n");
   }
   else if(child1 == 0 && child2 > 0)
   {    //if it is a child 1 process then it refers to the function where its functionality is implemented
        printf("\tFirst fork was successful. First child code is now starting...\n");
        exit_status = child1_process();
        printf("\tFirst Child has returned from the function. Status=%d\n",exit_status);
   }
   else if(child1 > 0 && child2 == 0)
   {
       //if it is a child 2 process then it refers to the function where its functionality is implemented
       printf("\tSecond fork was successful. Second child code is now starting...\n");
       exit_status = child2_process();
       printf("\tSecond Child has returned from the function. Status=%d\n",exit_status);
   }
   else if(child1 > 0 && child2 > 0)
   {
        //if it is a parent process then it is waiting for its child processes to complete their processing
        printf("ORIGINAL PARENT: I am waiting for the children to complete their processes\n");
        completed_pid = wait( (int *)0 );  // wait for any child to finish
        //it will tell which process id has completed its processing
        printf("ORIGINAL PARENT: A child with process id %d has completed its processing.\n\n\n", completed_pid);
   }

   return 0;
}
// ------------------------------------------------------------- Children and gradnchildren -------------------------------------------------------//

// DESCRIPTION: In the main function I created two child processes using fork and implemented a if statement.
// I used wait function in the parent process to wait for its child process and display a process id which complete its process
// In the if statement, the program is refering the child process to their functions, where the actual functionality is
// child1_process: In this process I am creating a grandchild and making child 1 wait for it while grandchild complete its processing
// child2_process: In this process I am reading a file and copying its content and storing it to another file and counting the bytes of the file
// where is copied the content, and printing it.
// grandchild_child1_process: In this function I am just executing a command using execlp and getenv to get the environment variable as username
// ------------------------------------------------------------------------------------------------------------------------------------------------//

//this is the process for the child 1 process
int child1_process()
{
  int child1_pid;
  int status, exit_status;
  int return_status;
  //assigning child 1 pid to a variable
  child1_pid = getpid();

  printf("Child 1 created\n");
  printf("first child process id is %d\n", child1_pid);

  //creating grandchild of the original process or child of a child 1 process
  pid_t grandchild_child1;
  grandchild_child1 = fork();
         //this if statement is doing the same functionality as in the main function's if statement is doing
        if(grandchild_child1 < 0)
        {
                 printf("error\n");
        }
        else if(grandchild_child1 == 0)
        {
                 //now this is also refering to the other function which has the functionality for the grandchild process
                 printf("\tThird fork was successful. Grand child code now starting\n");
                 exit_status = grandchild_child1_process();
                 printf("\tGrand child has returned from the function. Status=%d\n",exit_status);
        }
        else if(grandchild_child1 > 0)
        {
                 //now child 1 process who is the parent of grandchild is waiting for it to complete its processing
                 printf("PARENT OF GRANDCHILD: I am waiting for my child to complete its processing\n");
                 //here i am waiting in a different way, i am just checking either it has completed its  process or not by using WNOHANG
                 waitpid(grandchild_child1, &return_status, WNOHANG);  // wait for any child to finish
                 sleep(1);
                 //return status stores the status of the process either it is terminated or still in process
                 if(return_status == 0)
                 {
                       printf("PARENT OF GRANDCHILD: Grandchild process terminated normally\n");
                 }
                 else if(return_status == 1)
                 {
                      printf("PARENT OF GRANDCHILD: Try Again\n");
                 }
        }
  return 0;
}

//it is the child 2 process function
int child2_process()
{
  int child2_pid;
  int status, exit_status;
   FILE *fptr1, *fptr2;// these are two file pointer one is for reading a file and other is for writing a file
   char c;
    int byte;
    char ch;
  //it is to show that child 2 is created with the pid
  child2_pid =  getpid();
  printf("Child 2 created\n");
  printf("second child process id is %d\n", child2_pid);

  // Open one file for reading
  fptr1 = fopen("/home/COIS/3380/lab3/diplodocus.pdf", "r");
        if (fptr1 == NULL)
        {
                printf("Cannot open file %s \n");
                exit(0);
        }
 // Open another file for writing
 fptr2 = fopen("/home/usamamahmood/cois3380/lab04/lab4_file_copy.pdf", "w");
        if (fptr2 == NULL)
        {
                printf("Cannot open the writing file\n");
                exit(0);
        }

 // Read contents from file
 c = fgetc(fptr1);
        while (c != EOF)
        {
                fputc(c, fptr2);
                c = fgetc(fptr1);
        }
        while ((ch = fgetc(fptr2)) != EOF)// We used fgetc library to get every character from the file till end of the file to count bytes.
        {
                byte++; // Assinging values to the variables in the structure by the pointers.
        }
 printf("%d bytes are copied\n", byte); // printing the result showing the bytes copied
        //closing both the file after reading and writing
        fclose(fptr1);
        fclose(fptr2);
  return 0;
}

//finally this function is carrying the functionality for the grandchild son of child 1 and grandson of original parent
int grandchild_child1_process()
{
  int grandchild_child1_pid;
  int status, exit_status;
//  char *command;
  char *user_name;//it is for storing environment variable
  char *file_name = "ps";
  char *arg1 = "-T";
  char *arg2 = "-aef";
  char *arg3 = "--forest";
  char *arg4 = "-U";

  grandchild_child1_pid = getpid();
  //it is for making sure that function is working by showing grandchild's pid
  printf("Grand child created\n");
  printf("grand child process id is %d\n", grandchild_child1_pid);

  sleep(3);

        //executing command
        user_name = getenv("USER");//it is for storing environment variable username
        printf("ps -T -aef --forest -U command...\n");
        execlp(file_name, file_name, arg1 ,arg2, arg3, arg4, user_name ,NULL);// using execlp to run a command
  return 0;
}
