#include <stdio.h>
#include "ini.h"

void ini_example(char * path);

int main(int argc, char ** argv)
{
	while(--argc > 0)
		ini_example(*++argv);
	return 0;
}

void ini_example(char * path)
{
	ini_t * ini = ini_new_from_path(path);
	ini_dump( ini, stdout);
}
