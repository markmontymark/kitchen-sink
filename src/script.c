
/**
* @file script.c
* @brief A set of functionality for writing scripts
* @author Mark Koopman
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "script.h"

//TODO
// Add creating ~/.&lt;name&gt;/ per-user directory to log, create data from repeated use
//

/**
* Return the env setting for HOME
* @returns char * of HOME env setting, or NULL if no HOME is set
*/
static char * script_get_home_dir()
{
	return getenv("HOME");
}

/**
* Chop up argv[0] from main to get name of program, which is used for naming/looking up .&lt;name&gt;rc files, creating .&lt;name&gt;/ directories
* @param path Pass in argv[0] from main  
* @returns void, argv[0] is changed in place
*/
static char * script_get_progname(char * path)
{
   char * pathcopy = strdup(path);
   char * retval = malloc(strlen(pathcopy)+1);
   int tries = 3;
   while( --tries && (retval = rindex(pathcopy,'/')) != NULL)
      pathcopy = strcpy(pathcopy,retval+1);
}

/**
* Read arbitrarily long lines
* @param dest Destination pointer to pointer to char for line
* @param realloc_size Int to hold number of bytes to grow read in line
* @param fp Opened file pointer to read from
* @returns -1 on EOF or error
* @returns 0 Successful read, empty line
* @returns N Successful read, line has N chars
*/
static int read_line(char ** dest, int realloc_size, FILE *fp) 
{
	char *t=NULL, *p=NULL;
	int c; /* character buffer */
	int len = 0; /* current number of elements read and stored */
	int allocated = 0; /* number of allocated bytes in p */

	p = malloc(realloc_size);
	if(p == NULL)
		return -1;

	allocated = realloc_size;

	while( 
		(c = fgetc(fp)) != EOF 
		&& c != '\n'
	)
	{
		if(len == allocated) 
		{
			t = realloc(p, allocated + realloc_size);
			if (t == NULL)
			{
				free(p);
				return -1;
			}
			p = t;
			allocated += realloc_size;
		}
		p[len++] = (char) c;
	}
	if(len == 0) 
	{
		if(c == EOF) 
		{
			free(p);
			return -1;
		} 
		else 
		{
			assert(c == '\n');
			p[0] = '\0';
			*dest = p;
			return 0;
		}
	}

	if( (len + 1) != allocated) 
	{
		t = realloc(p, len+1);
		if (t == NULL) 
		{
			if(p)
				free(p);
			return -1;
		}
		p = t;
	}

	p[len] = '\0';
	*dest = p;
	return len;
}



/**
* Read simple key=value pairs from an optional rc file for your script
* @param script The script_t object
* @returns 0 on unsuccessful open/read of script->rcfile
* @returns 1 on successful read & parsing of script->rcfile
*/
static int script_read_rcfile(script_t * script)
{
	FILE * fp;
	fp = fopen(script->rcfile,"rb");
	if( ! fp )
	{
		printf("Can't open file %s. %s", script->rcfile,strerror(errno));
		return 0;
	}

	char *line[1];
	char * delim = "=";
	hash_table_t * cfg = hash_table_new(MODE_COPY);
	script->cfg = cfg;

	while( read_line(line,1024,fp) != -1)
	{
		if(**line == '#')
			continue;

		char * key = strtok(*line,delim);
		char * val = NULL;
		val = strtok( NULL, delim );
		if( val == NULL )
		{
			hash_table_add(cfg,key,strlen(key)+1, "\0",1);
			continue;
		}

		if( *val == '~')
		{
			*val++;
			char refval[1024];
			if( *val == '/')
				snprintf(refval,1024,"%s%s",script_get_home_dir(),val);
			else
				snprintf(refval,1024,"%s/%s",script_get_home_dir(),val);
			hash_table_add(cfg,key,strlen(key)+1, refval,strlen(refval)+1);
		}
		else
			hash_table_add(cfg,key,strlen(key)+1, val,strlen(val)+1);

	}
	fclose(fp);
	return 1;	
}

/**
* Set a script_t's char * rcfile if a file stat of path is successful
* @param script The script_t object
* @param path A char * for a path to invoke stat() on to see if it exists
* @returns 0 on unsuccessful stat of path
* @returns 1 on successful stat of path
*/
static int set_rcfile(script_t * script, char * path)
{
	struct stat st;
	if( stat(path,&st) )
		return 0;
	script->rcfile = strdup(path);
	return 1;
}


/**
* Try various locations to see if an rcfile is present.  The search stops once an rcfile is found
* @param script The script_t object
* @returns 0 on no rcfile read in
* @returns 1 on successfully reading an rcfile
*/
static int get_rcfile(script_t * script)
{
	char rcpath[1024];

	snprintf(rcpath, 1024, "%s/.scriptrc", script_get_home_dir());
	if(set_rcfile(script,rcpath))
		return script_read_rcfile(script);

	snprintf(rcpath,1024,"%s/.%src",script_get_home_dir(),script->progname);
	if(set_rcfile(script,rcpath))
		return script_read_rcfile(script);

	snprintf(rcpath,1024, "%s/%src", getenv("SCRIPT_HOME"), script->progname);
	if(set_rcfile(script,rcpath))
		return script_read_rcfile(script);

	return 0;
}

/**
* Initialize a script by letting it find its name and read its rc file
* @param name A string from argv[0] to determine name of program, which is used to determine which .&lt;prog&gt;rc file to read for script options
* @param usage A string describing command line options for your script 
* @returns a newly malloc'd script_t *
*/
script_t * script_new(char * name,char * usage)
{
	script_get_progname(name);
	script_t * script = malloc(script_sz);
	script->progname = strdup(name);
	script->usage = strdup(usage);
	script->has_rcfile = get_rcfile(script);
	return script;
}

/**
* Free script_t * object
* @param script one pointer to script_t
* @returns void
*/
void script_free(script_t * script)
{
	if(script->has_rcfile)
		hash_table_delete(script->cfg);
	free(script->progname);	
	free(script->usage);	
	free(script->rcfile);	
	free(script);
}


/**
* Get a configuration from your script's rc file
* @param script The script_t object
* @param key The configuration key to lookup
* @param defaultValue A default value to return if the lookup fails
* @returns defaultValue if script doesn't have an rcfile to run a lookup on
* @returns defaultValue if script's rcfile didn't have key in its lookup
* @returns char * val for a successful lookup of key
*/
char * script_config(script_t * script, char * key, char * defaultValue)
{
	if( ! script->has_rcfile)
		return defaultValue;
	char * val = hash_table_lookup(script->cfg,key,strlen(key)+1);
	if(val == NULL)
		return defaultValue;
	return val;
}


/**
* Print the script's usage message to stdout
* @param script The script_t object
* @returns void
*/
void script_usage(script_t * script)
{
	printf("\
%s\n\
%s\n\
rc file: %s\n",
		script->progname,
		script->usage,
		script->has_rcfile ? script->rcfile : "None"
	);
}

/**
* Print out all rcfile options parsed by script_get_rcfile
* @param script The script_t object
* @param fp A file pointer to print out to
* @returns void
*/
void script_dump_rcfile(script_t * script,FILE * fp)
{
	fprintf(fp,"%s\nrcfile %s\n",
		script->progname,
		script->has_rcfile ?  script->rcfile : "None");

	if(script->has_rcfile)
		hash_table_dump(script->cfg,fp);
		
}
