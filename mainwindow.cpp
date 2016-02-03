#include <QMessageBox>
#include <QErrorMessage>
#include <QInputDialog>
#include <iostream>
#include <QThread>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Tree.h"
#include "Transaction.h"
#include "Producer.h"
#include "Consumer.h"
#include "FileProducer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    count = new TreeBank();
    TrNum=0;

    //������� � ������� �������
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Day"<<"Mon"<<"Year"<<"Sender"<<"Reciever"<<"sum"<<"Type"<<"Purpose");

    //��������� ������ �������
    ui->pushButton_Add->setEnabled(false);
    ui->pushButton_Del->setEnabled(false);
    ui->pushButton_Print->setEnabled(false);
    ui->pushButton_Info->setEnabled(false);
    ui->pushButton_Edit->setEnabled(false);
    ui->pushButton_Pop->setEnabled(false);

    //��������� ������� � ���, ��� ����� ������� � lineEdit'�� �� ������, ������� �������� ������ ��� �������, ��� ��� ���������
    connect(ui->lineEdit_Day, SIGNAL(textChanged(QString)),this,SLOT(activateButton()));
    connect(ui->lineEdit_Mon, SIGNAL(textChanged(QString)),this,SLOT(activateButton()));
    connect(ui->lineEdit_Year, SIGNAL(textChanged(QString)),this,SLOT(activateButton()));
    connect(ui->lineEdit_Sum, SIGNAL(textChanged(QString)),this,SLOT(activateButton()));
    connect(ui->lineEdit_Receiver, SIGNAL(textChanged(QString)),this,SLOT(activateButton()));
    connect(ui->lineEdit_Sender, SIGNAL(textChanged(QString)),this,SLOT(activateButton()));

    //������������� ���������� ��������� ��� �������� ������
    QRegExp stringexp("[a-zA-Z ]{1,81}");
    ui->lineEdit_Receiver->setValidator(new QRegExpValidator(stringexp,this));
    ui->lineEdit_Sender->setValidator(new QRegExpValidator(stringexp,this));
    ui->lineEdit_Purpose->setValidator(new QRegExpValidator(stringexp,this));

    QRegExp intexp("[0-9]{1,2}");
    ui->lineEdit_Day->setValidator(new QRegExpValidator(intexp,this));
    ui->lineEdit_Mon->setValidator(new QRegExpValidator(intexp,this));

    QRegExp intexpyear("[0-9]{1,4}");
    ui->lineEdit_Year->setValidator(new QRegExpValidator(intexpyear,this));

    QRegExp floatexp("[0-9]{1,8}");
    ui->lineEdit_Sum->setValidator(new QRegExpValidator(floatexp,this));

    //��������� ������ � ���� ��� ������ ���������� � textEdit
    connect(this,SIGNAL(print(TreeBank*)),this,SLOT(print_tree(TreeBank*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::activateButton()
{
    //���� ��� ���� �� ������, �������� ������, ����� ���������
    if(!(ui->lineEdit_Day->text().isEmpty())&&!(ui->lineEdit_Mon->text().isEmpty())&&!(ui->lineEdit_Year->text().isEmpty())
            &&!(ui->lineEdit_Sum->text().isEmpty())&&!(ui->lineEdit_Day->text().isEmpty())&&!(ui->lineEdit_Sender->text().isEmpty())
            &&!(ui->lineEdit_Receiver->text().isEmpty()))
    {
        ui->pushButton_Add->setEnabled(true);
    }
    else
    {
        ui->pushButton_Add->setEnabled(false);
    }
}

void MainWindow::print_tree(TreeBank *count)
{
    //���� ������ - �� ����� �� �����
    if(!count)
        return;
    else
    {
        //������������ ������ ����, ����� ����, ����� ������� ���� (������������ �����)
        print_tree(count->getLeft());


        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QTableWidgetItem *itmID = new QTableWidgetItem(tr("%1").arg(QString::number(count->getInfo()->getID())));
        ui->tableWidget->setItem(TrNum,0,itmID);

        QTableWidgetItem *itmDD = new QTableWidgetItem(tr("%1").arg(QString::number(count->getInfo()->getDD())));
        ui->tableWidget->setItem(TrNum,1,itmDD);

        QTableWidgetItem* itmMM = new QTableWidgetItem(tr("%1").arg(QString::number(count->getInfo()->getMM())));
        ui->tableWidget->setItem(TrNum,2,itmMM);

        QTableWidgetItem *itmYY = new QTableWidgetItem(tr("%1").arg(QString::number(count->getInfo()->getYY())));
        ui->tableWidget->setItem(TrNum,3,itmYY);

        QTableWidgetItem *itmSender = new QTableWidgetItem();
        itmSender->setText(count->getInfo()->getSender());
        ui->tableWidget->setItem(TrNum,4,itmSender);

        QTableWidgetItem* itmReceiver = new QTableWidgetItem();
        itmReceiver->setText(count->getInfo()->getReceiver());
        ui->tableWidget->setItem(TrNum,5,itmReceiver);

        QTableWidgetItem *itmSum = new QTableWidgetItem(tr("%1").arg(QString::number(count->getInfo()->getSum())));
        ui->tableWidget->setItem(TrNum,6,itmSum);

        QTableWidgetItem *itmType= new QTableWidgetItem;
        if(count->getInfo()->getType())
            itmType->setText("Income");
        else
            itmType->setText("Consumption");
        ui->tableWidget->setItem(TrNum,7,itmType);

        QTableWidgetItem *itmPur = new QTableWidgetItem();
        itmPur->setText(count->getInfo()->getPurpose());
        ui->tableWidget->setItem(TrNum,8,itmPur);

        TrNum++;


        print_tree(count->getRight());
    }
}

void MainWindow::DelRows()
{
    for(int i=TrNum;i>0;i=i-1)
    {
        ui->tableWidget->removeRow(i-1);
    }
}



void MainWindow::on_pushButton_Add_clicked()
{
//    //������� ����� ������ � ��������� � ��� ���� ������ �� lineEdit'��
//    if(ui->lineEdit_Purpose->text().isEmpty())
//    {
//        Transaction *n = new Transaction;

//        n->setDD(ui->lineEdit_Day->text().toInt());
//        n->setMM(ui->lineEdit_Mon->text().toInt());
//        n->setYY(ui->lineEdit_Year->text().toInt());
//        n->setSum(ui->lineEdit_Sum->text().toInt());
//        if(ui->comboBox_Type->currentIndex() == 0)
//            n->setType(true);
//        else
//            n->setType(false);
//        n->setSender(ui->lineEdit_Sender->text());
//        n->setReceiver(ui->lineEdit_Receiver->text());

//        if((n->getDD())&&(n->getMM())&&(n->getYY()))
//        {
//            //���� ������ ������� ������ �������(������ ���� �� �����, ���� ��� ���� ������), �������� ��� �� �����, ���� ���, ������ ��������� ����
//            if(!count->getInfo()->getDD())
//            {
//                count->setInfo(n);
//            }
//            else
//                count->add(n);
//        }
//    }
//    else
//    {
//        nTransaction *a = new nTransaction();

//        a->setDD(ui->lineEdit_Day->text().toInt());
//        a->setMM(ui->lineEdit_Mon->text().toInt());
//        a->setYY(ui->lineEdit_Year->text().toInt());
//        a->setSum(ui->lineEdit_Sum->text().toInt());
//        if(ui->comboBox_Type->currentIndex() == 0)
//            a->setType(true);
//        else
//            a->setType(false);
//        a->setSender(ui->lineEdit_Sender->text());
//        a->setReceiver(ui->lineEdit_Receiver->text());
//        a->setPurpose(ui->lineEdit_Purpose->text());
//        if((a->getDD())&&(a->getMM())&&(a->getYY()))
//        {
//            //���� ������ ������� ������ �������(������ ���� �� �����, ���� ��� ���� ������), �������� ��� �� �����, ���� ���, ������ ��������� ����
//            if(!count->getInfo()->getDD())
//            {
//                count->setInfo(a);
//            }
//            else
//                count->add(a);
//        }
//    }

    QThread* producerThr = new QThread();
    Producer* producerObj = new Producer(count, this->ui);
    producerObj->moveToThread(producerThr);

    connect(producerThr, SIGNAL(started()),  producerObj, SLOT(start()));
    connect(producerThr, SIGNAL(finished()), producerThr, SLOT(deleteLater()));
    connect(producerObj, SIGNAL(finished()), producerObj, SLOT(deleteLater()));

    producerThr->start();

    //�������� ������
    ui->pushButton_Del->  setEnabled(true);
    ui->pushButton_Print->setEnabled(true);
    ui->pushButton_Info-> setEnabled(true);
    ui->pushButton_Pop->setEnabled(true);
}

void MainWindow::on_pushButton_Info_clicked()
{
    QMessageBox::information(this,"Info","Total: " + QString::number(count->total()) + "\n" +
                             "Maximum: " + QString::number(count->max()) + "\n" +
                             "Minimum: " + QString::number(count->min()));
}

void MainWindow::on_pushButton_Del_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this, "Confirm", "Do you really want to delete all information?",
                                                            QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Day"<<"Mon"<<"Year"<<"Sender"<<
                                                   "Reciever"<<"sum"<<"Type"<<"Purpose");
        DelRows();
        TrNum=0;

        delete count;
        count = new TreeBank();

        ui->pushButton_Del->  setEnabled(false);
        ui->pushButton_Print->setEnabled(false);
        ui->pushButton_Info-> setEnabled(false);
        ui->pushButton_Edit-> setEnabled(false);
    }
}

