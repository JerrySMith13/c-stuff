/*
A user-friendly CLI utility to print file information
*/

//Included for function fstat + struct stat
#include <sys/stat.h>
//Included for getting file descriptor
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


//This string MUST BE FREED
char* size_formatted(off_t st_size){
    char* buf;
    double fsize;
    if (st_size < 1e3){
        asprintf(&buf, "%lld bytes", st_size);
    }
    else if (st_size < 1e6){
        fsize = (double) st_size/1e3;
        asprintf(&buf, "%.3f kilobytes", fsize);
    }
    else if (st_size < 1e9){
        fsize = (double) st_size/1e6;
        asprintf(&buf, "%.3f megabytes", fsize);
    }
    else if (st_size < 1e12){
        fsize = (double) st_size/1e9;
        asprintf(&buf, "%.3f gigabytes", fsize);
    }
    else if (st_size < 1e15){
        fsize = (double) st_size/1e12;
        asprintf(&buf, "%.3f terabytes", fsize);
    }
    else{
        fsize = (double) st_size/1e15;
        asprintf(&buf, "%.3f petabytes", fsize);
    }

    return buf;
    

}

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

    char* __restrict__ canonizalized = realpath(args[1], NULL);

    if (!canonizalized){
        printf("Error: could not canonicalize path");
        return -1;
    }
    
    char* restrict filesize_formatted = size_formatted(file_stat.st_size);

    printf("Info for: %s\n", args[1]);

    //Print full path
    printf("Full path: %s\n", canonizalized); 
    //Print size
    printf("Size: %s\n", filesize_formatted);
    //Print date-time created
    //Print date-time of last modification
    //Print permissions

    free(canonizalized);
    free(filesize_formatted);

    return 0;
    
}