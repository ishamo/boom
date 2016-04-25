#ifndef MYDATA_H
#define MYDATA_H
/* all is the localhost data need to be send. */
#include <QtGlobal>
class MyData
{
public:
    MyData();
    char selfcheck[30]; //in constractor, Have to chose witch bit is.
    char argsetup[30];
    char record[30];
    char player[30];
    quint16 crc(char *, int len);
};

#endif // MYDATA_H