void MainWindow::on_pushButton_Print_clicked()
{
    QStringList items;
    items << tr("Screen") << tr("File");
    bool ok;
    QString item = QInputDialog::getItem(this, "Select" , "Select the output destination", items, 0, false, &ok);

    if(ok && item == "Screen")
    {
        ui->tableWidget->clear();
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Day"<<"Mon"<<"Year"<<"Sender"<<
                                                   "Reciever"<<"sum"<<"Type"<<"Purpose");
        DelRows();
        TrNum=0;
        emit MainWindow::print(count);

        ui->pushButton_Edit-> setEnabled(true);
    }
    else if (ok)
    {
        bool ok_;
        QString str = QInputDialog::getText( 0, "Input","Input name of file", QLineEdit::Normal, "C:\\Qt\\qtcreator-2.4.1\\oop_lab6\\file.txt" , &ok_);
        std::string filename = str.toStdString();
        f.open((char*)filename.c_str());
        int amount = count->getAmount();
        f.write((char*) &amount, sizeof(int));
        MainWindow::output(count);
        f.close();
    }
}

void MainWindow::on_pushButton_Edit_clicked()
{
    int transNum=0;

    bool ok_;
    transNum = QInputDialog::getInt(this, tr("Select ID"), tr("Enter ID of transaction, which you want to edit"),
                                        0, 0, TrNum-1, 1, &ok_);

    if (ok_)
    {
        QStringList items;
        items << tr("Delete element") << tr("Edit element");
        bool ok;
        QString item = QInputDialog::getItem(this, "Select" , "Select the operation", items, 0, false, &ok);
        if(ok)
        {
            if(item == "Edit element")
            {
                TreeBank* clipboard = count;
                count = new TreeBank();
                editTransactions(clipboard,transNum);
                count->setInfo(clipboard->getInfo());
                MainWindow::delTrans(clipboard,count,0);
            }
            else if(transNum == 0)
                MainWindow::delRoot();
            else
            {
                TreeBank* clipboard = count;
                count = new TreeBank();
                count->setInfo(clipboard->getInfo());
                MainWindow::delTrans(clipboard, count, transNum);
            }
        }
    }
}

