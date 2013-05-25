#include <stdio.h>

#include "arraylist_double.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t arraylist_double_s  = sizeof(arraylist_double_t);

#define ARRAYLIST_double_COMPARATOR(a,b) a == b

arraylist_double_t * arraylist_double_new() 
{
	arraylist_double_t * list = malloc(arraylist_double_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_double_new: %s\n", (unsigned long)arraylist_double_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}


double arraylist_double_size(arraylist_double_t * list)
{
	return list->size;
}


void arraylist_double_add(arraylist_double_t * list, double value) 
{
	double ** data;
	int size = arraylist_double_size(list);
	data = realloc(list->data, (size + 1) * sizeof data[0]);

	if(data == NULL)
	{
		fprintf(stderr,"Error realloc'ing size %lu in arralist_double_add: %s\n", (unsigned long)arraylist_double_s, strerror(errno) );
		return;
	}
	double * pvalue = malloc(sizeof(double));
	*pvalue = value;
	data[size] = pvalue;
	list->data = data;
	++list->size;
}

double arraylist_double_get(arraylist_double_t * list, int index) 
{
	if(index < arraylist_double_size(list))
		return *(list->data[index]);
	return 0;
}

double arraylist_double_indexof(arraylist_double_t * list, double value) 
{
	int sz = arraylist_double_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(ARRAYLIST_double_COMPARATOR( *(list->data[i]), value) == 0) 
			return i;
	//if(strcmp(list->data[i], value) == 0) 
	return -1;
}

void arraylist_double_free(arraylist_double_t * list)
{
	if(list == NULL)
		return;
	int sz = arraylist_double_size( list );
	while( --sz > -1 )
		free(list->data[sz]);
	free(list->data);
	free(list);
}
