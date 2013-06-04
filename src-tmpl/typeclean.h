#ifndef _ARRAYLIST_%typeclean%_H
#define _ARRAYLIST_%typeclean%_H

#include <stdio.h>

typedef struct %typeclean% %typeclean%_t;
struct %typeclean%
{
	int size;
	%type% data; // tricky substitution -- data is always a ptr to the type
};

//public api

//ctor w/ malloc & dtor
%typeclean%_t * %typeclean%_new();
void	%typeclean%_free(	%typeclean%_t * ptr);

int 		%typeclean%_size(	%typeclean%_t * ptr);
%type% 	%typeclean%_get(	%typeclean%_t * ptr);

#endif
