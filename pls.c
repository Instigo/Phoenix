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

static char permBuffer[30];
char pathname[MAXPATHLEN];

//
// Name: getPermissions
//
// Description: Returns a buf
const char *getPermissions(mode_t mode){

    char filetype = '?';

    if(S_ISREG(mode)) filetype = '-';
    if(S_ISLNK(mode)) filetype = 'l';
    if(S_ISDIR(mode)) filetype = 'd';
    if(S_ISBLK(mode)) filetype = 'b';
    if(S_ISCHR(mode)) filetype = 'c';
    if(S_ISFIFO(mode)) filetype = '|';

    sprintf(permBuffer, "%c%c%c%c%c%c%c%c%c%c %c%c%c", filetype,
        mode & S_IRUSR ? 'r' : '-', // read, owner
        mode & S_IWUSR ? 'w' : '-', // write, owner
        mode & S_IXUSR ? 'x' : '-', // execute/search, owner
        mode & S_IRGRP ? 'r' : '-', // read, group
        mode & S_IWGRP ? 'w' : '-', // write, group
        mode & S_IXGRP ? 'x' : '-', // execute/search, group
        mode & S_IROTH ? 'r' : '-', // read, others
        mode & S_IWOTH ? 'w' : '-', // write, others
        mode & S_IXOTH ? 'x' : '-', // execute, others
        mode & S_ISUID ? 'U' : '-', // set user ID on execution
        mode & S_ISGID ? 'G' : '-', // set group ID on execution
        mode & S_ISVTX ? 'S' : '-'); // on directories, restricted deletion flag

    return (const char*)permBuffer;
}

// define fcn pointer for scandir function call
//
static int one(const struct dirent *unused){
    return 1;
}

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

    int count = 0, i;
    DIR * dir = NULL;
    //struct dirent *_file = NULL;
    struct dirent **_files;
    struct stat *_stat;
    struct group _grp;
    struct group *_grpres;
    struct tm *_time;
    char buffer[1024];
    char dateString[256];

    // call opendir on whatever is passed in (i.e. file or directory)
    // we have no idea at the moment
    //
    // dir = opendir(argv[1]);
    _stat = (struct stat *)malloc(sizeof(struct stat));
    _time = (struct tm *)malloc(sizeof(struct tm));

    // scan the given path and sort the contents into 'files' in alphabetical order
    //
    count = scandir(argv[1], &_files, one, alphasort);

    if(count > 0){
        for( i = 0; i < count; ++i){
            if( stat(_files[i]->d_name, _stat) == 0){
                // Print out type, permissions, and number of links
                printf("%10.10s", getPermissions(_stat->st_mode));
                printf(" %d", _stat->st_nlink);
         
               if(!getgrgid_r(_stat->st_gid, &_grp, buffer, sizeof(buffer), &_grpres))
                   printf(" %s", _grp.gr_name);
               else
                   printf(" %d", _stat->st_gid);
           
               // print size of file
               printf(" %5d", (int)_stat->st_size);

               // gets broken-down local time (timezone is handled)
               localtime_r(&_stat->st_mtime, _time);

               // convert date and time to a string
               strftime(dateString, sizeof(dateString), "%F %T", _time);
               printf(" %s %s\n", dateString, _files[i]->d_name); 
           }
           free(_files[i]);
        }
        free(_files);
    }
    closedir(dir);
    free(_stat);
    free(_time);

    return EXIT_SUCCESS;
}
