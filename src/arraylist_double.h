#ifndef _ARRAYLIST_double_H
#define _ARRAYLIST_double_H

typedef struct arraylist_double arraylist_double_t;
struct arraylist_double
{
	int size;
	double** data; // tricky substitution -- data is always a ptr to the type
};

//ctor w/ malloc
arraylist_double_t * arraylist_double_new();

//public api
double 		arraylist_double_size(		arraylist_double_t * list);
double 		arraylist_double_get(		arraylist_double_t * list, int index);
void 			arraylist_double_add(		arraylist_double_t * list, double value);
double  		arraylist_double_indexof(	arraylist_double_t * list, double value);
void			arraylist_double_free(		arraylist_double_t * list);

#endif
