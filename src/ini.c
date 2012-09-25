#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ini.h"

#define DEBUG 0

struct token_positions
{
	int n_tokens;
	int positions[3];// 0 == '[', 1 == ']', 2 == '='
};

static void chomp(char * line)
{
	int len = strlen(line);
	if( *(line+len-1) == '\n')
		*(line+len-1) = '\0';
}

static void init_token_positions( struct token_positions * tp)
{
	for(int i = 0 ; i < tp->n_tokens; i++ )
		tp->positions[i] = -1;
}

static void get_token_positions( struct token_positions * tp, char * line)
{
	init_token_positions(tp);
	char * s = line;
	for(int i = 0; *s; *++s,++i)
	{	
		switch(*s)
		{
			case '[':
				tp->positions[0] = i;
				break;
			case ']':
				tp->positions[1] = i;
				break;

			case '=':
				tp->positions[2] = i;
				return; // if we find = we just break out entirely
		}
	}
}

static int ini_add_from_line(ini_t * ini, char * line)
{
	chomp(line);
	if(strlen(line) == 0)
		return 0;

	if(DEBUG) printf("line: %s\n",line);

	int n_found = 0;
	struct token_positions * tp = malloc(sizeof(struct token_positions));
	tp->n_tokens = 3;
	get_token_positions(tp,line);
	if( tp->positions[2] != -1)
	{
		if(DEBUG)
			printf("found key,val\n");
		char * key = strndup(line,tp->positions[2]);
		char * val = strdup(line+tp->positions[2]+1);
		hash_table_add(ini->cfg,key,strlen(key)+1,val,strlen(val)+1);
		if(DEBUG)
			printf("%s = %s\n",key,val);
	}
	else if( tp->positions[0] != -1 && tp->positions[1] != -1)
	{
		if(DEBUG)
			printf("found section key\n");
		hash_table_add(ini->cfg,strdup(line),strlen(line)+1,hash_table_new(MODE_COPY),sizeof(hash_table_t *));
	}
	else
	{
		if(DEBUG)
			printf("found a flag\n");
		int val = 1;
		hash_table_add(ini->cfg,line,strlen(line)+1,&val,sizeof(val));
	}
	free(tp);
	return 0;
}

static int _parse_file( ini_t * ini)
{
	FILE * f;
	f = fopen(ini->path,"rb");
	char buf[1024];
	while	(fgets(buf,1024,f)!= NULL)
	{
		ini_add_from_line(ini,buf);
	}
	return 0;	
}


ini_t * ini_new()
{
	ini_t * i = malloc( sizeof(ini_t) );
	//TODO add malloc failure test
	i->path = malloc( sizeof(char *) + 1);
	i->cfg = hash_table_new(MODE_VALUEREF);
	return i;
}


ini_t * ini_new_from_path(char * path)
{
	ini_t * ini = ini_new();
	ini->path = strdup(path);
	_parse_file( ini );
	return ini;
}


void ini_free(ini_t * ini)
{
	if(ini == NULL)
		return;
	if(ini->path != NULL)
		free(ini->path);
	if(ini->cfg != NULL)
		hash_table_delete( ini->cfg);	
	free( ini );
}

int ini_has(ini_t * ini, char * name)
{
	return 0;
}


int ini_add(ini_t * ini, char * key,char * val)
{
}


char * ini_get(ini_t * ini, char * name)
{
	return name;
}

void ini_dump_for_each( void * key , void * val)
{
	printf("in ini_dump_for_each with key %s = %s\n", (char *) key, (char *)val);
	if( ((char *)val) == NULL)
		printf("	val is null\n");
}

void ini_dump( ini_t * ini, FILE * fp)
{
	hash_table_iterate( ini->cfg, ini_dump_for_each );		
}


