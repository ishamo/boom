动态库的使用说明：

1.首先包含头文件
	#include"release_3.20.h"

2.使用发送语音函数的借口
	int radio_send(int prio,int filename,int flags,char *ipStr,int port);
	参数说明：prio:语音或短语的优先级（暂时不适用，默认调零）
		  filename 要发送的语音或短语的文件名
		  flags 发送给炮长或所有人
		  ipStr，port：要发送的炮长设备的地址和端口号
	返回值：非零表示故障（表示未找到语音文件）

3.目录说明
	将release_3.20.so radio release_3.20.h和filelist.h放到同一目录下
4.配置环境变量
	方式1：将release_3.20.so 拷贝到/usr/lib下（只要一次型配置即可）
	方式2：export LD_LIBRARY_PATH=release_3.20.so所在的目录下..(绝对路径)



案例：

/****************************
**运行环境：
1.以上所有文件放到一个跟目录下的zdw文件夹中（如:/zdw）
2.radio/1.g711语音文件存在
******************************/
test.c
********************************************************************************
#include"release_3.20.h"
#include<stdio.h>
#include<unistd.h>

void main(){
	radio_send(0,1,0,"192.168.0.100",61002);  //发送录音数据
	//sleep(100);  //主函数等待录音的播放
	getchar();
}

******************************************************************************
测试命令：
1.gcc test.c -o test -L./ -lrelease_3.20 
2.export LD_LIBRARY_PATH=/zdw/
3../test







