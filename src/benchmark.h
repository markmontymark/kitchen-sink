#ifndef __LIBMRK_BENCHMARK_H_
#define __LIBMRK_BENCHMARK_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

int benchmark( void * func, char * arg1, char * arg2);
int benchmark_char_char(unsigned int times,char *(*fptr)(char *,char*), char *, char *);

#endif
