#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[]) {

	struct stat attributes;

	if(argc != 2)
        return 1;
	
	lstat(argv[1],&attributes);
	
    printf("------------------ %s ------------------\n",argv[1]);
	
    printf("%-20s: ", "Access privileges");
    printf( (S_ISDIR(attributes.st_mode)) ? "d" : "-");
    printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    
    printf("%-20s: %ld\n", "inode-Number", attributes.st_ino);
    printf("%-20s: %ld\n", "Device numbers",attributes.st_rdev);
    printf("%-20s: %ld\n", "Links count", attributes.st_nlink);
    printf("%-20s: %u\n", "UID", attributes.st_uid);
    printf("%-20s: %u\n", "GID", attributes.st_gid);
    printf("%-20s: %ld\n", "File Size", attributes.st_size);
    
    printf("%-20s: %s", "Last access",ctime(&attributes.st_atime));
    printf("%-20s: %s", "Last modification",ctime(&attributes.st_mtime));
    printf("%-20s: %s", "Last inode change",ctime(&attributes.st_ctime));

	return 0;	
}
