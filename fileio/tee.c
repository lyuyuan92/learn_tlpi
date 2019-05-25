/**
 * Exercise 4.1
 * The tee command reads its standard input until end-of-file,
 * Writeing a copy of the input to standard output and to
 * the file named in its command-line argument. Implement tee
 * using I/O system calls. By default, tee overwrites any
 * existing file with the given name. Implement the -a command-line
 * option (tee -a file), which causes tee to append text to
 * the end of a file if it already exists.
 * 
 **/

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd, opt, index;
    char *line = NULL;
    char *fname = NULL;
    ssize_t read, written;
    size_t len = 0;
    Boolean append = FALSE;
    if (argc > 3 || argc == 2 && strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    while ((opt = getopt(argc, argv, "a:")) != -1) {
        switch (opt)
        {
        case 'a':
            append = TRUE;
            fname = optarg;
            break;

        default:
            errExit("Invalid command line arguments.");
        }
    }

    for (index = optind; index < argc; index++)
        fname = argv[optind];

    int flag = O_RDWR | O_CREAT;
    if (append)
        flag = flag | O_APPEND;

    fd = open(fname, flag,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);
    if (fd == -1)
        errExit("open");
    
    while ((read = getline(&line, &len, stdin)) != -1) {
        fprintf(stdout, "%s", line);
        if (fd) {
            written = write(fd, line, read);
        }
    }

    if (close(fd) == -1)
        errExit("close");

    free(line);
    exit(EXIT_SUCCESS);
}
