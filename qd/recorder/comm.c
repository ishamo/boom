#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <errno.h>
#include "comm.h"
#include "g711codec.h"
#include "ortp/ortp.h"

extern char *g_mp3Buf;
extern int g_mp3Buf_size;
extern int g_rtpover;

int get_file_size(char *file)
{
    struct stat s_buf;
    int status = 0;
    status = stat(file, &s_buf );
	if(-1 == status)
	{
		if(errno == ENOENT)
		{
			return 0;
		}
		else
			return ERROR;
	}

	return s_buf.st_size;
}

int store2file(char *ofile_path)
{
	FILE *outfp=NULL;
	int ret=-1;
//	int of_size=0;

	if(NULL == ofile_path)
	{
		return ERROR;
	}

	if((outfp = fopen(ofile_path, "rb+"))==NULL)
	{
		/* 如果文件不存在，创建文件*/
		if(ENOENT==errno)
		{
			outfp = fopen(ofile_path, "w+");
			if(NULL==outfp)
			{
				return ERROR;
			}
		}
		else
		{
			return ERROR;
		}
	}
#if 0
	of_size = get_file_size(ofile_path);

	/* 文件剩余空间足以存放MP3数据*/
	if(OUTPUT_FILE_SIZE-of_size>=g_mp3Buf_size)	
	{
		fseek(outfp, 0, SEEK_END);	/* 追加写 */
	}
	else if(g_mp3Buf_size > OUTPUT_FILE_SIZE)
	{
		printf("Input Mp3 File Is Too Large!\n");
		goto OUT_LABEL;
	}
#endif

	ret = fwrite(g_mp3Buf, g_mp3Buf_size, 1, outfp);

//OUT_LABEL:	
	fclose(outfp);
	free(g_mp3Buf);
	g_mp3Buf_size=0;

	if(ret>0)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}

void remove_file(char *file_name)
{
	char cCmdName[200] = {0};

	snprintf(cCmdName, sizeof(cCmdName), "rm -rf %s", file_name);
	system(cCmdName);
}

int g711u2mp3(char  *file_name)
{
	int ret = -1;
	
	if(NULL==file_name)
	{
		return ERROR;
	}

	if((ret=g711u2pcm(file_name))==ERROR)
	{
		return ERROR;
	}
	
	if((ret=pcm2mp3())==ERROR)
	{
		return ERROR;
	}

	return OK;
}

void ssrc_cb(RtpSession *session)
{
	printf("hey, the ssrc has changed !\n");
}

void rtp_finish()
{
	printf("rtp_finish!\n");
	g_rtpover = 1;
}

int rtp_init(RtpSession **session, char *ipaddr)
{
	bool_t adapt=TRUE;

	ortp_init();
	ortp_scheduler_init();	
//	signal(SIGINT,stop_handler);
	*session=rtp_session_new(RTP_SESSION_RECVONLY);	
	rtp_session_set_scheduling_mode(*session,1);
	rtp_session_set_blocking_mode(*session,1);
	rtp_session_set_local_addr(*session,"0.0.0.0", RTP_RECV_PORT);
	rtp_session_enable_adaptive_jitter_compensation(*session,adapt);
	rtp_session_set_jitter_compensation(*session,40);
	rtp_session_set_payload_type(*session,0);
	rtp_session_signal_connect(*session,"ssrc_changed",(RtpCallback)ssrc_cb,0);
	rtp_session_signal_connect(*session,"ssrc_changed",(RtpCallback)rtp_session_reset,0);

	rtp_session_signal_connect(*session,"rtcp_bye",(RtpCallback)rtp_finish,0);

	return 0;
}

int udp_init()
{
	int sfd = -1;
	struct sockaddr_in sockAddr;
	int addrLen = 0;

	if((sfd = socket(AF_INET, SOCK_DGRAM, 0))==ERROR)
	{
		perror("create socket ERROR!\n");
		return ERROR;		
	}

	addrLen = sizeof(struct sockaddr_in);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = INADDR_ANY;
	sockAddr.sin_port = htons(RTP_RECV_PORT);

	if (ERROR == bind(sfd, (struct sockaddr *)(&sockAddr), addrLen))
	{
	    perror("bind socket ERROR.\n");
	    close(sfd);
	 return ERROR;
	}

	return sfd;	
}

void rtp_exit(RtpSession *session)
{
	rtp_session_destroy(session);
	ortp_exit();
	
	ortp_global_stats_display();
}

