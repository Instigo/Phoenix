#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_CHARS 255

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
