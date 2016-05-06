#include"filelist.h"
#include"release_3.19.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h> //atoi(),strtok()
#include<memory.h>
#include<signal.h>
#include<netdb.h>

#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<unistd.h> //sleep()

#include<time.h>	//set_timer
#include<sys/time.h>

#include<pthread.h> //pthread_create()
int g_flag = 0;
//int  ERROR_TYPE = 0;	//返回错误类型
//int send_flag = 0;
//int current_prio = -1;	
LinkList list = NULL;    // send file buffer...

FILE *infile = NULL;
char *format = "./radio/%d.g711";

typedef struct{
	/** byte 0 **/
	unsigned char srcc_len:4;
	unsigned char extension:1;
	unsigned char padding:1;
	unsigned char version:2;
	/** byte 1**/
	unsigned char payload:7;
	unsigned char marker:1;
	/** byte 2,3 **/
	unsigned short seq_no;
	/** byte 4-7 **/
	unsigned long timestamp;
	/** byte 8-11 **/
	unsigned long ssrc;
}RtpHeader;
struct sockaddr_in destIp;
int len = sizeof(struct sockaddr_in);
int socketfd;

/**
** check file has or not .....
**/
int checkFile(int filenameNum){
	char filename[20];
	memset(filename,0,20);
	sprintf(filename,format,filenameNum);
	FILE *file = fopen(filename,"r");
	if(file == NULL){
		return 1;
	}else{
		fclose(file);
		return 0;
	}
}
/**
** check ip format.....
**/

int checkIpAddress(char *ipStr){
	//1.get local ip
	//2.compare mask
	//3.return result
	return 1;
}
/**
** init pakage header...23 bytes...
**/
void InitHeader(char *pSendbuf,char *dstIp){
	unsigned long src_addr;
	unsigned long dst_addr;
	int i = 10;
	if(pSendbuf == NULL) return;
	
	pSendbuf[0] = 0x1;	//Ð­ÒéÀàÐÍ
	pSendbuf[1] = 0x0;	//ÓŠÓÃ±šÎÄÀàÐÍŒ°°æ±Ÿ±êÊ¶
	pSendbuf[2] = 14;	//Í·²¿³€¶È
	pSendbuf[3] = 0;	//ÐÅÏ¢ÀàÐÍ
	pSendbuf[4] = 0;	//ÓÅÏÈŒ¶
	pSendbuf[5] = 0x1;	//·þÎñÀàÐÍ£º0ÎÞ¿É¿¿£¬1¿É¿¿£¬ÒªÇóÓŠŽð	
	src_addr = ntohl(inet_addr("192.168.0.100"));
	pSendbuf[6] = (char)(src_addr>>24);	//ÔŽIpµØÖ·£º¹Ì¶šÎª192.168.0.2
	pSendbuf[7] = (char)(src_addr>>16);
	pSendbuf[8] = (char)(src_addr>>8);
	pSendbuf[9] = (char)src_addr;
	dst_addr = ntohl(inet_addr(dstIp));//Ä¿µÄIpµØÖ·£º¹Ì¶šÎª192.168.0.2
	pSendbuf[10] = (char)(dst_addr>>24);	//ÔŽIpµØÖ·£º¹Ì¶šÎª192.168.0.2
	pSendbuf[11] = (char)(dst_addr>>16);
	pSendbuf[12] = (char)(dst_addr>>8);
	pSendbuf[13] = (char)dst_addr;
	pSendbuf[14] = (char)(345>>8); //ÕýÎÄ³€¶ÈÁœžö×ÖœÚ£ºžß×ÖœÚÔÚÇ°£¬µÄ×ÖœÚÔÚºó ŒÆËã£º1+4+2+336+2=345
	pSendbuf[15] = (char)345;  //²»Ç¿×ªÒ²ÐÐ
	pSendbuf[16] = 0;	//¿ØÖÆŽ«Êä×Ö
	pSendbuf[17] = 0;	//ÓŠÓÃ±šÎÄÀàÐÍ£º4žö×ÖœÚ  ÓŠžÃž³ÖµÎª 0x00000200
	pSendbuf[18] = 0;
	pSendbuf[19] = 2;

	pSendbuf[20] = 0;	
	pSendbuf[21] = (char)(336>>8);	//ÓŠÓÃ±šÎÄ³€¶È£º2žö×ÖœÚ N=336žö×ÖœÚ¹Ì¶š
	pSendbuf[22] = (char)336;
}

