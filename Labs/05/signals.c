// -------------------------------------------------------------------HEADER------------------------------------------------------------------------//

// FILE NAME: signal.c
// WRITTEN BY: Usama Mahmood (0710399)

// DESCRIPTION: This code is written in C programming language.
// This is the C program to implement the signals with a signal handler function.
// In this program there is a signal handler function performing different functionalities.
// This program has a main function which installs the signals.
// The purpose of the program is to implement the signals as; SIGINT, SIGQUIT, and SIGUSR1.
// Other information is in the code, thank you.

// ------------------------------------------------------------------------------------------------------------------------------------------------//

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>
#define MAX 5

// --------------------------------------------------------SIGNAL HANDLER FUNCTION----------------------------------------------------------------//

// DESCRIPTION: Signal handler function name is signal_handler, and it handles the SIGINT, SIGQUIT and SIGUSR1.
// Signal handler function has a if statement which describes all the signals as;
// SIGINT signal install for the counting the number of times pressing CTRL-C, and tells when it reaches to its maximum limit.
// SIGQUIT has been called by the kill call, when child process calls kill to kill the process.
// SIGUSR1 displays the message of recieving a signal from child process.

// ------------------------------------------------------------------------------------------------------------------------------------------------//

void signal_handler(int signal_num)
{
 static int counter = 1; //counting the number of ctrl-c pressed
 int parent;

 if(signal_num == SIGINT)
 {
  printf("This is the %d time you pressed ctrl-c\n",counter);
  //reinitialize SIGINT signal
  signal(SIGINT, signal_handler);
 }
     if(counter++ > 5)// counting
     {
     printf("%d has been exceeded and signal handler is deactivated\n",MAX);
     signal(SIGINT, SIG_DFL);
     }
 printf("Wait for another signal...\n");

 if(signal_num == SIGQUIT)
 {
  //if SIGQUIT pressed new process is created ,child sends SIGUSR1 to parent
  parent = getpid();//storing pid in the parent
  pid_t child;
  child = fork();//creating child process
     if(child < 0)
     {
      printf("Error in child creation\n");
     }
     else if(child == 0) //child process created
     {
      printf("I am the child and I am sending a signal\n");
      //it sends SIGUSR1 signal to parent process
      kill(getppid(),SIGUSR1);
      exit(0); //exit
     }
     if(child > 0)//parent process
     {
      signal(SIGUSR1,signal_handler);//parent process recieves a signal from the child process
      wait(0);
           if(signal_num == SIGUSR1)//when it recieves a signal from child process, it will show these messages
           {
            printf("Child has sent a signal so I guess you are bored, have a great day!\n");
            printf("Parent exiting after receiving SIGUSR1 from child.\n");
            signal(SIGUSR1,SIG_DFL);
            exit(0);
           }
     }
 }
}

// -------------------------------------------------------------MAIN FUNCTION-----------------------------------------------------------------------//

// DESCRIPTION: Main funciton is just installing the signal handlers in order to running the program.

// ------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
 //installing signal handlers
 signal(SIGINT,signal_handler);
 signal(SIGQUIT,signal_handler);
 signal(SIGUSR1,signal_handler);
 printf("Wait for another signal...\n");
 for(;;);
}
