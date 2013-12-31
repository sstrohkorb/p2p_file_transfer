/*****************************************************************************************
 * PROJECT: Sashe
 * TEAM MEMBERS: Arjun Aletty, Keely Haverstock, Sarah Seko, Sarah Strohkorb
 * 
 * FILE: serv_cli.h
 * 
 * DESCRIPTION:
 * 
*****************************************************************************************/

/*--------------------------------------------------------------------
						GENERAL INCLUDES
--------------------------------------------------------------------*/
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include 	<strings.h>
#include 	<signal.h>
#include	<sys/ioctl.h>
#include 	<sys/sendfile.h>
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<sys/types.h>	/* basic system data types */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<sys/un.h>		/* for Unix domain sockets */
#include	<sys/wait.h>
#include	<time.h>		/* timespec{} for pselect() */
#include	<unistd.h>

/*--------------------------------------------------------------------
					    LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define	LISTENQ				1024
#define LOOKUP_TABLE_LEN	3
#define	MAXLINE				4096			/* max text line length */
#define	SA					struct sockaddr
#define	SERV_PORT		 	9877			/* TCP and UDP client-servers */

/*--------------------------------------------------------------------
						    TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
						  PROCEDURES
--------------------------------------------------------------------*/
/* client_exe01.c */
void client_exec(FILE *fp, int sockfd, char *fname);

/* error.c */
void error(char *msg);
void error_no_exit(char *msg);

/* send_recieve.c */
ssize_t Recieve(int fd, void *vptr, size_t maxlen);
ssize_t	Send(int fd, const void *vptr, size_t n);
void file_transfer(char *file_name, int connfd);
void RecvFile(int connfd, char *filename);