/**
** init rtp  header information....12 bytes...
**/
void InitRtpHeader(char *pSendbuf, int seq_num){
	RtpHeader *pRtpHeader;	
	pRtpHeader = (RtpHeader *)&pSendbuf[0];
	// btye 1
	pRtpHeader->version = 2;	//°æ±ŸºÅ£¬¹Ì¶šÎª2
	pRtpHeader->padding = 0;
	pRtpHeader->extension = 0;
	pRtpHeader->srcc_len = 0;
	// byte 2
	pRtpHeader->payload = 0;	//žºÔØÀàÐÍºÅ 7bit
	pRtpHeader->marker = 0;		//±êÖŸÎ»£¬ÓÉŸßÌåÐ­Òé¹æ¶šÆäÖµ 1 bit
	// byte 3-4
	pRtpHeader->seq_no = htons(seq_num); //ÐòÁÐºÅ
	// byte 4-7
	pRtpHeader->timestamp = htonl((seq_num+1)*320);  //Ê±ŒäŽÁ
	// byte 8-12
	pRtpHeader->ssrc = htonl(10); //Ëæ»úÖž¶š£¬È«ŸÖÎšÒ»
}

/**
**功能：CRC_16 校验和
**/
unsigned short getCheckSum(char *message, int len){
	int i,j;
	unsigned short crc_reg;
	unsigned short current;
	for(i = 0; i < len; i++){
		current = message[i] << 8;
		for(j = 0; j < 8; j++){
			if((short)(crc_reg^current) < 0){
				crc_reg = (crc_reg << 1)^0x1021;
			}else{
				crc_reg <<= 1;
			}
			current <<= 1;
		}
	}

	return crc_reg;
}
/**
** set baoliuzi information...
**/
void setBetweenByte(char *pSendbuf){
	unsigned short temp;
	pSendbuf[0] = 0;
	pSendbuf[1] = 0;
	pSendbuf[2] = 0;
	pSendbuf[3] = 0;
	temp = getCheckSum(pSendbuf+15,345); //336+9
	pSendbuf[4] = (char)(temp>>8);//23+336
	pSendbuf[5] = temp;
}
/**
** print header information....
**/
void printHeaderInfo(char *pSendbuf){
	int i = 0;
	if(pSendbuf == NULL){
		printf("not header information...\n");
		return ;
	}

	for(i = 0; i < 35; i++){
		printf("pSendbuf[%d] = %2x\n",i,pSendbuf[i]);	
	}
}
/**
** vedio send thread.....
**/
void *send_thread(void *p){
	int ret = 0;
	char sendbuf[400];
	char filename[20];
	int seq_number = 0;
	int filenameNum = 0;

	while(!list_isEmpty(list)){
/*
		printf("**************************************************\n");
		list_print(list);
		printf("**************************************************\n");
*/
		memset(filename,0,20);
		filenameNum = list_header(list);
		sprintf(filename,format,filenameNum);
		infile = fopen(filename,"rb");
		while((ret = fread(sendbuf+35,1,320,infile)) > 0){ 
			InitHeader(sendbuf,"192.168.0.20");
			InitRtpHeader(sendbuf+23,seq_number);
			setBetweenByte(sendbuf+355);
			sendto(socketfd,sendbuf,25+336,0,(struct sockaddr*)&destIp,len);  				//recvfrom(socketfd,sendbuf,512,0,(struct sockaddr*)&destIp,len); 
			seq_number++;
			//printHeaderInfo(sendbuf);
			usleep(39000);
		}
		list_delete(&list); 
		fclose(infile);
	}
	g_flag = 0;
	/*printf("thread_send end....\n");*/
}

/**
** init socket...gobal varable..
**/
int InitSocket(char *ipStr, int port){
	socketfd = socket(AF_INET,SOCK_DGRAM,0);
	destIp.sin_family = AF_INET;
	destIp.sin_port = htons(port);
	destIp.sin_addr.s_addr = inet_addr(ipStr);
	if(socketfd <= 0){
		perror("socketfd");
		return -1;  //初始话套接字失败...
	}
	return 0;
}

/**
**  if defined header file ,it is a interface....
**/
void radio_setIPAddress(char *ipStr,int port){
	InitSocket(ipStr,port);
}

void radio_closepriority(int *prio){
	*prio = 0;  //default zero...
}


int radio_send(int prio, int filenameNum,int flags,char *ipStr, int port){
	pthread_t pid;
	//check all parameters....
	radio_closepriority(&prio);
	if(checkFile(filenameNum)) return 1; //not find file...
	if(list == NULL){
		list_init(&list);
	}	
	list_insert(&list,filenameNum,prio); 

	if(g_flag == 0){ //thread is end.
		radio_setIPAddress(ipStr,port);
		pthread_create(&pid,NULL,(void *)send_thread,NULL);
		g_flag = 1;
	}
	return 0;
}
/*

void main(){

	//radio_send(0,6,0,"192.168.0.100",61001);
	sleep(1);
	radio_send(0,1,0,"192.168.0.100",61001);
	//list_print(list);
	sleep(2);
	radio_send(1,2,0,"192.168.0.100",61001);
	radio_send(4,3,0,"192.168.0.100",61001);
	//list_print(list);
	sleep(2);
	radio_send(-1,4,0,"192.168.0.100",61001);
	radio_send(20,5,0,"192.168.0.100",61001);
	//list_print(list);
	sleep(2);
	//radio_send(0,2,0,"192.168.0.100",61001);
	//list_print(list);
	sleep(100);
}
*/



