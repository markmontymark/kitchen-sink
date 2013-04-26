#include <stdio.h>
#include <stdlib.h>

#ifndef __CHAR_STACK_H_
#define __CHAR_STACK_H_

typedef struct char_stack char_stack_t;
struct char_stack
{
   char c;
   char_stack_t * next;
};
#define char_stack_s sizeof(char_stack_t)

char_stack_t char_stack_init();
char_stack_t char_stack_push( char_stack_t * cs,char c);
char_stack_t char_stack_pop(  char_stack_t * cs);
int    char_stack_is_empty( char_stack_t * cs);
void   char_stack_free(char_stack_t * cs);
void   char_stack_dump(char_stack_t * cs, FILE * fp);

#endif
