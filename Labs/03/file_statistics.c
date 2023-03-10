// -------------------------------------------------------------HEADER------------------------------------------------------------------------------//

// File Name: file_stat.c
// Written by: Usama Mahmood (0710399)

// Description: This code is written in C programming language.
// This is the script to show the 4 types of files in the directory, which are;
//(1) Largest file, (2) Smallest file, (3) Most recent file, (4) Oldest file.
// This program takes directory name as an argument from the command line, if there is no argument, the it reads the current present directory.
// This code uses opendir(), readdir(), and stat() functions in order to give the required output.
// This program mimics the "ls" and "ls -l" functionality.
// This program has; two function;
// Function 01: long_listing()
// long_listing function includes all implemented functionality code in it. Which is the display of ls -l and use of stat function in it.
// Function 02: main()
// Main function includes opening a directory, taking argument from the command line, and reading the content of a directory.

// ------------------------------------------------------------------------------------------------------------------------------------------------//





#include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include<dirent.h>
# include <time.h>
#include <unistd.h>
# include <pwd.h>
# include <grp.h>

    struct dirent *the_file; //This will be used to call when the file will be found in the directory.
    struct stat the_buffer; //This is for the implementation of the stat functionality and for getting the file information.
    struct passwd *tf; //This is for to know the file owner.
    struct group *gf; //This is for to know the file group.
   char buf[512];// This is to display the path of the file.


int long_listing(DIR *the_directory)
 {
        //File type display according to the proper format.
 switch (the_buffer.st_mode & S_IFMT)
        {
            case S_IFBLK: printf("b "); break;
            case S_IFCHR: printf("c "); break;
            case S_IFDIR: printf("d "); break;
            case S_IFIFO: printf("p "); break;
            case S_IFLNK: printf("l "); break;
            case S_IFSOCK: printf("s "); break;
            //Filetype isn't identified
            default: printf("- "); break;
        }

 //Permissions according to the proper format.
        printf( (the_buffer.st_mode & S_IRUSR) ? " r" : " -");
        printf( (the_buffer.st_mode & S_IWUSR) ? "w" : "-");
        printf( (the_buffer.st_mode & S_IXUSR) ? "x" : "-");
        printf( (the_buffer.st_mode & S_IRGRP) ? "r" : "-");
        printf( (the_buffer.st_mode & S_IWGRP) ? "w" : "-");
        printf( (the_buffer.st_mode & S_IXGRP) ? "x" : "-");
        printf( (the_buffer.st_mode & S_IROTH) ? "r" : "-");
        printf( (the_buffer.st_mode & S_IWOTH) ? "w" : "-");
        printf( (the_buffer.st_mode & S_IXOTH) ? "x" : "-");

      // printf("\t%d ", the_buffer.st_nlink);

       //User ID according to the proper format.
       tf = getpwuid(the_buffer.st_uid);
       printf("\t%s ", tf->pw_name);

      // Group ID according to the proper format.
       gf = getgrgid(the_buffer.st_gid);
       printf("\t%s ", gf->gr_name);

     // Size according to the proper format.
       printf("%zu",the_buffer.st_size);

     //Name according to the proper format.
       printf(" %s", the_file->d_name);

    // Time of last modification according to the proper format.
       printf(" %s", ctime(&the_buffer.st_mtime));
}

void main(int argc, char *argv[])

{
   //This the pointer of target directory, by the use of argv pointer we will accept the argument.
    DIR *the_directory;

  //This if statement tells thats if there is no argument on the command line then accept the current directory as an target directory.
  if(argv[1] == NULL)
{
    the_directory = opendir(".");
  //This while loop tells that read the file until it ends.
 while ((the_file = readdir(the_directory)) != NULL)
  {

  //This defines the path to the file.
    sprintf(buf, "%s/%s",".", the_file->d_name);

  //Then we use stat function in order to retrieve information about the file
    stat(buf, &the_buffer);

   //Calling the above function to implement the functionality here.
    long_listing(the_directory);
}
  }

   //If there is an argument then accept it as a target directory and open it.
 else if(argv[1] != NULL)
{
   the_directory = opendir(argv[1]);
  //This while loop tells that read the file until it ends.
 while ((the_file = readdir(the_directory)) != NULL)

  {

  //This defines the path to the file.
  sprintf(buf, "%s/%s", argv[1], the_file->d_name);

  //Then we use stat function in order to retrieve information about the file
   stat(buf, &the_buffer);

  //Calling the above function to implement the functionality here.
  long_listing(the_directory);
  }
}
 else
  {
   printf("Could not open the file\n");
  }

  closedir(the_directory);

}
