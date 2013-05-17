#include "arraylist_%typeclean%.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t arraylist_%typeclean%_s  = sizeof(arraylist_%typeclean%_t);

#define ARRAYLIST_%TYPECLEAN%_COMPARATOR(a,b) strcmp(a,b)

arraylist_%typeclean%_t * arraylist_%typeclean%_new() 
{
	arraylist_%typeclean%_t * list = malloc(arraylist_%typeclean%_s);
	if(list == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in arralist_%typeclean%_new: %s\n", (unsigned long)arraylist_%typeclean%_s, strerror(errno) );
		return NULL;	
	}	
	list->size = 0;
	list->data = NULL;
	return list;
}


int arraylist_%typeclean%_size(arraylist_%typeclean%_t * list)
{
	return list->size;
}


void arraylist_%typeclean%_add(arraylist_%typeclean%_t * list, %type% value) 
{
	%type%* data;
	int size = arraylist_%typeclean%_size(list);
	data = realloc(list->data, (size + 1) * sizeof data[0]);

	if(data == NULL)
	{
		fprintf(stderr,"Error realloc'ing size %lu in arralist_%typeclean%_add: %s\n", (unsigned long)arraylist_%typeclean%_s, strerror(errno) );
		return;
	}
	data[size] = value;
	list->data = data;
	++list->size;
}

%type% arraylist_%typeclean%_get(arraylist_%typeclean%_t * list, int index) 
{
	if(index < arraylist_%typeclean%_size(list))
		return list->data[index];
	return NULL;
}

int arraylist_%typeclean%_indexof(arraylist_%typeclean%_t * list, %type% value) 
{
	int sz = arraylist_%typeclean%_size( list );
	for(int i = 0; i != sz; i++ ) 
		if(ARRAYLIST_%TYPECLEAN%_COMPARATOR(list->data[i], value) == 0) 
			return i;
	//if(strcmp(list->data[i], value) == 0) 
	return -1;
}

void arraylist_%typeclean%_free(arraylist_%typeclean%_t * list)
{
	if(list == NULL)
		return;
	free(list->data);
	free(list);
}
