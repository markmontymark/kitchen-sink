#include "arraylist_objn.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"
#include "objn.h"

static const size_t arraylist_objn_s  = sizeof(arraylist_objn_t);

#define ARRAYLIST_objn_COMPARATOR(a,b) objn_compare(a,b)

arraylist_objn_t * arraylist_objn_new() 
{
	arraylist_objn_t * list = malloc(arraylist_objn_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_objn_new: %s\n", (unsigned long)arraylist_objn_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}


int arraylist_objn_size(arraylist_objn_t * list)
{
	return list->size;
}


void arraylist_objn_add(arraylist_objn_t * list, objn_t * value) 
{
	objn_t ** data;
	int size = arraylist_objn_size(list);
	data = realloc(list->data, (size + 1) * sizeof data[0]);

	if(data == NULL)
	{
		fprintf(stderr,"Error realloc'ing size %lu in arralist_objn_add: %s\n", (unsigned long)arraylist_objn_s, strerror(errno) );
		return;
	}
	data[size] = value;
	list->data = data;
	++list->size;
}

objn_t * arraylist_objn_get(arraylist_objn_t * list, int index) 
{
	if(index < arraylist_objn_size(list))
		return list->data[index];
	return NULL;
}

int arraylist_objn_indexof(arraylist_objn_t * list, objn_t * value) 
{
	int sz = arraylist_objn_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(ARRAYLIST_objn_COMPARATOR(list->data[i], value) == 0) 
			return i;
	//if(strcmp(list->data[i], value) == 0) 
	return -1;
}

void arraylist_objn_free(arraylist_objn_t * list)
{
	if(list == NULL)
		return;
	free(list->data);
	free(list);
}
