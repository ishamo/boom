#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include "mp3decode.h"
#include "g711codec.h"
#include "comm.h"
#include "ortp/ortp.h"

FILE *recvfile=NULL;
int g_rtpover=0;

#ifdef _ORTP_
int main(int argc, char *argv[])
{
	RtpSession *session;
	char buffer[BUFFER_SIZE];
	int rdlen=0;
	uint32_t ts=0;
	int stream_received=0;
	int have_more;
//	int i;
//	bool_t adapt=TRUE;
	int ret=-1;
	int rf_size=0;
	int left_len=0;

	ret = rtp_init(&session, argv[1]);
	if(-1 == ret)
	{
		return -1;
	}

	recvfile=fopen(INPUT_ORIG_FILE, "wb");
	if (recvfile==NULL) 
	{
		perror("Cannot open file for writing");
		return -1;
	}

	while(g_rtpover==0)
	{
		have_more=1;
		while (have_more)
		{
			rdlen=rtp_session_recv_with_ts(session,buffer,320,ts,&have_more);
			if (rdlen>0) 
			{
				stream_received=1;
			}
			
			/* this is to avoid to write to disk some silence before the first RTP packet is returned*/	
			if ((stream_received) && (rdlen>0)) 
			{
				/* 文件剩余空间足以存放MP3数据*/
				if(rdlen>OUTPUT_FILE_SIZE)
				{
					printf("Input File Is Too Large!\n");
					return ERROR;
				}
					
				else if(rf_size+rdlen>=OUTPUT_FILE_SIZE)	
				{
					fwrite(buffer,1,OUTPUT_FILE_SIZE-rf_size,recvfile);
					left_len = rdlen -(OUTPUT_FILE_SIZE-rf_size);
					fseek(recvfile, 0, SEEK_SET);	/* 从文件头开始写 */
					fwrite(buffer,1,left_len,recvfile);
					rf_size = left_len;
				}
				else
				{
					fwrite(buffer,1,rdlen,recvfile);
					rf_size += rdlen;
				}
			}
		}
		ts+=BUFFER_SIZE;
		//ortp_message("Receiving packet.");
	}

	rtp_exit(session);
	g_rtpover = 0;

	if((ret=g711u2mp3(INPUT_ORIG_FILE))==ERROR)
	{
		return ERROR;
	}

	store2file(OUTPUT_FILE);

	return 0;
}
#else

int over = 0;

void sync2disk(int sig)
{
	fflush(recvfile);
	fclose(recvfile);
}


void sig_init()
{
      struct sigaction action;
	  
	action.sa_flags = 0;
	action.sa_handler = sync2disk;
	sigemptyset(&action.sa_mask);
	
	if (sigaction(SIGINT, &action, NULL) != OK)
	{
		perror("Sigaction SIGINT ERROR.");
	}
	
	if (sigaction(SIGQUIT, &action, NULL) != OK)
	{
		perror("Sigaction SIGQUIT ERROR.");
	}
#if 0
	if (sigaction(SIGKILL, &action, NULL) != OK)
	{
		perror("Sigaction SIGKILL ERROR.");
	}
#endif

	if (sigaction(SIGTERM, &action, NULL) != OK)
	{
		perror("Sigaction SIGTERM ERROR.");
	}
#if 0
	if (sigaction(SIGSTOP, &action, NULL) != OK)
	{
		perror("Sigaction SIGSTOP ERROR.");
	}
#endif
}

int select_file_and_open(int *wr_tag, int *file_size)
{
//	int file_size=0;
	char mode[3]="\0";
	char wr_file_name[20]="\0";

	*file_size = get_file_size(INPUT_ORIG_FILE_1);
	if(*file_size>=OUTPUT_FILE_SIZE)
	{
		strcpy(wr_file_name, INPUT_ORIG_FILE_2);
		*wr_tag = 2;
		
		*file_size = get_file_size(INPUT_ORIG_FILE_2);
		if(*file_size == 0 || *file_size<OUTPUT_FILE_SIZE)
		{
			strcpy(mode, "a");
		}
		else
		{
			strcpy(mode, "w");
			*file_size = 0;
		}
	}
	else
	{
		strcpy(wr_file_name, INPUT_ORIG_FILE_1);		
		*wr_tag =1;
		strcpy(mode, "a");
	}	

	recvfile=fopen(wr_file_name, mode);
	if (recvfile==NULL) 
	{
		perror("Cannot open file for writing");
		return -1;
	}

}

int main(int argc, char *argv[])
{
	char buffer[DATA_LEN];
	int rdlen=0;
	int rf_size=0;
	int left_len=0;
	int sfd = -1;
	char *p_data = NULL;
      struct sockaddr_in clientSockAddr;
	int addrLen;
	int wr_tag=1;
	int file_size=0;
	
	sfd = udp_init();
	if(-1 == sfd)
	{
		perror("udp_init failed!\n");
	}

	select_file_and_open(&wr_tag, &file_size);

	addrLen = sizeof(struct sockaddr_in);

	sig_init();
	
	while(1)
	{
		memset(buffer, 0, DATA_LEN);
	
		/* 阻塞并循环接收 */
		rdlen = recvfrom(sfd, buffer, DATA_LEN, 0, (struct sockaddr *)&clientSockAddr, (socklen_t *)&addrLen);
		if(ERROR == rdlen)
		{
			if(errno == EINTR)
			{
				printf("recv interrupted, recv over!\n");
				return OK;
			}
			else
			{
				perror("recv data error!\n");
				return ERROR;
			}
		}
		else if(rdlen != DATA_LEN)
		{
			printf("recv data is incorrect: recv %d bytes, but should be %d bytes!\n", rdlen, DATA_LEN);
			return ERROR;
		}

		p_data = buffer+APP_HEADER+RTP_HEADER;
		
		/* 写文件 */			
		if(file_size+rf_size+DATA_SIZE>OUTPUT_FILE_SIZE)	
		{
			fwrite(p_data,1,OUTPUT_FILE_SIZE-rf_size-file_size,recvfile);
			p_data += OUTPUT_FILE_SIZE-rf_size-file_size;
			left_len = DATA_SIZE -(OUTPUT_FILE_SIZE-rf_size-file_size);
			fflush(recvfile);
			fclose(recvfile);

			if(wr_tag == 1)
			{
				recvfile=fopen(INPUT_ORIG_FILE_2, "w");
			}
			else
			{
				recvfile=fopen(INPUT_ORIG_FILE_1, "w");
			}
			file_size = 0;
//			fseek(recvfile, 0, SEEK_SET);	/* 从文件头开始写 */
			fwrite(p_data,1,left_len,recvfile);
			rf_size = left_len;
		}
		else
		{
			fwrite(p_data,1,DATA_SIZE,recvfile);
			rf_size += DATA_SIZE;
		}
		
	}

	return 0;
}

#endif
