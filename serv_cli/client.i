/* File : client.i */

%module client
%{
/* Headers and other declarations */
typedef struct connection {
	FILE *fp;
	int sockfd;	
} Connection;

#include "serv_cli.h"

%}

typedef struct connection {
	FILE *fp;
	int sockfd;	
} Connection;

extern void transfer_file(Connection *connection, char *fname);
extern void make_connection(Connection *connection, char *ip_address);
extern void close_connection(Connection *connection);
//extern struct Connection *new_Connection();
//int _(char *ip_address);

