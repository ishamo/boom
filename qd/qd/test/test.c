#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>


#include <signal.h>
#include <string.h>


int recvfd;

void hander(int value)
{
	fsync(recvfd);
	close(recvfd);


	printf("record end!\n");
	exit(1);
}

extern void hexprint(unsigned char);


int main()
{
	signal(SIGINT,hander);

	int socketfd;
	struct sockaddr_in addr;

	recvfd=open("recv.u711",O_WRONLY | O_TRUNC);
	printf("%d\n",recvfd);


	socketfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(61002);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(socketfd,(struct sockaddr*)&addr,sizeof(addr));

	unsigned char buffer[1024];
	
	while(1){
		int lens=recvfrom(socketfd,buffer,sizeof(buffer),0,NULL,NULL);
		printf("%d\n",lens);
		int i;
		for(i=0;i<lens;i++){
			hexprint(buffer[i]);
			printf(" ");
		}
		printf("\n");

		unsigned char* p=buffer+23+12;
		
		int length=write(recvfd,p,320);
	}


	close(recvfd);
	close(socketfd);


	return 0;
}
