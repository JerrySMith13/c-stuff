#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int nargs, char** args){
    
    if (nargs != 2){
        printf("Usage: %s <filepath>", args[0]);
    }

    int filedesc;

    filedesc = open(args[1], O_RDONLY);

    struct stat file_stat;
    fstat(filedesc, &file_stat);
}