#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <time.h> // necessary to print times

void main(int argc, char *argv[]) {
    struct stat fileAttributes;

    printf("Inode number: %ld\n", fileAttributes.st_ino);
    printf("File size: %ld bytes\n", fileAttributes.st_size);
    printf("Blocks: %ld\n", fileAttributes.st_blocks);
    
    // File permissions
    printf("File permissions: ");
    printf((S_ISDIR(fileAttributes.st_mode)) ? "d" : "-");
    printf((fileAttributes.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileAttributes.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileAttributes.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileAttributes.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileAttributes.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileAttributes.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileAttributes.st_mode & S_IROTH) ? "r" : "-");
    printf((fileAttributes.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileAttributes.st_mode & S_IXOTH) ? "x\n" : "-\n");

    printf("User ID: %d\n", fileAttributes.st_uid);
    printf("Time of last access: %s", ctime(&fileAttributes.st_atime));
    printf("Time of last data modification: %s", ctime(&fileAttributes.st_mtime));
    printf("Last status change time: %s", ctime(&fileAttributes.st_ctime));

}
