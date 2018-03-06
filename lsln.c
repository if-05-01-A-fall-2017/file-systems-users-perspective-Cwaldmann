#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h> 

char* getPremissionOfFile(mode_t mode);
char getShortOfFile(mode_t mode);

int list_dir(const char* dirname)
{
    struct dirent* current_directory;
    struct stat my_stat;
    struct tm lt;  
    struct passwd *pwd;

    DIR* directory = opendir(dirname);

    if(directory == NULL)
        return 0;

    printf("%s\n", dirname);
    printf("\n");

    current_directory = readdir(directory);
    while(current_directory)
    {
        stat(current_directory->d_name, &my_stat);  

        if (!stat(current_directory->d_name, &my_stat))
            pwd = getpwuid(my_stat.st_uid);

        time_t t = my_stat.st_mtime;
        localtime_r(&t, &lt);
        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%c", &lt);
        if (pwd && current_directory->d_name[0] != '.')
            printf("%s \t %c \t %s \t %ld \t %s \t %s", getPremissionOfFile(my_stat.st_mode), getShortOfFile(my_stat.st_mode),pwd->pw_name, (long)my_stat.st_size, timebuf, current_directory->d_name);
        else
            printf("%d \t %ld \t %s \t %s", my_stat.st_uid, (long)my_stat.st_size, timebuf, current_directory->d_name);
        printf("\n");
        current_directory = readdir(directory);
    }
    closedir(directory);
    return 0; 
}

int main(int argc, char* argv[])
{
    if ( argc == 1 )
        return list_dir (".");
    return list_dir(argv[1]);
}

char* getPremissionOfFile(mode_t mode)
{   
    char* prems = (char*)malloc(sizeof(char)*10);
    prems[0] = mode & S_IRUSR ? 'r' : '-';
    prems[1] = mode & S_IWUSR ? 'w' : '-';
    prems[2] = mode & S_IXUSR ? 'x' : '-';
    prems[3] = mode & S_IRGRP ? 'r' : '-';
    prems[4] = mode & S_IWGRP ? 'w' : '-';
    prems[5] = mode & S_IXGRP ? 'x' : '-';
    prems[6] = mode & S_IROTH ? 'r' : '-';
    prems[7] = mode & S_IWOTH ? 'w' : '-';
    prems[8] = mode & S_IXOTH ? 'x' : '-';
    prems[9] = '\0';
    return prems;
}
char getShortOfFile(mode_t mode)
{
    switch (mode & S_IFMT) {
        case S_IFREG:
            return '-';
        case S_IFDIR:
            return 'd';
        case S_IFCHR:
            return 'c';
        case S_IFBLK:
            return 'b';
        case S_IFLNK:
            return 'l';
        case S_IFIFO:
            return 'f';
        case S_IFSOCK:
            return 's';
    }
    return '?';
}
