#include <nTransaction.h>

#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <iostream>
#include <fstream>

nTransaction::nTransaction()
{
    purpose=" ";
}

nTransaction::nTransaction(const nTransaction& oldTransaction)
{
    dd=oldTransaction.dd;
    mm=oldTransaction.mm;
    yy=oldTransaction.yy;
    sum=oldTransaction.sum;
    type=oldTransaction.type;
    receiver=oldTransaction.receiver;
    sender=oldTransaction.sender;
    purpose=oldTransaction.purpose;
    id=oldTransaction.id;
}

nTransaction::~nTransaction()
{
}

void nTransaction::print(std::ofstream &file)
{
    file.write((char*) &dd,  sizeof(int));
    file.write((char*) &mm,  sizeof(int));
    file.write((char*) &yy,  sizeof(int));
    file.write((char*) &sum, sizeof(int));
    file.write((char*) &type, sizeof(bool));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QByteArray send = codec->fromUnicode(sender);
    const char* s = send.constData();
    int sizeSend = strlen(s);
    file.write((char*)&sizeSend, sizeof(int));
    file.write(s, strlen(s));

    QByteArray rec = codec->fromUnicode(receiver);
    const char* r = rec.constData();
    int sizeRec = strlen(r);
    file.write((char*)&sizeRec, sizeof(int));
    file.write(r, strlen(r));

    QByteArray pur = codec->fromUnicode(purpose);
    const char* p = pur.constData();
    int sizePur = strlen(p);
    file.write((char*)&sizePur, sizeof(int));
    file.write(p, strlen(p));
}

void nTransaction::read(std::ifstream &file)
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

    int sizePur;
    file.read((char*)&sizePur,sizeof(int));
    char* pur = new char[sizePur];
    file.read(pur,sizePur);
    purpose = codec->toUnicode(pur);
}
