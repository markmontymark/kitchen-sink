#include "line.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static const size_t line_s  = sizeof(line_t);

line_t * line_new() 
{
	line_t * ptr = malloc(line_s);
	if(ptr == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in line_new: %s\n", (unsigned long)line_s, strerror(errno) );
		return NULL;	
	}	
	ptr->size = 0;
	ptr->data = NULL;
	return ptr;
}


int line_size(line_t * ptr)
{
	return ptr->size;
}


char * line_get(line_t * ptr) 
{
	return ptr->data;
}

void line_set(line_t * ptr, char * data) 
{
	int size = strlen(data) + 1;
	if( (ptr->data = malloc(size)) == NULL)
	{
		perror("line_set");
		return;
	}
	strncpy(ptr->data,data,size);
	char * d = ptr->data;
	ptr->size = size;
	ptr->flags.null_terminated = (size < 2) ? ((*d == '\0') ? 1 : 0) : (( *(d + size - 1 ) == '\0') ? 1 : 0);
	ptr->flags.has_newline = (size < 2) ? ((*d == '\n') ? 1:0) : (( *(d + size - 2) == '\n') ? 1 : 0);
}

unsigned int line_has_newline( line_t * ptr)
{
	return ptr->flags.has_newline;
}

unsigned int line_null_terminated(line_t * ptr)
{
	return ptr->flags.null_terminated;
}


void line_free(line_t * ptr)
{
	if(ptr == NULL)
		return;
	free(ptr->data);
	free(ptr);
}
