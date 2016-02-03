#include "Producer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QThread>
#include <QDebug>

void Producer::start()
{
    data->dataMutex.lock();

    //������� ����� ������ � ��������� � ��� ���� ������ �� lineEdit'��
    if(ui->lineEdit_Purpose->text().isEmpty())
    {
        Transaction *n = new Transaction;

        n->setDD(ui->lineEdit_Day->text().toInt());
        n->setMM(ui->lineEdit_Mon->text().toInt());
        n->setYY(ui->lineEdit_Year->text().toInt());
        n->setSum(ui->lineEdit_Sum->text().toInt());
        if(ui->comboBox_Type->currentIndex() == 0)
            n->setType(true);
        else
            n->setType(false);
        n->setSender(ui->lineEdit_Sender->text());
        n->setReceiver(ui->lineEdit_Receiver->text());

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
    else
    {
        nTransaction *a = new nTransaction();

        a->setDD(ui->lineEdit_Day->text().toInt());
        a->setMM(ui->lineEdit_Mon->text().toInt());
        a->setYY(ui->lineEdit_Year->text().toInt());
        a->setSum(ui->lineEdit_Sum->text().toInt());
        if(ui->comboBox_Type->currentIndex() == 0)
            a->setType(true);
        else
            a->setType(false);
        a->setSender(ui->lineEdit_Sender->text());
        a->setReceiver(ui->lineEdit_Receiver->text());
        a->setPurpose(ui->lineEdit_Purpose->text());
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

    qDebug() << "PRODUCE THREAD: RECORD CREATED";
    data->dataMutex.unlock();
    emit finished();
}

