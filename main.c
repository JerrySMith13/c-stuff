/*
A user-friendly CLI utility to print file information
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int nargs, char** args){
    
    if (nargs != 2){
        printf("Usage: %s <filepath>", args[0]);
        return 0;
    }

    int filedesc;
    filedesc = open(args[1], O_RDONLY);

    struct stat file_stat;
    if (fstat(filedesc, &file_stat) != 0){
        printf("Error: File was unable to be opened");
        return -1;
    }

    char* restrict canonizalized = realpath(args[1], NULL);

    if (!canonizalized){
        printf("Error: could not canonicalize path");
        return -1;
    }




    printf("Info for: %s\n", args[1]);

    //Print full path
    printf("Full path: %s", canonizalized); 
    //Print size
    //Print date-time created
    //Print date-time of last modification
    //Print permissions


    free(canonizalized);

    return 0;
    
}