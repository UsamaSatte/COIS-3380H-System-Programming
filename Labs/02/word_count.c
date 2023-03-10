// -----------------------------------HEADER------------------------------------------------//
// File Name: word_count.c

// Written by: Usama Mahmood (0710399)

// Description: This is the script to count the number of lines, words and bytes of a file.
//It takes the parameter on a command line as a filename that we are going to count its
//number of lines, words and bytes.
//When we run the script it will show the output as three numbers which represents the number
//of lines in a file, number of words in a file and number of bytes of a file. If there is an
//error in the file name or in finding it, the output will show the error message.
//-------------------------------------------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining structure on the top.
struct file_data
{
    int line_count;
    int word_count;
    int byte_count;
};

  struct file_data file_ini = {0 , 0, 0}; // Initializing values to the variables in the structure.
  struct file_data *file_ini_pointer = &file_ini; // Pointer for the variable of structure type.

int counter(FILE *file_pointer) // Function to perform the counting functionality
{
    char ch;
  int in_word = 0;

  // It is the functionaity to count the number of lines, words and bytes in the file.

  while ((ch = fgetc(file_pointer)) != EOF)// We used fgetc library to get every character from the file till end of the file to count bytes.
{
    file_ini_pointer->byte_count++; // Assinging values to the variables in the structure by the pointers.

    if(ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n')
 {
      if (in_word)
      {
        in_word = 0;
        file_ini_pointer->word_count++;
      }
 }
  if(ch = '\0' || ch == '\n')file_ini_pointer->line_count++;
     else
    {
      in_word = 1;
    }
}
}

// Main function which accepts the argument from command line and reads the file.
// Main function also shows the output.

void main(int argc, char *argv[])
{
  FILE *file_pointer;
  file_pointer = fopen(argv[1], "r"); //Accepting the argument from the command line and reading the file.
  if(file_pointer == NULL) {
    printf("Could not open the file %s\n"); // If there is no file, then showing a message.
  }
counter(file_pointer); // Calling the function counter which has all the functionality.
// Printing the result.
  printf("%d\t", file_ini_pointer->line_count);
  printf("%d\t", file_ini_pointer->word_count);
  printf("%d\t", file_ini_pointer->byte_count);
}
