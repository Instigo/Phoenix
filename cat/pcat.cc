#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define MAX_FILENAME_CHARS 255

//
// Name: getFileType
//
// Description: Returns the filetype of a file
/*const char *getPermissions(mode_t mode){

    char filetype = '?';

    if(S_ISREG(mode)) filetype = '-';
    if(S_ISLNK(mode)) filetype = 'l';
    if(S_ISDIR(mode)) filetype = 'd';
    if(S_ISBLK(mode)) filetype = 'b';
    if(S_ISCHR(mode)) filetype = 'c';
    if(S_ISFIFO(mode)) filetype = '|';


    return (const char*)permBuffer;
}*/


// 
// Name: kill
//
// Description: Kills the program with a given error message
//
void kill(char *message){

    perror(message);
    exit(0);
}

int main(int argc, char * argv[]){

    FILE *fp = NULL;
    char filename[MAX_FILENAME_CHARS];
    char ch;
    int idx;


    if(argc < 1){
        // display usage
        printf("Usage pcat <filename>\n");
        return 0;
    }

    for(idx = 1; idx <= argc; ++idx){
        fp = fopen(argv[idx], "r");
        if(fp == NULL){
            printf("%s: No such file or directory\n", argv[idx]);
            return 0;
        }    
        // we will simply read the contents of the file
        while((ch = fgetc(fp)) != EOF)
            putchar(ch);

        fclose(fp);
    }

    return EXIT_SUCCESS;
}
