#ifndef TREE_H
#define TREE_H

#include "Transaction.h"
#include "nTransaction.h"

#include <cstddef>
#include <QMutex>

template <class T> class Tree
{
public:
    //�����������
    Tree ()               {info = new T; left=right=NULL;}
    Tree (T *x) {info = new T; info=x; left=right=NULL;}
    Tree (const Tree<T>&);
    ~Tree() {delete_tree(this);}

    //���������
    Tree<T>* getRight() {return right;}
    Tree<T>* getLeft() {return left;}
    T* getInfo() {return info;}

    //������������
    void setInfo(T* x) {info = x;}
    int SetId(Tree<T>* tree, int i);
    void setNull(bool isLeft);

    //�������� ������
    void add(T *x);
    void copyTree(Tree<T> *newTree, const Tree<T> &oldTree);

    int total() {return this->total_sum(this, 0.0);}
    int max()   {return this->searchMax(this, 0.0);}
    int min()   {return this->searchMin(this, this->max());}
    int getAmount() {return searchAmount(this);}

    //�������� ����������
    T* operator[](int i)
    {
        return searchTrans(this,i);
    }

    T operator+( Tree<T>& r) { *info + *(r.getInfo()); }

    //����� ��������������� ��� ��������� ����������
    T* searchTrans(Tree<T> *tree,int i);

    QMutex dataMutex;

private:
    T* info;
    Tree *left, *right;
    static int sum;

    //������� ������
    void addSon(Tree<T> *old, Tree<T> *nov);

    int total_sum(Tree<T> *der, int summa);
    int searchMax(Tree<T> *der, int max);
    int searchMin(Tree<T> *der, int min);
    int searchAmount(Tree<T>* tree);

    void delete_tree(Tree<T> *tree);
    void importChildren(const Tree<T> *oldTree);
};

#endif // TREE_H
