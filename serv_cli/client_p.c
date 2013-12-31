/*****************************************************************************************
 * PROJECT: Sashe
 * TEAM MEMBERS: Arjun Aletty, Keely Haverstock, Sarah Seko, Sarah Strohkorb
 * 
 * FILE: client01.c
 * 
 * DESCRIPTION:
 * 
*****************************************************************************************/

/*--------------------------------------------------------------------
						GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "serv_cli.h"
#include "send_recieve.c"
#include "error.c"

typedef struct connection {
	FILE *fp;
	int sockfd;	
} Connection;

void transfer_file(Connection *connection, char *sendline)
{
	char *cmnd;
	char *fname;
	fname = (char *)malloc(100 * sizeof(char));
	cmnd = (char *)malloc(100 * sizeof(char));

		/* stores the client request message in the file descriptor sockfd */
	if (Send(connection->sockfd, sendline, strlen(sendline)) != strlen(sendline))
		error_no_exit("written error");
	/* read the input from the server */
	cmnd = strtok(sendline, " ");
	fname = strtok(NULL, " ");
	
	printf("%i,  %s\n", connection->sockfd, fname);
	RecvFile(connection->sockfd, fname);
	printf("I made it\n");

	free(fname);
	free(cmnd);
	exit(0);
}

void make_connection(Connection *connection, char *ip_address)
{
	/*------------------------------------------------------
	Local Variables
	------------------------------------------------------*/
	struct sockaddr_in	servaddr;

	//Connection *connection = (Connection *) malloc(sizeof(Connection));
	//connection->fp = (FILE *) malloc(sizeof(FILE));

	/* creates a socket that is bound to a specific transport service provider */
	if ( (connection->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_no_exit("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	if ( (inet_pton(AF_INET, ip_address, &servaddr.sin_addr)) <= 0)
		error_no_exit("inet_pton error");

	if (connect(connection->sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		error_no_exit("connect error");	
}

void close_connection(Connection *connection)
{
	close(connection->sockfd);
}
	
