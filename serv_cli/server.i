/* File : server.i */

%module server
%{
/* Headers and other declarations */
#include "serv_cli.h"

%}

extern void str_exec(int connfd);
extern int run_server();

