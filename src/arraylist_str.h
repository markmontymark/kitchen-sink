#ifndef _ARRAYLIST_STR_H
#define _ARRAYLIST_STR_H

#include <stdio.h>

typedef struct arraylist_str arraylist_str_t;
struct arraylist_str
{
	int size;
	char ** data;
};

//ctor w/ malloc
arraylist_str_t * arraylist_str_new();

//public api
int 		arraylist_str_size(		arraylist_str_t * list);
char * 	arraylist_str_get(		arraylist_str_t * list, int index);
void 		arraylist_str_add(		arraylist_str_t * list, char * value);
int  		arraylist_str_indexof(	arraylist_str_t * list, char * value);
void		arraylist_str_free(		arraylist_str_t * list);

#endif
