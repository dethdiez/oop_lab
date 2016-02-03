#include "Transaction.h"

#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <iostream>
#include <fstream>

//������������

Transaction::Transaction()
{
    dd=0;
    mm=0;
    yy=0;
    sum=0.0;
    type=false;
    receiver=' ';
    sender=' ';
    id=0;
}

Transaction::Transaction(int date, int mounth, int year, int summa, bool t, QString send , QString rec)
{
    dd=date;
    mm=mounth;
    yy=year;
    sum=summa;
    type=t;
    receiver=rec;
    sender=send;
    id=0;
}

Transaction::Transaction(const Transaction& oldTransaction)
{
    dd=oldTransaction.dd;
    mm=oldTransaction.mm;
    yy=oldTransaction.yy;
    sum=oldTransaction.sum;
    type=oldTransaction.type;
    receiver=oldTransaction.receiver;
    sender=oldTransaction.sender;
    id=oldTransaction.id;
}

Transaction::~Transaction()
{
}


//������������
void Transaction::setDD(int a)
{
    if((mm=2)&&(yy%4!=0))
    {
        if((a>=1)&&(a<=28))
            dd=a;
    }
    else
        if((mm=2)&&(yy%4==0))
        {
            if((a>=1)&&(a<=29))
                dd=a;
        }
        else
            if((mm=1)||(mm=3)||(mm=5)||(mm=7)||(mm=8)||(mm=10)||(mm=12))
            {
                if((a>=1)&&(a<=31))
                dd=a;
            }
            else
                if((a>=1)&&(a<=30))
                    dd=a;
}

void Transaction::setMM(int a)
{
    if((a>=1)&&(a<=12))
        mm=a;
}

void Transaction::setYY(int a)
{
    if(a>=1 && a<=3000)
        yy=a;
}

void Transaction::setSum(int a)
{
    if(a>0.0)
        sum=a;
}

void Transaction::print(std::ofstream &file)
{
    file.write((char*) &dd,  sizeof(int));
    file.write((char*) &mm,  sizeof(int));
    file.write((char*) &yy,  sizeof(int));
    file.write((char*) &sum, sizeof(int));
    file.write((char*) &type, sizeof(bool));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QByteArray send;// = codec->fromUnicode(sender);
    for (int i=0; i<sender.length(); i++)
        send+=sender[i].toAscii();
    const char* s = send.constData();
    int sizeSend = strlen(s);
    file.write((char*)&sizeSend, sizeof(int));
    file.write(s, strlen(s));

    QByteArray rec = codec->fromUnicode(receiver);
    const char* r = rec.constData();
    int sizeRec = strlen(r);
    file.write((char*)&sizeRec, sizeof(int));
    file.write(r, strlen(r));
}

void Transaction::read(std::ifstream &file)
{
    file.read((char*) &dd,  sizeof(int));
    file.read((char*) &mm,  sizeof(int));
    file.read((char*) &yy,  sizeof(int));
    file.read((char*) &sum, sizeof(int));
    file.read((char*) &type, sizeof(bool));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    int sizeSend;
    file.read((char*)&sizeSend,sizeof(int));
    char* send = new char[sizeSend];
    file.read(send,sizeSend);
    sender = codec->toUnicode(send);

    int sizeRec;
    file.read((char*)&sizeRec,sizeof(int));
    char* rec = new char[sizeRec];
    file.read(rec,sizeRec);
    receiver = codec->toUnicode(rec);
}
