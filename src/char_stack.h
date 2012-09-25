#include <stdio.h>
#include <stdlib.h>

#ifndef __CHAR_STACK_H_
#define __CHAR_STACK_H_

struct char_stack
{
   char c;
   struct char_stack * next;
};

struct char_stack * char_stack_init();
void char_stack_free(struct char_stack * cs);
void char_stack_dump(struct char_stack * cs,FILE * fp);
struct char_stack * char_stack_push( struct char_stack *cs,char c);
struct char_stack * char_stack_pop( struct char_stack *cs);
int char_stack_is_empty( struct char_stack * cs);

#endif
