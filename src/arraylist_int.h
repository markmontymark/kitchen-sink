#ifndef _ARRAYLIST_int_H
#define _ARRAYLIST_int_H

typedef struct arraylist_int arraylist_int_t;
struct arraylist_int
{
	int size;
	int** data; // tricky substitution -- data is always a ptr to the type
};

//ctor w/ malloc
arraylist_int_t * arraylist_int_new();

//public api
int 		arraylist_int_size(		arraylist_int_t * list);
int 		arraylist_int_get(		arraylist_int_t * list, int index);
void 		arraylist_int_add(		arraylist_int_t * list, int value);
int  		arraylist_int_indexof(	arraylist_int_t * list, int value);
void		arraylist_int_free(		arraylist_int_t * list);

#endif
