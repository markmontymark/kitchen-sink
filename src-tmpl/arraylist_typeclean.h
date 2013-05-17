#ifndef _ARRAYLIST_%typeclean%_H
#define _ARRAYLIST_%typeclean%_H

#include <stdio.h>

typedef struct arraylist_str arraylist_%typeclean%_t;
struct arraylist_str
{
	int size;
	%type%* data; // tricky substitution -- data is always a ptr to the type
};

//ctor w/ malloc
arraylist_%typeclean%_t * arraylist_%typeclean%_new();

//public api
int 		arraylist_%typeclean%_size(		arraylist_%typeclean%_t * list);
%type% 	arraylist_%typeclean%_get(		arraylist_%typeclean%_t * list, int index);
void 		arraylist_%typeclean%_add(		arraylist_%typeclean%_t * list, %type% value);
int  		arraylist_%typeclean%_indexof(	arraylist_%typeclean%_t * list, %type% value);
void		arraylist_%typeclean%_free(		arraylist_%typeclean%_t * list);

#endif
