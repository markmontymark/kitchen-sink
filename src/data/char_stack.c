#include <stdio.h>
#include <stdlib.h>

#include "char_stack.h"

char_stack_t *
char_stack_init()
{
	char_stack_t * nextEntry = malloc(char_stack_s);
	nextEntry->c = '\0';
	nextEntry->next = NULL;
	return nextEntry;
}

void char_stack_free(char_stack_t  * cs)
{
	char_stack_t * tmp;
	while(cs != NULL)
	{
		tmp = cs;
		cs = cs->next;
		free(tmp);
	}
	free(cs);
}

void char_stack_dump(char_stack_t * cs,FILE * fp)
{
	char_stack_t * tmp;
	while(cs != NULL)
	{
		fprintf(fp,"stack: %c, %p\n",cs->c,cs);
		cs = cs->next;
	}
}

char_stack_t * 
char_stack_push( char_stack_t * cs,char c)
{
	char_stack_t * nextEntry = malloc(char_stack_s);
	nextEntry->c = c;
	nextEntry->next = cs;
	return nextEntry;
}

char_stack_t * char_stack_pop( char_stack_t * cs)
{
	char_stack_t * tmp;
	tmp = cs;
	cs = cs->next;	
	free(tmp);
	return cs;
}

int char_stack_is_empty( char_stack_t * cs)
{
	if(cs == NULL)
		return 1;
   return cs->next == NULL ? 1 : 0;
}

int char_stack_test( int argc, char ** argv )
{
	char_stack_t * stack = char_stack_init();
	printf("initial char_stack root is empty? %s\n",
		char_stack_is_empty( stack ) ? "yes" : "no");

	printf("stack bfore push %p, val is %c\n",stack,stack->c);
	stack = char_stack_push( stack, 'c');
	stack = char_stack_push( stack, 'd');
	char_stack_dump( stack,stdout );
	printf("stack after push %p, val is %c\n",stack,stack->c);
	stack = char_stack_pop( stack);
	printf("stack after pop %p, popped val is %c\n",stack,stack->c);
	stack = char_stack_pop( stack);
	//printf("pushed a char to %%p, is empty? %s\n",
		//char_stack_is_empty( stack ) ? "yes" : "no");
	char_stack_dump( stack,stdout );
	char_stack_free(stack);
   return 0;
}
