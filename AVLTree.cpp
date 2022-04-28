/**
 * @file AVLTree.cpp
 * @author Mike Boyle
 * @brief implementation file for AVL Tree
 * @date 2022-05-19
 *
 */

#include "AVLTree.h"
#include <string>

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
void AVLTree<T>::insert(const T &item)
{
    insertNode(root, item, false);
}

template <class T>
void AVLTree<T>::insertNode(node<T> *&p, const T &item, bool taller)
{
    if (p == NULL)
    {
        p = new node<T>;
        p->info = item;
        p->left = NULL;
        p->right = NULL;
        p->balanceFactor = 0;
    }
    else if (p->info == item)
        cout << "Error: duplicates not allowed" << endl; // TODO: Raise error
    else if (item < p->info)
        insertNode(p->left, item, taller);
    else
        insertNode(p->right, item, taller);
}

template <class T>
void AVLTree<T>::rotateLeft(node<T> *&p)
{
    node<T> *q = p->right;
    p->right = q->left;
    q->left = p;
    p = q;
}

template <class T>
void AVLTree<T>::rotateRight(node<T> *&p)
{
    node<T> *q = p->left;
    p->left = q->right;
    q->right = p;
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
    cout << "root = " << root->info << endl;
}

// TODO: Remove
template <class T>
void AVLTree<T>::testRotateLeft()
{
    rotateLeft(root);
    // cout << "root = " << root->info << endl;
}

// TODO: Remove
template <class T>
void AVLTree<T>::testRotateRight()
{
    rotateRight(root);
}
