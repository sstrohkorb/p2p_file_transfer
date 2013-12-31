/*****************************************************************************************
 * PROJECT: Sashe
 * TEAM MEMBERS: Arjun Aletty, Keely Haverstock, Sarah Seko, Sarah Strohkorb
 * 
 * FILE: error.c
 * 
 * DESCRIPTION: Provides error functions for errors that we want to cause an exit for and
 * 	those that we only want to provide a warning for, and not exit out of the 
 * 	server/client. 
 * 
*****************************************************************************************/

/*--------------------------------------------------------------------
						GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "serv_cli.h"

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

void error_no_exit(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}
