#include "%typeclean%.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"

static const size_t %typeclean%_s  = sizeof(%typeclean%_t);

%typeclean%_t * %typeclean%_new() 
{
	%typeclean%_t * ptr = malloc(%typeclean%_s);
	if(ptr == NULL)
	{
		fprintf(stderr,"Error malloc'ing size %lu in %typeclean%_new: %s\n", (unsigned long)%typeclean%_s, strerror(errno) );
		return NULL;	
	}	
	ptr->size = 0;
	ptr->data = NULL;
	return ptr;
}


int %typeclean%_size(%typeclean%_t * ptr)
{
	return ptr->size;
}


%type% %typeclean%_get(%typeclean%_t * ptr, int index) 
{
	if(index < %typeclean%_size(ptr))
		return ptr->data[index];
	return NULL;
}

void %typeclean%_free(%typeclean%_t * ptr)
{
	if(ptr == NULL)
		return;
	free(ptr->data);
	free(ptr);
}
