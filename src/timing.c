
// This file auto-generated on Wed Aug 15 07:52:40 2012_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#include "benchmark.h"

int benchmark( void * func, char * arg1, char * arg2)
{
	printf("in benchmark\n");
	for(int i = 0; i < 100; i++)
		(*func)(arg1,arg2);

	printf("out benchmark\n");
	return 0;
}

int benchmark_char_char(unsigned int times, char *(*func)(char *,char*), char * a, char * b)
{
	if(times == 0)
		return 0;
		
	time_t t1,t2;
	(void) time(&t1);
	int retval = 0;
	while( times-- )
		(*func)(a,b);
	(void) time(&t2);
	return (int) t2-t1;
}

