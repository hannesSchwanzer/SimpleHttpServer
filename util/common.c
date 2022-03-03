#include "common.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_n_die(const char* err_msg, ...) 
{
    int errno_save;
    va_list ap;

    errno_save = errno;

    va_start(ap, err_msg);
    vfprintf(stdout, err_msg, ap);
    fprintf(stdout, "/n");
    fflush(stdout);

    if (errno_save != 0) 
    {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);

    exit(EXIT_FAILURE);
}