#include "serv_cli.h"

char *receive_file(int sock_desc, int file_size)
{
	FILE *rf;
	rf = fopen("rec_file.c", "w");
	char *msg = "file received";
	int remain_data = file_size;
	int len;
	char buffer[5242880];
	
	while(((len = recv(sock_desc, buffer, file_size, 0)) > 0) && (remain_data > 0))
	{
		fwrite(buffer, sizeof(char), len, rf);
		remain_data -= len;
	}
	return msg;
}