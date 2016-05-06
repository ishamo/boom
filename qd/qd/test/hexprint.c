#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void hprint(unsigned char ch)
{
	if(ch>=0 && ch<=9)
		printf("%c",ch+48);
	else
		printf("%c",ch+65-10);	
}

void hexprint(unsigned char ch)
{
	unsigned char tmp;
	tmp=ch>>4;
	hprint(tmp);
	tmp=ch & 0x0f;
	hprint(tmp);
}

/*
int main()
{
	unsigned char ch1=0xff;
	unsigned char ch2=0x03;

	hexprint(ch1);
	printf("\n");
	hexprint(ch2);
	printf("\n");

	return 0;
}

*/
