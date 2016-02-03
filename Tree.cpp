#include <QString>
#include <iostream>

#include <Tree.h>

template <class T>
Tree<T>::Tree(const Tree<T> &tree)
{
    copyTree(this, tree);
}

//�������� ������

template <class T>
int Tree<T>::SetId(Tree<T> *tree, int i=0)
{
    if(!tree)
        return i;
    else
    {
        tree->info->setID(i);
        i++;
        i=Tree<T>::SetId(tree->left,i);
        i=Tree<T>::SetId(tree->right,i);
        return i;
    }
}

template <class T>
void Tree<T>::addSon(Tree<T> *old, Tree<T> *newTree)
{
//    bool f = newTree->info < old->info;

    if      ((newTree->info->getSum() < old->info->getSum())  && (left == NULL))  //���� ����� ��������, �� ������ ������
                old->left = newTree;
    else if ((newTree->info->getSum() < old->info->getSum())  && (left != NULL))  //���� ����� ������, �� �������� addSon ��� ������ ����
                old->left->addSon(old->left,newTree);
    else if ((newTree->info->getSum() >= old->info->getSum()) && (right == NULL)) //���� ������ ��������, �� ������ �������
                old->right = newTree;
    else if ((newTree->info->getSum() >= old->info->getSum()) && (right != NULL)) //���� ������ ������, �� �������� addSon ��� ������� ����
                old->right->addSon(old->right, newTree);
}

template <class T>
int Tree<T>::total_sum(Tree<T> *der, int summa)
{
    if(!der)
        return 0.0;
    else
    {
        summa=der->info->getSum()+der->total_sum(der->left, summa)+der->total_sum(der->right, summa);
        return summa;
    }
}

template <class T>
int Tree<T>::searchMax(Tree<T> *der, int max)
{
    if(!der)
        return max;
    else
    {
        if(der->info->getSum()>max)
            max=der->info->getSum();
        max=searchMax(der->left, max);
        max=searchMax(der->right,max);
        return max;
    }
}

template <class T>
int Tree<T>::searchMin(Tree<T> *der, int min)
{
    if(!der)
        return min;
    else
    {
        if(der->info->getSum()<min)
            min=der->info->getSum();
        min=searchMin(der->left, min);
        min=searchMin(der->right,min);
        return min;
    }
}

template <class T>
int Tree<T>::searchAmount(Tree<T> *tree)
{
    int A=0;
    if(!tree)
        return A;
    else
    {
        A = A + searchAmount(tree->left);
        A = A + searchAmount(tree->right);
        A++;
        return A;
    }
}

template <class T>
void Tree<T>::delete_tree(Tree<T> *tree)
{
    if(!tree)
    {
        return;
    }
    else
    {
        if(tree->left)
        {
            tree->left->~Tree();
        }
        if(tree->right)
        {
            tree->right->~Tree();
        }
        return;
    }
}

template <class T>
void Tree<T>::copyTree(Tree<T> *newTree, const Tree<T> &oldTree)
{
    newTree = new Tree;
    const Tree<T>* oldTreePointer = &oldTree;
    newTree->importChildren(oldTreePointer);
//    newTree->setInfo(oldTree.info);
//    const Tree* oldTreePointer = oldTree.left;
//    newTree->importChildren(oldTreePointer);
//    oldTreePointer = oldTree.right;
//    newTree->importChildren(oldTreePointer);
}

template <class T>
void Tree<T>::importChildren(const Tree<T> *oldTree)
{
    if (!oldTree)
        return;
    else
    {
        if(!this->getInfo()->getDD())
        {
            this->setInfo(oldTree->info);
        }
        else
            this->add(oldTree->info);

//        this->add(oldTree->info);

        this->importChildren(oldTree->left);
        this->importChildren(oldTree->right);
    }
}

//�������� ������
template <class T>
void Tree<T>::add(T *x)
{
    Tree<T> *newTree = new Tree(x);

    this->addSon(this,newTree);

    Tree<T>::SetId(this);
}

template <class T>
T* Tree<T>::searchTrans(Tree<T> *tree, int i)
{
    if(!tree)
        return NULL;
    else
    {
        if(tree->getInfo()->getID() == i)
            return tree->getInfo();

        else
        {
            searchTrans(tree->getLeft(),i);
            searchTrans(tree->getRight(),i);
        }
    }
}

template <class T>
void Tree<T>::setNull(bool isLeft)
{
    if(isLeft)
        left = NULL;
    else
        right = NULL;
}

//template <class T>
//T* Tree<T>::plus(Tree<T> &le, Tree<T> &ri)
//{
//    int buff;
//    buff = le.getInfo() + ri.getInfo();
//    le.getInfo()->setSum(buff);
//    return le->getInfo();
//}

template class Tree<Transaction>;
