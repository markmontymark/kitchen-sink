#ifndef __LIBMRK_PROMPT_H_
#define __LIBMRK_PROMPT_H_

/*
	@brief Prompt the user to enter input while not echoing what is typed
	@param char * msg, The prompt string sent to stdout
	@param char * in, The reference where the input is saved
	@returns 0 on success
	@returns non-zero
*/
int prompt_noecho(char * msg,char * in);

/*
	@brief Prompt the user to enter input and echo what is typed
*/
int prompt(char * msg,char * in);

#endif
