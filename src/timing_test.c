
// This file auto-generated on Tue Aug 21 13:50:45 2012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "common.h"

const char * USAGE = "Write a pointer based version of strcat(dest,src)";

void impl( );

char * ptr_strcat (char * dest, const char * src);
char * ptr_strncat(char * dest, const char * src, size_t n);
char * mystrcat(char * dest, char * src) ;
int timeval_subtract (struct timeval * result, struct timeval *x,struct timeval  *y);

int main( int argc, char ** argv )
{
	char * progname = argv[0];
	get_progname(progname);
	usage(USAGE,progname);
	impl();
	return 0;
}

void impl( )
{
	char * src1 = "b";
	char * src2 = "str2";

	char * (*fptr)(char * a,char *b) = mystrcat;	

	struct timespec t1;
	struct timespec t2;
	if(clock_getres(CLOCK_PROCESS_CPUTIME_ID,&t1))
	{
		printf("%s\n",strerror(errno));
	}

	unsigned int times = 1000;		
	int t = timing_char_char(times, fptr, src1, src2);
	printf("mystrcat %d iters = %d seconds\n",times,t);
	clock_getres(CLOCK_REALTIME,&t2);
	printf("timeval %ld, %ld, %ld and %ld = %ld \n", t1.tv_sec, t2.tv_sec,t1.tv_nsec,t2.tv_nsec, (t2.tv_nsec - t1.tv_nsec)/1000);
	
}

int timeval_subtract (struct timeval * result, struct timeval *x,struct timeval  *y)
{
       /* Perform the carry for the later subtraction by updating y. */
       if (x->tv_usec < y->tv_usec) {
         int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
         y->tv_usec -= 1000000 * nsec;
         y->tv_sec += nsec;
       }
       if (x->tv_usec - y->tv_usec > 1000000) {
         int nsec = (x->tv_usec - y->tv_usec) / 1000000;
         y->tv_usec += 1000000 * nsec;
         y->tv_sec -= nsec;
       }
     
       /* Compute the time remaining to wait.
          tv_usec is certainly positive. */
       result->tv_sec = x->tv_sec - y->tv_sec;
       result->tv_usec = x->tv_usec - y->tv_usec;
     
       /* Return 1 if result is negative. */
       return x->tv_sec < y->tv_sec;
}


char * mystrcat(char * dest, char * src) 
{
	printf("in mystrcat\n");
	int dlen = strlen(dest);	
	int slen = strlen(src);	
	char * p = NULL;
	p = malloc(dlen * sizeof(char));
	int i = 0;
	while( *dest != '\0')
	{
		*p++ = *dest++;
		i++;
	}
	dest -= i;
	p -= i;	
	char * t = realloc(p, (dlen+slen) * sizeof(char)  + 1);
   if (t == NULL)
   {
      free(p);
      return NULL;
   }
   p = t;
	p += i;

	while( *p++ = *src++ )
		;

	p -= (dlen+slen+1);
	return p;
}
