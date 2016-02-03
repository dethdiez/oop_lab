#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Tree.h"
#include "Transaction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    typedef Tree<Transaction> TreeBank;

    void delTrans (TreeBank *clipboard, TreeBank *tree, int transNum);
    void delRoot ();

signals:
    void print(TreeBank* tree);
    
private slots:

    void on_pushButton_Add_clicked();

    void activateButton();

    void on_pushButton_Print_clicked();

    void on_pushButton_Info_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Edit_clicked();

    void on_pushButton_Import_clicked();

    void on_pushButton_Pop_clicked();

    void print_tree(TreeBank *tree);

private:
    Ui::MainWindow* ui;
//    TreeBank tree;
    TreeBank* count;
    int TrNum;
    std::ofstream f;

    void DelRows();

    void editTransactions(TreeBank *tree, int transNum);
    Transaction *editInfo(Transaction* transaction);

    void output(TreeBank* tree);
};

#endif // MAINWINDOW_H
