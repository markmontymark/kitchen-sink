
#include "run_cmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void run_cmd(char * cmd)
{
	int ret = system(cmd);
	if (WIFSIGNALED(ret) && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT))
	{
		fprintf(stderr,"Failed on %s:  %s",cmd,strerror(errno));
		exit(1);
	}
}

