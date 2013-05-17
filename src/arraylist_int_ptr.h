#ifndef _ARRAYLIST_int_ptr_H
#define _ARRAYLIST_int_ptr_H

#include <stdio.h>

typedef struct arraylist_int_ptr arraylist_int_ptr_t;
struct arraylist_int_ptr
{
	int size;
	int** data; // tricky substitution -- data is always a ptr to the type
};

//ctor w/ malloc
arraylist_int_ptr_t * arraylist_int_ptr_new();

//public api
int 		arraylist_int_ptr_size(		arraylist_int_ptr_t * list);
int* 	arraylist_int_ptr_get(		arraylist_int_ptr_t * list, int index);
void 		arraylist_int_ptr_add(		arraylist_int_ptr_t * list, int* value);
int  		arraylist_int_ptr_indexof(	arraylist_int_ptr_t * list, int* value);
void		arraylist_int_ptr_free(		arraylist_int_ptr_t * list);

#endif
