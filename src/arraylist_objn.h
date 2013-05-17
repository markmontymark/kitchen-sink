#ifndef _ARRAYLIST_objn_H
#define _ARRAYLIST_objn_H

#include <stdio.h>
#include "objn.h"

typedef struct arraylist_objn arraylist_objn_t;
struct arraylist_objn
{
	int size;
	objn_t ** data; // tricky substitution -- data is always a ptr to the type
};

//ctor w/ malloc
arraylist_objn_t * arraylist_objn_new();

//public api
int 		arraylist_objn_size(		arraylist_objn_t * list);
objn_t *	arraylist_objn_get(		arraylist_objn_t * list, int index);
void 		arraylist_objn_add(		arraylist_objn_t * list, objn_t * value);
int  		arraylist_objn_indexof(	arraylist_objn_t * list, objn_t * value);
void		arraylist_objn_free(		arraylist_objn_t * list);

#endif