void MainWindow::editTransactions(TreeBank *tree, int transNum)
{
    if(!tree)
        return;
    else
    {
        if(tree->getInfo()->getID() == transNum)
        {
            tree->setInfo(MainWindow::editInfo(tree->getInfo()));
            return;
        }

        else
        {
            editTransactions(tree->getLeft(),transNum);
            editTransactions(tree->getRight(),transNum);
        }
    }
}

Transaction* MainWindow::editInfo(Transaction *transaction)
{
    bool isSub = (transaction->getPurpose() != "none");
    QStringList items;
    if(isSub)
    {
        items <<"Day"<<"Mon"<<"Year"<<"Sender"<<"Reciever"<<"sum"<<"Type"<<"Purpose";
    }
    else
    {
        items <<"Day"<<"Mon"<<"Year"<<"Sender"<<"Reciever"<<"sum"<<"Type";
    }
    bool ok;
    QString item = QInputDialog::getItem(this, "Select" , "Select the field", items, 0, false, &ok);
    if(ok)
    {
        bool isInt=false;
        bool isType=false;

        if (item == "Day" || item == "Mon" || item == "Year" || item == "sum")
            isInt=true;
        else if (item == "Type")
            isType=true;

        if (isInt)
        {
            bool ok_;
            int i = QInputDialog::getInt(this, tr("Input"),
                                          tr("Enter new data"), 0, 0, 100000, 1, &ok_);

            if (ok_)
            {
                if (item == "Day")
                    transaction->setDD(i);
                else
                if (item == "Mon")
                    transaction->setMM(i);
                else
                if (item == "Year")
                    transaction->setYY(i);
                else
                if (item == "sum")
                    transaction->setSum(i);
            }
        }
        else if(isType)
        {
            QStringList items;
            items << "Consumption" << "Income";
            bool ok_;
            QString item = QInputDialog::getItem(this, "Select" , "Select the new type", items, 0, false, &ok_);
            if(ok_ && item == "Income")
                transaction->setType(true);
            else if (ok_)
                transaction->setType(false);
        }
        else
        {
            bool ok_;
            if (item == "Sender")
            {
                QString str = QInputDialog::getText( 0, "Input","Input new Sender", QLineEdit::Normal, "Sender" , &ok_);
                if(ok_)
                    transaction->setSender(str);
            }
            else if(item == "Reciever")
            {
                QString str = QInputDialog::getText( 0, "Input","Input new Reciever", QLineEdit::Normal, "Reciever" , &ok_);
                if(ok_)
                    transaction->setReceiver(str);
            }
            else if(item == "Purpose")
            {
                QString str = QInputDialog::getText( 0, "Input","Input new Purpose", QLineEdit::Normal, "Purpose" , &ok_);
                if(ok_)
                    transaction->setPurpose(str);
            }
        }
    }
    return transaction;
}

