/**
 * Exercise 4.2
 * Write a program like `cp` that, when used to copy a regular file
 * that contains holes (sequences of null bytes), also creates corresponding holes in the target file.
 * 
 **/

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int src_fd, tar_fd;
    char *src_fname = NULL;
    char *tar_fname = NULL;
    ssize_t read_len, write_len;
    char *buf = NULL;

    const int bufsize = 512;

    if (argc != 3)
        usageErr("%s <source> <target>\n", argv[0]);

    src_fname = argv[1];
    tar_fname = argv[2];

    src_fd = open(src_fname, O_RDONLY,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH);
    if (src_fd == -1)
        errExit("open source file");

    tar_fd = open(tar_fname, O_WRONLY | O_CREAT,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                    S_IROTH | S_IWOTH);
    if (tar_fd == -1)
        errExit("open source file");

    buf = malloc(bufsize);
    if (buf == NULL)
        errExit("malloc");

    while ((read_len = read(src_fd, buf, bufsize)) > 0) {
        write_len = write(tar_fd, buf, read_len);
        if (write_len == -1)
            errExit("write");
    }

    free(buf);
    if (close(src_fd) == -1)
        errExit("close source");
    if (close(tar_fd) == -1)
        errExit("close target");

    exit(EXIT_SUCCESS);
}