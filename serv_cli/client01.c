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


void client_exec(FILE *fp, int sockfd, char *fname)
{
	/*------------------------------------------------------
	Local Variables
	------------------------------------------------------*/
	char	sendline[MAXLINE], recvline[MAXLINE];
	char *cmnd = "download ";
	printf("executing client processing\n");
	/* sends a message to the server if there is user input */ 
	printf("client input: %s\n", sendline);
	printf("sockfd: %i\n", sockfd);

	strcpy(sendline, cmnd);
	strcat(sendline, fname);

	/* stores the client request message in the file descriptor sockfd */
	if (Send(sockfd, sendline, strlen(sendline)) != strlen(sendline))
		error_no_exit("written error");

	printf("sent command to server\n");

	/* read the input from the server */
	//cmnd = strtok(sendline, " ");
	//fname = strtok(NULL, " ");

	if (strcmp(cmnd, "download ") == 0){
		RecvFile(sockfd, fname);
	}

	if (strcmp(cmnd, "list_dir") == 0){
		if (Recieve(sockfd, recvline, sizeof(recvline)) >= 0){
			error_no_exit("str_cli: server terminated prematurely");
		}
	}

	/* put the server input on display in the command window */
	fputs(recvline, stdout);
}

int main(int argc, char **argv)
{
	/*------------------------------------------------------
	Local Variables
	------------------------------------------------------*/
	char 			   *ip_address;
	struct sockaddr_in	servaddr;
	int					sockfd;
	
	/*------------------------------------------------------
	Initialize Local Variables
	------------------------------------------------------*/
	ip_address = (char *)malloc(100 * sizeof(char));
	ip_address = argv[1];

	if (argc != 3)
		error("usage: tcpcli <IPaddress>");

	/* creates a socket that is bound to a specific transport service provider */
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_no_exit("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);

	if ( (inet_pton(AF_INET, ip_address, &servaddr.sin_addr)) <= 0)
		error_no_exit("inet_pton error");

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		error_no_exit("connect error");

	client_exec(stdin, sockfd, argv[2]);		/* do it all */

	/*------------------------------------------------------
	Free Allocated Memory
	------------------------------------------------------*/
	free(ip_address);

	exit(0);
}