void MainWindow::delRoot()
{

    if(TrNum == 1)
    {
//        delete clipboard;
        emit on_pushButton_Del_clicked();
        return;
    }
    else
    {
        TreeBank* clipboard = count;
        count = new TreeBank();
        if(clipboard->getLeft())
        {
            count->setInfo(clipboard->getLeft()->getInfo());
        }
        else
        {
            count->setInfo(clipboard->getRight()->getInfo());
        }
        int transNum = 1;
        MainWindow::delTrans(clipboard, count, transNum);
    }
}

void MainWindow::delTrans(TreeBank *clipboard, TreeBank *tree, int transNum)
{
    if(!clipboard)
        return;
    else
    {
        if((clipboard->getInfo()->getID() != 0) && (clipboard->getInfo()->getID() != transNum))
            tree->add(clipboard->getInfo());
        MainWindow::delTrans(clipboard->getLeft(), tree, transNum);
        MainWindow::delTrans(clipboard->getRight(), tree, transNum);
    }
}

void MainWindow::on_pushButton_Import_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this, "Confirm", "All information will be delete. Are you sure?",
                                                            QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        count = new TreeBank;

        bool ok_;
        QString str = QInputDialog::getText( 0, "Input","Input name of file", QLineEdit::Normal, "C:\\Qt\\qtcreator-2.4.1\\oop_lab6\\file.txt" , &ok_);
        std::ifstream file((char*) str.toStdString().c_str());

        QThread* producerThr = new QThread();
        FileProducer* producerObj = new FileProducer(count, this->ui, str);
        producerObj->moveToThread(producerThr);

        connect(producerThr, SIGNAL(started()),  producerObj, SLOT(start()));
        connect(producerThr, SIGNAL(finished()), producerThr, SLOT(deleteLater()));
        connect(producerObj, SIGNAL(finished()), producerObj, SLOT(deleteLater()));

        producerThr->start();
