#include <stdio.h>
#include <stdlib.h>
#include "g711codec.h"
#include "comm.h"

char *g_pcmBuf=NULL;
int g_pcm_size;

/*
 * function: convert PCM audio format to g711 alaw/ulaw.(zqj)
 *	 InAudioData:	PCM data prepared for encoding to g711 alaw/ulaw.
 *   OutAudioData:	encoded g711 alaw/ulaw.
 *   DataLen:		PCM data size.
 *   reserve:		reserved param, no use.
 */

/*alaw*/
int PCM2G711a( char *InAudioData, char *OutAudioData, int DataLen, int reserve )
{	
	//check params.
	if( (NULL == InAudioData) && (NULL == OutAudioData) && (0 == DataLen) )
	{
		printf("Error, empty data or transmit failed, exit !\n");	
		return -1;
	}
	printf("DataLen = %d, %s, %d\n", DataLen, __func__, __LINE__);

	int Retaen = 0; 
	printf("G711a encode start......\n");
	Retaen = g711a_encode( (unsigned char *)OutAudioData, (short*)InAudioData, DataLen/2 );
	printf("Retaen = %d, %s, %d\n", Retaen, __func__, __LINE__);

	return Retaen; //index successfully encoded data len.
}

/*ulaw*/
int PCM2G711u( char *InAudioData, char *OutAudioData, int DataLen, int reserve )
{	
	//check params.
	if( (NULL == InAudioData) && (NULL == OutAudioData) && (0 == DataLen) )
	{
		printf("Error, empty data or transmit failed, exit !\n");	
		return -1;
	}
	printf("DataLen = %d, %s, %d\n", DataLen, __func__, __LINE__);

	int Retuen = 0; 
	printf("G711u encode start......\n");
	Retuen = g711u_encode( (unsigned char *)OutAudioData, (short*)InAudioData, DataLen/2 );
	printf("Retuen = %d, %s, %d\n", Retuen, __func__, __LINE__);

	return Retuen; 
}

/*
 * function: convert g711 alaw audio format to PCM.(zqj)
 *	 InAudioData:	g711 alaw data prepared for encoding to PCM.
 *   OutAudioData:	encoded PCM audio data.
 *   DataLen:		g711a data size.
 *   reserve:		reserved param, no use.
 */

/*alaw*/
int G711a2PCM( char *InAudioData, char *OutAudioData, int DataLen, int reserve )
{
	//check param.
	if( (NULL == InAudioData) && (NULL == OutAudioData) && (0 == DataLen) )
	{
		printf("Error, empty data or transmit failed, exit !\n");	
		return -1;
	}
	printf("DataLen = %d, %s, %d\n", DataLen, __func__, __LINE__);

	int Retade = 0;
	printf("G711a decode start......\n");
	Retade = g711a_decode( (short*)OutAudioData, (unsigned char *)InAudioData, DataLen );
	printf("Retade = %d, %s, %d\n", Retade, __func__, __LINE__);

	return Retade;	//index successfully decoded data len.
}

int g711u2pcm(char *file_name)
{
	FILE *pInFile = NULL;
	FILE *pOutFile = NULL;
	char *ucInBuff=NULL;
	int DataLen = 0;
	int rdlen = 0;
	int ret = -1;

	if(NULL == file_name)
	{
		return ERROR;
	}

	if((pInFile = fopen(file_name, "rb"))==NULL)
	{
		return ERROR;
	}

	DataLen = get_file_size(file_name);
    	printf("file_size = %d\n", DataLen);

	if((ucInBuff = calloc(1, DataLen + 1))==NULL)
	{
		fclose(pInFile);
		return ERROR;
	}
	
	if((g_pcmBuf = calloc(1, 2*DataLen + 1))==NULL)
	{
		goto LABEL_OUT;
	}

	if((rdlen = fread(ucInBuff, 1, DataLen, pInFile ))==0)
	{
		goto LABEL_OUT;
	}

	if((ret = __g711u2pcm(ucInBuff, g_pcmBuf, rdlen, 0))==ERROR)
	{
		goto LABEL_OUT;	
	}
	g_pcm_size = ret;
	

	if((pOutFile = fopen(PCM_FILE, "wb"))==NULL)
	{
		goto LABEL_OUT;
	}
	if((ret = fwrite(g_pcmBuf, 1, g_pcm_size, pOutFile ))==ERROR)
	{
	}

	fclose(pOutFile);			

LABEL_OUT:
	free(ucInBuff);
	fclose(pInFile);
	if(ERROR == ret && NULL != g_pcmBuf)
	{
		free(g_pcmBuf);
	}

	return ret;
}

/*ulaw*/
int __g711u2pcm( char *InAudioData, char *OutAudioData, int DataLen, int reserve )
{
	//check param.
	if( (NULL == InAudioData) || (NULL == OutAudioData) || (0 == DataLen) )
	{
		printf("Error, empty data or transmit failed, exit !\n");	
		return ERROR;
	}
	printf("DataLen = %d, %s, %d\n", DataLen, __func__, __LINE__);

	int Retude = 0;
	printf("G711u decode start......\n");
	Retude = g711u_decode( (short*)OutAudioData, (unsigned char *)InAudioData, DataLen );
	printf("Retude = %d, %s, %d\n", Retude, __func__, __LINE__);

	return Retude;	
}

