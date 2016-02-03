#include "FileProducer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <windows.h>

void FileProducer::start()
{
    if(file.is_open())
    {
    int amount;
    file.read((char*)&amount, sizeof(int));

    for (int i = 0; i<amount; i++)
    {
        data->dataMutex.lock();
        bool isSub;
        file.read((char*)&isSub, sizeof(bool));
        if(isSub)
        {
            nTransaction* a = new nTransaction;
            file >> *a;
//                a->read(file);
            if((a->getDD())&&(a->getMM())&&(a->getYY()))
            {
                //���� ������ ������� ������ �������(������ ���� �� �����, ���� ��� ���� ������), �������� ��� �� �����, ���� ���, ������ ��������� ����
                if(!data->getInfo()->getDD())
                {
                    data->setInfo(a);
                }
                else
                    data->add(a);
            }
        }
        else
        {
            Transaction* n = new Transaction;
            file >> *n;
//                n->read(file);
            if((n->getDD())&&(n->getMM())&&(n->getYY()))
            {
                //���� ������ ������� ������ �������(������ ���� �� �����, ���� ��� ���� ������), �������� ��� �� �����, ���� ���, ������ ��������� ����
                if(!data->getInfo()->getDD())
                {
                    data->setInfo(n);
                }
                else
                    data->add(n);
            }
        }
        qDebug() << "PRODUCE THREAD: RECORD CREATED";
        data->dataMutex.unlock();
        Sleep(500);
    }
    }
}


