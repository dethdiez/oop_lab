#ifndef NTRANSACTION_H
#define NTRANSACTION_H

#include <Transaction.h>

#include <QString>
#include <iostream>
#include <fstream>

class nTransaction: public Transaction
{
public:
    nTransaction (const nTransaction&);
    nTransaction();
    ~nTransaction();

    virtual void setPurpose(QString a) { purpose = a; }

    virtual QString getPurpose() { return purpose; }

    virtual void print(std::ofstream &file);
    virtual void read(std::ifstream &file);

    friend std::istream &operator>>(std::ifstream &os, nTransaction &n) { n.read(os); return os; }

    nTransaction* operator = (nTransaction &a);

private:
    QString purpose;
};

#endif // NTRANSACTION_H
