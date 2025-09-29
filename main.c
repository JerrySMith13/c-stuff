/*
A user-friendly CLI utility to print file information
*/

//Included for function fstat + struct stat
#include <sys/stat.h>
//Included for getting file descriptor
#include <fcntl.h>
//Included for getting time formatting
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



//This pointer lives on the stack, so DO NOT FREE
char* file_type(mode_t permissions){
    
    if (S_ISREG(permissions)){
        return "Regular File";
    }
    else if S_ISDIR(permissions){
        return "Directory";
    }
    else if S_ISBLK(permissions){
        return "Block File";
    }
    else if S_ISCHR(permissions){
        return "Character File";
    }
    else if S_ISFIFO(permissions){
        return "FIFO File";
    }
    else if S_ISLNK(permissions){
        return "Link File";
    }
    else if S_ISSOCK(permissions){
        return "Socket File";
    }
    else{
        return "Unknown";
    }
}

//Must be freed if allocated
void time_formatted(time_t time, char* buf, size_t maxsize){
    struct tm* time_f;
    time_f = localtime(&time);
    char* time_format = malloc(sizeof(char) * 21);
    strftime(buf, maxsize, "%Y-%m-%d %H:%M:%S", time_f);
}

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
    char status_time[21];
    char access_time[21];
    char modify_time[21];
    time_formatted(file_stat.st_ctimespec.tv_sec, status_time, 21);
    time_formatted(file_stat.st_atimespec.tv_sec, access_time, 21);
    time_formatted(file_stat.st_mtimespec.tv_sec, modify_time, 21);

    char* ftype = file_type(file_stat.st_mode);
    

    printf("Info for: %s\n", args[1]);

    //Print file type
    printf("File type: %s\n", ftype);

    //Print full path
    printf("Path: %s\n", canonizalized); 
    //Print size
    printf("Size: %s\n", filesize_formatted);
    //Print date-time created
    printf("Created: %s\n", status_time);
    //Print date-time of last access
    printf("Accessed: %s\n", access_time);
    printf("Modified: %s\n", modify_time);
    //Print permissions

    


    free(canonizalized);
    free(filesize_formatted);

    return 0;
    
}