//        if(file.is_open())
//        {
//        int amount;
//        file.read((char*)&amount, sizeof(int));

//        for (int i = 0; i<amount; i++)
//        {
//            bool isSub;
//            file.read((char*)&isSub, sizeof(bool));
//            if(isSub)
//            {
//                nTransaction* a = new nTransaction;
//                file >> *a;
////                a->read(file);
//                if((a->getDD())&&(a->getMM())&&(a->getYY()))
//                {
//                    //���� ������ ������� ������ �������(������ ���� �� �����, ���� ��� ���� ������), �������� ��� �� �����, ���� ���, ������ ��������� ����
//                    if(!count->getInfo()->getDD())
//                    {
//                        count->setInfo(a);
//                    }
//                    else
//                        count->add(a);
//                }
//            }
//            else
//            {
//                Transaction* n = new Transaction;
//                file >> *n;
////                n->read(file);
//                if((n->getDD())&&(n->getMM())&&(n->getYY()))
//                {
//                    //���� ������ ������� ������ �������(������ ���� �� �����, ���� ��� ���� ������), �������� ��� �� �����, ���� ���, ������ ��������� ����
//                    if(!count->getInfo()->getDD())
//                    {
//                        count->setInfo(n);
//                    }
//                    else
//                        count->add(n);
//                }
//            }
//        }
//        }
//        else
//        {
//            QErrorMessage* err = new QErrorMessage(this);
//            err->showMessage("Error! Unable to open file.");
//        }
    }
    if(count->getInfo()->getDD())
    {
        ui->pushButton_Del->  setEnabled(true);
        ui->pushButton_Print->setEnabled(true);
        ui->pushButton_Info-> setEnabled(true);
    }
}

void MainWindow::output(TreeBank *tree)
{
    if(!tree)
        return;
    else
    {
        bool isSub = false;
        if(tree->getInfo()->getPurpose() != "none")
            isSub = true;
        f.write((char*)&isSub,sizeof(bool));
//        tree->getInfo()->print(f);
        f<<*tree->getInfo();

        output(tree->getLeft());
        output(tree->getRight());
    }
}

void MainWindow::on_pushButton_Pop_clicked()
{

        if( TrNum == 1)
        {
            emit on_pushButton_Del_clicked();
            return;
        }
        QThread* consumerThr = new QThread;
        Consumer* consumerObj = new Consumer(count, this->ui);
        consumerObj->moveToThread(consumerThr);

        connect(consumerThr, SIGNAL(started()), consumerObj, SLOT(start()));
        connect(consumerObj, SIGNAL(finished()), consumerObj, SLOT(deleteLater()));
        connect(consumerThr, SIGNAL(finished()), consumerThr, SLOT(deleteLater()));

        consumerThr->start();

}
