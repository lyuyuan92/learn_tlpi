/**
 * Exercise 6.1
 * Compile the program in Listing 6-1 and list its size using ls -l.
 * Although the program contains an array that is around 10 MB size,
 * the executable file is much smaller than this. Why?
 * 
 **/

#include <stdio.h>
#include <stdlib.h>

char globBUf[65536];
int primes[] = {2, 3, 5, 7};

static int
square(int x)
{
    int result;

    result = x * x;
    return result;
}

static void
doCalc(int val)
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char *argv[])
{
    static int key = 9973;
    static char mbuf[10240000];
    char *p;

    p = malloc(1024);
    
    doCalc(key);

    exit(EXIT_SUCCESS);
}

/**
 * Answer:
 * Since the array mbuf is not initialized, it is part of the uninitialized data segment.
 * Therefore, no disk space is required to hold this variable. Instead, it is allocated
 * when the program is loaded.
 * 
 **/