/**
* @file script.h
* @brief A set of functionality for writing scripts
* @author Mark Koopman
*/

#ifndef __SCRIPT_H_
#define __SCRIPT_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#include "cfg.h"

typedef struct script script_t;

struct script
{
	int has_rcfile;
	char * progname;
	char * usage;
	char * rcfile;
	cfg_t * cfg;
};
#define script_sz sizeof(script_t)

script_t * script_new(char * argv_0, char * usage);
void script_dump_rcfile(script_t * script, FILE * fp);
void script_free(script_t * script);
char * script_config(script_t * script,char * key, char * defaultValue);

#endif
