#ifndef MYDATA_H
#define MYDATA_H

#include <QtGlobal>
#include <QFile>
class MyData
{
public:
    MyData();
    unsigned char Header[30]; //in constractor, Have to chose witch bit is.
    QFile *file;
    quint16 crc(unsigned char *message, int len);
};

#endif // MYDATA_H
