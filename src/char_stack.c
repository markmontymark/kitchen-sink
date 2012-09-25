#include <stdio.h>
#include <stdlib.h>

#include "char_stack.h"

struct char_stack * 
char_stack_init()
{
	struct char_stack * nextEntry = malloc(sizeof(struct char_stack));
	nextEntry->c = '\0';
	nextEntry->next = NULL;
	return nextEntry;
}

void char_stack_free(struct char_stack * cs)
{
	struct char_stack * tmp;
	while(cs != NULL)
	{
		tmp = cs;
		cs = cs->next;
		free(tmp);
	}
	free(cs);
}

void char_stack_dump(struct char_stack * cs,FILE * fp)
{
	struct char_stack * tmp;
	while(cs != NULL)
	{
		fprintf(fp,"stack: %c, %p\n",cs->c,cs);
		cs = cs->next;
	}
}

struct char_stack * 
char_stack_push( struct char_stack *cs,char c)
{
	struct char_stack * nextEntry = malloc(sizeof(struct char_stack));
	nextEntry->c = c;
	nextEntry->next = cs;
	return nextEntry;
}

struct char_stack * char_stack_pop( struct char_stack * cs)
{
	struct char_stack * tmp;
	tmp = cs;
	cs = cs->next;	
	free(tmp);
	return cs;
}

int char_stack_is_empty( struct char_stack * cs)
{
	if(cs == NULL)
		return 1;
   return cs->next == NULL ? 1 : 0;
}

int char_stack_test( int argc, char ** argv )
{
	struct char_stack * stack = char_stack_init();
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
