#ifndef PRODUCER_H
#define PRODUCER_H

#include <QMainWindow>
#include <QObject>
#include "mainwindow.h"

class Producer: public QObject
{
    Q_OBJECT

public:
    Producer(Tree<Transaction>* data, Ui::MainWindow *ui):
             data(data), ui(ui){;}

    public slots:
        void start();

    signals:
        void finished();

private:
        Tree<Transaction>* data;
        Ui::MainWindow *ui;
};

#endif // PRODUCER_H
