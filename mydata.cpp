#include "mydata.h"

MyData::MyData()
{
    Header[0] = 1;
    Header[1] = 0;
    Header[2] = 14;
    Header[3] = 0;
    Header[4] = 0;
    Header[5] = 1;
    Header[6] = 127;
    //source address, i ve not count it, just set it as 127.0.0.1
    Header[7] = 0;
    Header[8] = 0;
    Header[9] = 1;
    Header[10] = 192;
    Header[11] = 168;
    Header[12] = 0;
    Header[13] = 2;
    Header[14] = 0;   //length
    Header[15] =  8;
    Header[16] = 0;   //first send, if not received , have to try it third times. And if third times ,tihs byte need to be set as 1.
    Header[17] = 0;
    Header[18] = 0;
    Header[19] = 0;
    Header[20] = 1;
    Header[21] = 0;
    Header[22] = 0;
    // two bytes for crc, just set  it 0, i ven't count it
    Header[23] = 0;
    Header[24] = 0;
}

quint16 MyData::crc(char * message, int len)
{
    //write the crc code there.
        int i,j;
        quint16 crc_reg;
        quint16 current;
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

