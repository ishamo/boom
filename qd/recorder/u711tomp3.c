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

int g_rtpover=0;
FILE *recvfile=NULL;

static char *help="usage: u711tomp3 filename \n";

int make_mp3_name(char *ouput_name, char *input_name)
{
	char *p_str=NULL;

	if(NULL == ouput_name || NULL == input_name)
	{
		return ERROR;
	}

	strcpy(ouput_name, input_name);
	p_str = strchr(ouput_name, '.');
	if(NULL == p_str)
	{
		strcat(ouput_name, "mp3");
	}
	else
		strcpy(p_str+1, "mp3");

	return OK;
}

int main(int argc, char *argv[])
{
	int ret=-1;
	char output_name[20]="\0";

	if (argc != 2) 
	{
		printf("Usage: %s \n", help);
		exit(1);
	}

	if((ret=g711u2mp3(argv[1]))==ERROR)
	{
		return ERROR;
	}

	make_mp3_name(output_name, argv[1]);
	
	store2file(output_name);
	
	return 0;
}

