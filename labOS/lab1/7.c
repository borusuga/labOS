//
//  7.c
//  labOS
//
//  Created by Alyona Borushnova on 18.10.2023.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    struct stat statbuf = {0};
    stat(argv[1], &statbuf);

    printf("ID of device containing file: %d\n", statbuf.st_dev);
    printf("Inode: %llu\n", statbuf.st_ino);
    printf("File type and mode: %u\n", statbuf.st_mode);
    printf("Number of hard links: %hu\n", statbuf.st_nlink);
    printf("Owner user ID: %u\n", statbuf.st_uid);
    printf("Owner group ID: %u\n", statbuf.st_gid);
    printf("Device ID (if special file): %d\n", statbuf.st_rdev);
    printf("Total size, bytes: %lld\n", statbuf.st_size);
    printf("I/O block size: %d\n", statbuf.st_blksize);
    printf("Blocks: %lld\n", statbuf.st_blocks);
    printf("Time of last access: %ld\n", statbuf.st_atimespec.tv_sec);
    printf("Time of last modification: %ld\n", statbuf.st_mtimespec.tv_sec);
    printf("Time of last status change: %ld\n", statbuf.st_ctimespec.tv_sec);

    return 0;
}
