#include "arraylist_int_ptr.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t arraylist_int_ptr_s  = sizeof(arraylist_int_ptr_t);

#define ARRAYLIST_int_ptr_COMPARATOR(a,b) a == b

arraylist_int_ptr_t * arraylist_int_ptr_new() 
{
	arraylist_int_ptr_t * list = malloc(arraylist_int_ptr_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_int_ptr_new: %s\n", (unsigned long)arraylist_int_ptr_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}


int arraylist_int_ptr_size(arraylist_int_ptr_t * list)
{
	return list->size;
}


void arraylist_int_ptr_add(arraylist_int_ptr_t * list, int* value) 
{
	int** data;
	int size = arraylist_int_ptr_size(list);
	data = realloc(list->data, (size + 1) * sizeof data[0]);

	if(data == NULL)
	{
		fprintf(stderr,"Error realloc'ing size %lu in arralist_int_ptr_add: %s\n", (unsigned long)arraylist_int_ptr_s, strerror(errno) );
		return;
	}
	data[size] = value;
	list->data = data;
	++list->size;
}

int* arraylist_int_ptr_get(arraylist_int_ptr_t * list, int index) 
{
	if(index < arraylist_int_ptr_size(list))
		return list->data[index];
	return NULL;
}

int arraylist_int_ptr_indexof(arraylist_int_ptr_t * list, int* value) 
{
	int sz = arraylist_int_ptr_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(ARRAYLIST_int_ptr_COMPARATOR(list->data[i], value) == 0) 
			return i;
	//if(strcmp(list->data[i], value) == 0) 
	return -1;
}

void arraylist_int_ptr_free(arraylist_int_ptr_t * list)
{
	if(list == NULL)
		return;
	free(list->data);
	free(list);
}
