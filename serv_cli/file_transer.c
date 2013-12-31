#include "serv_cli.h"

void file_transfer(char *file_name, int connfd)
{
	int sf; //status of sendfile
	off_t offset = 0; //offset variable
	struct stat stat_buf; //argument for stat

	//open file and create file descriptor
	FILE *fd = fopen(file_name, "r");
	if (fd == -1){
		error("unable to open file");
	}

	//get file size
	fstat(fd, &stat_buf);

	//sendfile
	sf = sendfile(connfd, fd, &offset, stat_buf.st_size);
	if(sf != stat_buf.st_size){
		error("can't send file");
	}
}