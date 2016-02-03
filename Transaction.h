#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <iostream>
#include <fstream>

class Transaction
{
public:
    //������������
    Transaction ();
    Transaction (int date, int mounth, int year, int summa, bool t, QString send, QString rec);
    Transaction (const Transaction&);
    ~Transaction();

    //������������
    void setDD(int a);
    void setMM(int a);
    void setYY(int a);
    void setSum(int a);
    void setType(bool a) {type = a;}
    void setReceiver(QString a) {receiver = a;}
    void setSender(QString a) {sender = a;}
    void setID(int a) {id=a;}
    virtual void setPurpose(QString a) {;}

    //���������
    int     getDD()       {return dd;}
    int     getMM()       {return mm;}
    int     getYY()       {return yy;}
    int     getSum()      {return sum;}
    bool    getType()     {return type;}
    QString getReceiver() {return receiver;}
    QString getSender()   {return sender;}
    int     getID()       {return id;}
    virtual QString getPurpose() {return "none";}


    //�������� ������
    virtual void print(std::ofstream &file);
    virtual void read(std::ifstream &file);

    //���������

    //���������
    bool operator > (const Transaction &a) {return sum > a.sum;}
    bool operator < (const Transaction &a) {return sum < a.sum;}
    bool operator == (const Transaction &a) {return sum == a.sum;}
    bool operator >= (const Transaction &a) {return !(sum < a.sum);}

    //��������������
//    int operator+(const Transaction &a) {return sum+a.sum;}
    Transaction* operator+(const Transaction &a) { sum+=a.sum; return this;}
    int operator-(const Transaction &a) {return sum-a.sum;}
    int operator*(const Transaction &a) {return sum*a.sum;}

    //�����������
    Transaction& operator=(const Transaction& right)
    {
        //�������� �� ����������������
        if (this == &right)
        {
            return *this;
        }
        dd = right.dd;
        mm = right.mm;
        yy = right.yy;
        sum = right.sum;
        type = right.type;
        receiver = right.receiver;
        sender = right.sender;
        return *this;
    }

    //����������/����������� ��������� � ���������
    Transaction &operator++() { sum++; return *this; }
    Transaction operator++(int) { Transaction temp = *this; ++*this; return temp; }
    Transaction &operator--() { sum--; return *this; }
    Transaction operator--(int) { Transaction temp = *this; --*this; return temp; }

    //�����/������
    friend std::ifstream &operator>>(std::ifstream &os, Transaction &n) { n.read(os); return os; }
    friend std::ofstream &operator<<(std::ofstream &os, Transaction &n) { n.print(os); return os; }

    //������
    Transaction& operator()(int n) { sum = n; return *this; }
    //a(5).setDD(6);

protected:
    int dd, mm, yy;
    int sum;
    bool type;
    QString receiver, sender;
    int id;
};

#endif // TRANSACTION_H
