#include <stdio.h>

#include "arraylist_int.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t arraylist_int_s  = sizeof(arraylist_int_t);

#define ARRAYLIST_int_COMPARATOR(a,b) a == b

arraylist_int_t * arraylist_int_new() 
{
	arraylist_int_t * list = malloc(arraylist_int_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_int_new: %s\n", (unsigned long)arraylist_int_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}


int arraylist_int_size(arraylist_int_t * list)
{
	return list->size;
}


void arraylist_int_add(arraylist_int_t * list, int value) 
{
	int ** data;
	int size = arraylist_int_size(list);
	data = realloc(list->data, (size + 1) * sizeof data[0]);

	if(data == NULL)
	{
		fprintf(stderr,"Error realloc'ing size %lu in arralist_int_add: %s\n", (unsigned long)arraylist_int_s, strerror(errno) );
		return;
	}
	int * pvalue = malloc(sizeof(int));
	*pvalue = value;
	data[size] = pvalue;
	list->data = data;
	++list->size;
}

int arraylist_int_get(arraylist_int_t * list, int index) 
{
	if(index < arraylist_int_size(list))
		return *(list->data[index]);
	return 0;
}

int arraylist_int_indexof(arraylist_int_t * list, int value) 
{
	int sz = arraylist_int_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(ARRAYLIST_int_COMPARATOR( *(list->data[i]), value) == 0) 
			return i;
	//if(strcmp(list->data[i], value) == 0) 
	return -1;
}

void arraylist_int_free(arraylist_int_t * list)
{
	if(list == NULL)
		return;
	int sz = arraylist_int_size( list );
	while( --sz > -1 )
		free(list->data[sz]);
	free(list->data);
	free(list);
}
