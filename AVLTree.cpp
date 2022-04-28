/**
 * @file AVLTree.cpp
 * @author Mike Boyle
 * @brief implementation file for AVL Tree
 * @date 2022-05-19
 *
 */

#include "AVLTree.h"
#include <string>

const int LEFT_TALLER = -1;
const int RIGHT_TALLER = 1;
const int BALANCED = 0;

template <class T>
AVLTree<T>::AVLTree()
{
    root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    destroyTree();
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T> &other)
{
    copyTree(root, other.root);
}

template <class T>
const AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &other)
{
    if (this != &other)
    {
        destroyTree();
        copyTree(root, other.root);
    }
    return *this;
}

template <class T>
void AVLTree<T>::insert(const T &item)
{
    bool taller = false;
    insertNode(root, item, taller);
}

template <class T>
int AVLTree<T>::height(node<T> *p)
{
    if (p == NULL)
        return -1;
    else
        return p->height;
}

template <class T>
void AVLTree<T>::updateHeightAndBalance(node<T> *p)
{
    if (p != NULL)
    {
        int leftHeight = height(p->left);
        int rightHeight = height(p->right);
        p->height = max(leftHeight, rightHeight) + 1;
        p->balance = rightHeight - leftHeight;
    }
}

template <class T>
void AVLTree<T>::balance(node<T> *&p)
{
    if (p->balance < -1)
    {
        if (p->left->balance > 0)
            rotateLeft(p->left);
        rotateRight(p);
    }
    else if (p->balance > 1)
    {
        if (p->right->balance < 0)
            rotateRight(p->right);
        rotateLeft(p);
    }
}

template <class T>
void AVLTree<T>::insertNode(node<T> *&p, const T &item, bool &taller)
{
    if (p == NULL)
    {
        p = new node<T>;
        p->info = item;
        p->left = NULL;
        p->right = NULL;
        p->balance = 0;
        p->height = 0;
        taller = true;
    }
    else if (p->info == item)
        cout << "Error: duplicates not allowed" << endl; // TODO: Raise error
    else if (item < p->info)
        insertNode(p->left, item, taller);
    else
        insertNode(p->right, item, taller);

    updateHeightAndBalance(p);
    balance(p);
}

template <class T>
void AVLTree<T>::rotateLeft(node<T> *&p)
{
    // TODO: throw error if p null or p->right is null
    node<T> *q = p->right;
    p->right = q->left;
    q->left = p;
    updateHeightAndBalance(p);
    updateHeightAndBalance(q);
    p = q;
}

template <class T>
void AVLTree<T>::rotateRight(node<T> *&p)
{
    // TODO: throw error if p null or p->left is null
    node<T> *q = p->left;
    p->left = q->right;
    q->right = p;
    updateHeightAndBalance(p);
    updateHeightAndBalance(q);
    p = q;
}

template <class T>
void AVLTree<T>::inOrder(node<T> *p, function<void(node<T> *)> func)
{
    if (p != NULL)
    {
        inOrder(p->left, func);
        func(p);
        inOrder(p->right, func);
    }
}

template <class T>
void AVLTree<T>::preOrder(node<T> *p, function<void(node<T> *)> func)
{
    if (p != NULL)
    {
        func(p);
        preOrder(p->left, func);
        preOrder(p->right, func);
    }
}

template <class T>
void AVLTree<T>::postOrder(node<T> *p, function<void(node<T> *)> func)
{
    if (p != NULL)
    {
        postOrder(p->left, func);
        postOrder(p->right, func);
        func(p);
    }
}

template <class T>
void AVLTree<T>::destroyTree()
{
    postOrder(root, [](node<T> *p)
              { delete p; });
}

template <class T>
void AVLTree<T>::copyTree(node<T> *&dest, node<T> *src)
{
    if (src == NULL)
        dest = NULL;
    else
    {
        dest = new node<T>;
        dest->info = src->info;
        dest->height = src->height;
        dest->balance = src->balance;
        copyTree(dest->left, src->left);
        copyTree(dest->right, src->right);
    }
}

template <class T>
void AVLTree<T>::printPreOrder()
{
    preOrder(root, [](node<T> *p)
             { cout << p->info << " "; });
    cout << endl;
}

template <class T>
void AVLTree<T>::printInOrder()
{
    inOrder(root, [](node<T> *p)
            { cout << p->info << " "; });
    cout << endl;
}

template <class T>
void AVLTree<T>::printPostOrder()
{
    postOrder(root, [](node<T> *p)
              { cout << p->info << " "; });
    cout << endl;
}
