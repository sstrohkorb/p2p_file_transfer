/*****************************************************************************************
 * PROJECT: Sashe
 * TEAM MEMBERS: Arjun Aletty, Keely Haverstock, Sarah Seko, Sarah Strohkorb
 * 
 * FILE: send_recieve.c
 * 
 * DESCRIPTION: Provides sending and recieving capabilities that both the client and 
 * 	server can use. 
 * 
*****************************************************************************************/

/*--------------------------------------------------------------------
						GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "serv_cli.h"

static ssize_t my_recieve(int fd, char *ptr)
{
	/*------------------------------------------------------
	Local Variables
	------------------------------------------------------*/
	static int	read_cnt = 0;
	static char	*read_ptr;
	static char	read_buf[MAXLINE];

	if (read_cnt <= 0) {
again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return(-1);
		} else if (read_cnt == 0)
			return(0);
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return(1);
}

ssize_t Recieve(int fd, void *vptr, size_t maxlen)
{
	/*------------------------------------------------------
	Local Variables
	------------------------------------------------------*/
	int		n, rc, iter;
	char	c, *ptr, *iter_size;

	// FILE *str_fd = fopen("~/Dropbox/softsys/str_size.txt", "r");
	// fread(iter_size, sizeof(char), 10, str_fd);

	// iter  = atoi(iter_size);
	// printf("%i\n", iter);

	ptr = vptr;
	for (n = 1; n < 18; n++) {
		printf("iter %i\n", n);
		if ( (rc = my_recieve(fd, &c)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		} else if (rc == 0) {
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} else
			return(-1);		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}

ssize_t	Send(int fd, const void *vptr, size_t n)
{
	/*------------------------------------------------------
	Local Variables
	------------------------------------------------------*/
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}

void file_transfer(char *file_name, int connfd)
{
	printf("starting file transfer\n");
	int sent_bytes; //status of sendfile
	int *fsize; //filesize variable
	struct stat stat_buf; //argument for stat
	int nread;

	//open file and create file descriptor
	int fd = open(file_name, O_RDONLY);
	if (fd <= 0){
		error("can't open file");
	}

	//get file size
	fstat(fd, &stat_buf);
	*fsize = stat_buf.st_size;

/*	//send file size
	while (sent_bytes < sizeof(*fsize)){
		sent_bytes += send(connfd, fsize, sizeof(*fsize), 0);
	}*/
	
	//send file
	char *filebuf[*fsize];
	while ((nread = read(fd, filebuf, sizeof(filebuf))) > 0) {
     size_t toread = nread, off = 0, wr;
     while (toread > 0) {
         wr = write(connfd, filebuf + off, toread);
         if (wr >= 0) {
             toread -= wr;
             off += wr;
         	} else {
         		close(fd);
             	error("can't connect to socket");
         	}
    	}
	}

	shutdown(connfd,SHUT_RDWR);
	close(connfd);
	close(fd);
	printf("%s\n", "file sent and closed");
	return;
}


void RecvFile(int connfd, char *filename)
{ 
	int fs_rec = 0;
    size_t file_size;
    size_t bytes_read = 0;

    // filename = "test.txt";

    FILE *fd = fopen(filename, "wb");
    if (fd < 0){
    	error("can't open file");
    } 

    //get file size
    // while (){
    // 	fs_rec = recv(connfd, &file_size, sizeof(file_size), 0);
    // }

    file_size = 1363155;

    //allocate space for buffer
	char *buf;
	buf = (char *)malloc(file_size+1);

	//get file from socket and store in buffer
	//write buffer to file
	while(bytes_read < file_size){
		int nRecv = recv(connfd, buf, file_size, 0);
		if(nRecv == 0){
			break;
		}
		if (nRecv < 0)
			error("can't read from socket");
		int wrByte = fwrite(buf, sizeof(char), nRecv, fd);
		bytes_read += wrByte;
		for (int i = 0; i < wrByte; i++){
			if(buf[i] == '\n'){
				bytes_read += 1;
			}
		}
	}

	fclose(fd);
	free(buf);
	close(connfd);
	printf("File Transfer complete\n\n");
	return;
}