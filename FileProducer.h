#ifndef FILEPRODUCER_H
#define FILEPRODUCER_H

#include <QMainWindow>
#include <QObject>
#include "mainwindow.h"

class FileProducer: public QObject
{
    Q_OBJECT

public:
    FileProducer(Tree<Transaction>* data, Ui::MainWindow *ui, QString str):
        data(data), ui(ui), file((char*) str.toStdString().c_str()){;}

    public slots:
        void start();

    signals:
        void finished();

private:
        Tree<Transaction>* data;
        Ui::MainWindow *ui;
        std::ifstream file;
};

#endif // FILEPRODUCER_H
