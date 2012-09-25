#include "prompt.h"

#include <stdio.h>
#include <stdlib.h>

int prompt_noecho(char * msg,char * in)
{
   printf("%s",msg);
   system("stty -echo");
   fscanf(stdin,"%s",in);
   system("stty echo");
   printf("\n");
}

int prompt(char * msg,char * in)
{
   printf("%s",msg);
   fscanf(stdin,"%s",in);
}

