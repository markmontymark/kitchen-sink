#ifndef line_H
#define line_H

typedef struct line line_t;
struct line
{
   struct 
	{
      unsigned has_newline : 1;
      unsigned null_terminated : 1;
   } flags;
	int size;
	char * data; // tricky substitution -- data is always a ptr to the type
};

//public api

//ctor w/ malloc & dtor
line_t * line_new();
void	line_free(	line_t * ptr);

int 		line_size(	line_t * ptr);
char * 	line_get(	line_t * ptr);
void 		line_set(	line_t * ptr, char * data);
unsigned int 		line_has_newline(	line_t * ptr);
unsigned int 		line_null_terminated(line_t * ptr);

#endif
