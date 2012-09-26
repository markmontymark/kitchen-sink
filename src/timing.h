/**
* @file timing.h
* @brief A set of functions to help time functions
* @author Mark Koopman
*/

#ifndef __LIBMRK_timing_H_
#define __LIBMRK_timing_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

/**
* timing a function that takes two char * args
* @param func Function to time
* @param arg1 First char * arg to function to be timed
* @param arg2 Second char * arg to function to be timed
* @returns The time in seconds it took to run func
*/
int timing( void * func, char * arg1, char * arg2);

/**
* timing a function that takes two char * args and return a char *
* @param times The number of times to call function
* @param func Function to time, takes two char * as args
* @param arg1 First char * arg to function to be timed
* @param arg2 First char * arg to function to be timed
* @returns The time in seconds it took to run func
*/
int timing_char_char(unsigned int times,char *(*func)(char *,char*), char * arg1, char * arg2);

#endif
