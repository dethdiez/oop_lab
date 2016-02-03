#ifndef CONSUMER_H
#define CONSUMER_H

#include <QMainWindow>
#include <QObject>
#include "mainwindow.h"

class Consumer: public QObject
{
    Q_OBJECT

public:
    typedef Tree<Transaction> TreeBank;

    Consumer(TreeBank* data, Ui::MainWindow *ui):
             data(data), ui(ui){;}

public slots:
    void start();

signals:
    void finished();

private:
//    int id;
    TreeBank* data;
    Ui::MainWindow *ui;

    void pop(TreeBank* tree, int id);
};

#endif // CONSUMER_H
