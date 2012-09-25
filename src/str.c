#ifndef __KITCHENSINK_STR_H_
#define __KITCHENSINK_STR_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "str.h"

char * str_chomp(char * line)
{
   if( line == NULL ||
	   *(line+(strlen(line)-1)) != '\n')
      return line;

	char * retval = strdup(line);
   *(retval+(strlen(retval)-1)) = '\0';
   return retval;
}

char * str_substring(char * text , int start, int stop)
{
   //printf("substring in %d %d %s, strlen = %d\n",start,stop,text,strlen(text));
	char * retval = malloc(stop - start + 1);
   snprintf(retval,strlen(text),"%.*s",stop-start,text+start);
   //printf("substring out %s\n",text);
   return retval;
}

int str_indexof(char * text,char delim)
{
   if(text == NULL)
      return -1;
   char * s = text;
   for( int i = 0; *s; i++)
      if(s[i] == delim)
         return i;
   return -1;
}

#endif
