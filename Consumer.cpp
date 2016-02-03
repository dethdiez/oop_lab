#include "Consumer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tree.h"

#include <QString>
#include <QThread>
#include <QDebug>
#include <windows.h>

void Consumer::start()
{
    while (data->getAmount()>1)
    {
    data->dataMutex.lock();

    pop(data, data->getAmount()-1);

    qDebug() << "CONSUME THREAD: RECORD DELETED";
    data->dataMutex.unlock();
    Sleep(700);
    }
    emit finished();
}

void Consumer::pop(TreeBank *tree, int id)
{
    if (!tree)
    {
        qDebug() << "CONSUME THREAD: END OF TREE";
    }
    else
    {
    if (tree->getLeft())
    {
        if (tree->getLeft()->getInfo()->getID() == id)
        {
            Transaction* buffer = tree->getLeft()->getInfo();
            qDebug() << "CONSUME THREAD: SENDER: " << buffer->getSender() << " RECEIVER: " << buffer->getReceiver() << " DATE: "
                        << buffer->getDD() + '.' + buffer->getMM() + '.' + buffer->getYY() << " SUM: " << buffer->getSum() << " TYPE: "
                        << buffer->getType() << " PURPOSE: " << buffer->getPurpose();
            tree->setNull(true);
        }
        else
            pop(tree->getLeft(), id);
    }
    if (tree->getRight())
    {
        bool f = (tree->getRight()->getInfo()->getID() == id);
        if(f)
        {
            Transaction* buffer = tree->getRight()->getInfo();
            qDebug() << "CONSUME THREAD: SENDER: " << buffer->getSender() << " RECEIVER: " << buffer->getReceiver() << " DATE: "
                        << buffer->getDD() + '.' + buffer->getMM() + '.' + buffer->getYY() << " SUM: " << buffer->getSum() << " TYPE: "
                        << buffer->getType() << " PURPOSE: " << buffer->getPurpose();
            tree->setNull(false);
        }
        else
            pop(tree->getRight(), id);
    }
    }
}

