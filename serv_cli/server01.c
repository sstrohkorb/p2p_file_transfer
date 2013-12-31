/*****************************************************************************************
 * PROJECT: Sashe
 * TEAM MEMBERS: Arjun Aletty, Keely Haverstock, Sarah Seko, Sarah Strohkorb
 * 
 * FILE: server01.c
 * 
 * DESCRIPTION:
 * 
*****************************************************************************************/

/*--------------------------------------------------------------------
                                                GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "serv_cli.h"

void str_exec(int connfd)
{
        /*------------------------------------------------------
        Local Variables
        ------------------------------------------------------*/
        long            arg1, arg2;
        char         str_arg1[100], str_arg2[100];
        char            line[MAXLINE];
        char               *lookup_table[LOOKUP_TABLE_LEN] = {"list_dir", "download"};
        ssize_t         n;
        
        for ( ; ; ) {
                printf("initializing\n");
                if ( (n = Recieve(connfd, line, MAXLINE)) == 0)
                        return;         /* connection closed by other end */

                printf("%s\n", line);
                if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2) {
                        snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
                } else {
                        /* parse the input line into 1 or 2 strings */
                        if (sscanf(line, "%s%s", (char *)&str_arg1, (char *)&str_arg2) == 2) {
                        } else {
                                if (sscanf(line, "%s", (char *)&str_arg1) == 1) {
                                } else {
                                        snprintf(line, sizeof(line), "input error\n");
                                }
                        }
                        /* find the corresponding command integer in our lookup table */
                        int command_num = -1;
                        int i;
                        for (i = 0; i < LOOKUP_TABLE_LEN; i++){
                                //printf("%s, %s\n", lookup_table[i], str_arg1);
                                if (strcmp(lookup_table[i], str_arg1) == 0){
                                        command_num = i;
                                        break;
                                }
                        }
                        if (command_num == -1)
                                snprintf(line, sizeof(line), "input error\n");
                        
                        /* execute the corresponding function with the correct arguments */
                        switch(command_num)
                        {
                                case 0:
                                        /* PUT LIST DIRECTORY FUNCTION CALL HERE */
                                        snprintf(line, sizeof(line), "List dir function\n");
                                        break;
                                case 1:
                                        //snprintf("%s\n","flag1");
                                        /* arg2 is a string that is the filename */
                                        file_transfer(str_arg2, connfd);
                                        //printf(line, sizeof(line), "Download file function\n");
                                        break;
                                default:
                                        snprintf(line, sizeof(line), "input error\n");
                                        break;
                        }
                }
                
                n = strlen(line);
                Send(connfd, line, n);
        }
}


int main()
{
        /*------------------------------------------------------
        Local Variables
        ------------------------------------------------------*/

        int                                     listenfd, connfd;
        pid_t                           childpid;
        socklen_t                       clilen;
        struct sockaddr_in      cliaddr, servaddr;

        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
                error("socket error");

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port        = htons(SERV_PORT);

        /* Bind to a port */
        int reuse = 1;
        if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
                error("can't reuse port");
        if((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
                error("bind error");

        /* Listen for a connection */
        char    *ptr;
        int              backlog = LISTENQ;
        /*can override 2nd argument with environment variable */
        if ( (ptr = getenv("LISTENQ")) != NULL)
                backlog = atoi(ptr);
        if ((listen(listenfd, backlog)) < 0)
                error("listen error");

        for ( ; ; ) {
                clilen = sizeof(cliaddr);
                // again:
                if ((connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0)
                        error("accept error");

                //       #ifdef  EPROTO
                //               if (errno == EPROTO || errno == ECONNABORTED)
                //       #else
                //               if (errno == ECONNABORTED)
                //       #endif
                // goto again;
                //               else
                //                       printf("listenfd: %i\n", listenfd);
                //                       error("accept error");
                        
                if ((childpid = fork()) == 0) {                 /* child process */
                        if (close(listenfd) == -1)
                                error_no_exit("close error");   /* close listening socket */
                        str_exec(connfd);                                       /* process the request */
                        exit(0);
                }

                if (close(connfd) == -1)                                /* parent closes connected socket */
                        error_no_exit("close error");
        }
        exit(0);
}
