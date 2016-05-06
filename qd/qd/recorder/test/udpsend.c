#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXDATASIZE 200*1024 /* Max number of bytes of data */
#define PACKET_SIZE 359 

static char *help="usage: udpsend	filename dest_ip4addr dest_port \n";

int main(int argc, char *argv[])
{
	int sfd=-1; /* files descriptors */
	int fd=-1;
	int rd_len=-1;
	int left_len=0;
	char file_buf[MAXDATASIZE];
	char *pfile_buf;
	char sendbuf[PACKET_SIZE];
	struct sockaddr_in server; /* server's address information */
	socklen_t addrLen;
	int over = 0;

	if (argc != 4) 
	{
		printf("Usage: %s \n", help);
		exit(1);
	}


	if((fd =open(argv[1], O_RDONLY))==-1)
	{
		perror("open error!\n");
		return -1;
	}

	rd_len = read(fd, file_buf, MAXDATASIZE);
	if(rd_len == -1)
	{
		printf("read error!\n");
		return -1;
	}

	printf("read file size: %d bytes\n", rd_len);

	if ((sfd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
	{
		printf("socket() error\n");
		exit(1);
	}

	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[3])); /* htons() is needed again */
	server.sin_addr.s_addr = inet_addr(argv[2]); 
	addrLen=sizeof(struct sockaddr_in);

	pfile_buf = file_buf;
	while (!over)
	{
		memset(sendbuf, 0, PACKET_SIZE);

		left_len = rd_len - (pfile_buf - file_buf);
		if(left_len<320)
		{
			over = 1;
			memcpy(sendbuf+35, pfile_buf, left_len);
		}
		else
		{
			memcpy(sendbuf+35, pfile_buf, 320);
		}

		sendto(sfd,sendbuf,PACKET_SIZE,0,(struct sockaddr *)&server, addrLen);
		usleep(500);
		
		pfile_buf+=320;
	}

	printf("send data size %d bytes\n", pfile_buf-file_buf);

	close(sfd); /* close fd */

	return 0;
}
