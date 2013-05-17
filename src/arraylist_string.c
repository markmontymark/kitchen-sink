#include "arraylist_string.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t arraylist_string_s  = sizeof(arraylist_string_t);

#define ARRAYLIST_string_COMPARATOR(a,b) strcmp(a,b)

arraylist_string_t * arraylist_string_new() 
{
	arraylist_string_t * list = malloc(arraylist_string_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_string_new: %s\n", (unsigned long)arraylist_string_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}


int arraylist_string_size(arraylist_string_t * list)
{
	return list->size;
}


void arraylist_string_add(arraylist_string_t * list, char* value) 
{
	char** data;
	int size = arraylist_string_size(list);
	data = realloc(list->data, (size + 1) * sizeof data[0]);

	if(data == NULL)
	{
		fprintf(stderr,"Error realloc'ing size %lu in arralist_string_add: %s\n", (unsigned long)arraylist_string_s, strerror(errno) );
		return;
	}
	data[size] = value;
	list->data = data;
	++list->size;
}

char* arraylist_string_get(arraylist_string_t * list, int index) 
{
	if(index < arraylist_string_size(list))
		return list->data[index];
	return NULL;
}

int arraylist_string_indexof(arraylist_string_t * list, char* value) 
{
	int sz = arraylist_string_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(ARRAYLIST_string_COMPARATOR(list->data[i], value) == 0) 
			return i;
	//if(strcmp(list->data[i], value) == 0) 
	return -1;
}

void arraylist_string_free(arraylist_string_t * list)
{
	if(list == NULL)
		return;
	free(list->data);
	free(list);
}
