#ifndef __COMM_H
#define __COMM_H

#include "ortp/ortp.h"

#define ERROR 	-1
#define OK		0

#define PCM_FILE "tmp.pcm"
#define OUTPUT_FILE "record.mp3"
#define INPUT_ORIG_FILE_1 "recv-1.u711"
#define INPUT_ORIG_FILE_2 "recv-2.u711"

#define INPUT_ORIG_FILE "recv.u711"

#define APP_HEADER	23
#define RTP_HEADER	12
#define DATA_SIZE 	320
#define RESERVE		4

#define DATA_LEN APP_HEADER+RTP_HEADER+DATA_SIZE+RESERVE

#define BUFFER_SIZE	320

#define OUTPUT_FILE_SIZE 700*1024*1024	//文件大小限制为700M
//#define OUTPUT_FILE_SIZE 700*1024*1024 //文件大小限制为700M

#define RTP_RECV_PORT 61002

extern int get_file_size(char *file);
extern int store2file(char *ofile_path);
extern void remove_file(char *file_name);
extern int g711u2mp3(char  *file_name);
extern int rtp_init(RtpSession **session, char *ipaddr);
extern void rtp_exit(RtpSession *session);
extern int udp_init();

#endif

