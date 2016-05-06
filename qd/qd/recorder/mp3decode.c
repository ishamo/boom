#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lame.h"
#include "lame_global_flags.h"
#include "comm.h"

extern char *g_pcmBuf;
extern int g_pcm_size;

char *g_mp3Buf=NULL;
int g_mp3Buf_size=0;

int __pcm2mp3() 
{
	int status = 0;
	lame_global_flags* gfp=NULL;
	int ret_code=-1;
	unsigned char* mp3_buffer=NULL;
	unsigned char*tbuf=NULL;
	unsigned int t_size=0;
	int mp3_bytes=0;
	int osize=0;
	
	gfp = lame_init();
	if (gfp == NULL) 
	{
		printf("lame_init failed\n");
		status = ERROR;
		goto exit;
	}

	lame_set_in_samplerate(gfp, 8000);
	lame_set_num_channels(gfp, 1);

	/* for '-r' */
	lame_set_mode(gfp, MONO);
	lame_set_scale_left(gfp, 0);
	lame_set_scale_right(gfp, 2);
		
	ret_code = lame_init_params(gfp);
	if (ret_code < 0) 
	{
		printf("lame_init_params returned %d/n",ret_code);
		status = ERROR;
		goto close_lame;
	}

	osize = 1.25 * g_pcm_size + 7200;
	mp3_buffer = (unsigned char*)malloc(osize);
	
	mp3_bytes = lame_encode_buffer (gfp, (short *)g_pcmBuf, NULL, g_pcm_size/2, mp3_buffer, osize); 

	if((tbuf= calloc(1, mp3_bytes))==NULL)
	{
		return ERROR;
	}
	memcpy(tbuf, mp3_buffer, mp3_bytes);
	
	g_mp3Buf_size += mp3_bytes;
	t_size = mp3_bytes;
	printf("writing %d mp3 bytes\n", mp3_bytes);
	
	mp3_bytes = lame_encode_flush(gfp, mp3_buffer, osize);
	g_mp3Buf_size += mp3_bytes;

	printf("writing %d mp3 bytes\n", mp3_bytes);

	if((g_mp3Buf = calloc(1, g_mp3Buf_size))==NULL)
	{
		return ERROR;
	}
	memcpy(g_mp3Buf, tbuf, t_size);
	memcpy(g_mp3Buf+t_size, mp3_buffer, mp3_bytes);

	free(tbuf);	
	free(mp3_buffer);
	free(g_pcmBuf);
	g_pcm_size = 0;

close_lame:
	lame_close(gfp);
exit:
	return status;
}

int pcm2mp3() 
{
	int ret=-1;

	ret = __pcm2mp3();

	remove_file(PCM_FILE);
	
	return ret;
}
