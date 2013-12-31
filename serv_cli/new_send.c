printf("sendline len: %zu\n", (strlen(sendline)+1));

int tosend = strlen(sendline)+1;
int off = 0;
int wr;

while(tosend > 0){
	wr = write(connection->sockfd, sendline+off, tosend);
	if (wr >= 0){
		tosend -= wr;
		off += wr;
	} else{
		close(connection->sockfd);
		error("can't write to socket");
	}
}	