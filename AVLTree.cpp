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
void AVLTree<T>::insert(const T &item)
{
    bool taller = false;
    insertNode(root, item, taller);
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
        taller = true;
    }
    else if (p->info == item)
        cout << "Error: duplicates not allowed" << endl; // TODO: Raise error
    else if (item < p->info)
    {
        insertNode(p->left, item, taller);
        if (taller)
        {
            if (p->balance == LEFT_TALLER)
            {
                balanceLeft(p);
                taller = false;
            }
            else if (p->balance == RIGHT_TALLER)
            {
                p->balance = BALANCED;
                taller = false;
            }
            else
                p->balance = LEFT_TALLER;
        }
    }
    else
    {
        insertNode(p->right, item, taller);
        if (taller)
        {
            if (p->balance == RIGHT_TALLER)
            {
                balanceRight(p);
                taller = false;
            }
            else if (p->balance == LEFT_TALLER)
            {
                p->balance = BALANCED;
                taller = false;
            }
            else
                p->balance = RIGHT_TALLER;
        }
    }
}

template <class T>
void AVLTree<T>::balanceLeft(node<T> *&p)
{
    node<T> *l = p->left;

    if (l->balance == LEFT_TALLER)
    {
        p->balance = BALANCED;
        l->balance = BALANCED;
        rotateRight(p);
    }
    else if (l->balance == RIGHT_TALLER)
    {
        node<T> *r = l->right;
        if (r->balance == LEFT_TALLER)
        {
            p->balance = RIGHT_TALLER;
            l->balance = BALANCED;
        }
        else if (r->balance == RIGHT_TALLER)
        {
            p->balance = BALANCED;
            l->balance = LEFT_TALLER;
        }
        else
        {
            p->balance = BALANCED;
            l->balance = BALANCED;
        }
        r->balance = BALANCED;
        rotateLeft(l);
        p->left = l;
        rotateRight(p);
    }
    else
        cout << "Error balancing left" << endl;
}

template <class T>
void AVLTree<T>::balanceRight(node<T> *&p)
{
    node<T> *r = p->right;

    if (r->balance == RIGHT_TALLER)
    {
        p->balance = BALANCED;
        r->balance = BALANCED;
        rotateLeft(p);
    }
    else if (r->balance == LEFT_TALLER)
    {
        node<T> *l = r->left;
        if (l->balance == RIGHT_TALLER)
        {
            p->balance = LEFT_TALLER;
            r->balance = BALANCED;
        }
        else if (l->balance == LEFT_TALLER)
        {
            p->balance = BALANCED;
            r->balance = RIGHT_TALLER;
        }
        else
        {
            p->balance = BALANCED;
            r->balance = BALANCED;
        }
        l->balance = BALANCED;
        rotateRight(r);
        p->right = r;
        rotateLeft(p);
    }
    else
        cout << "Error balancing right" << endl;
}

template <class T>
void AVLTree<T>::rotateLeft(node<T> *&p)
{
    // TODO: throw error if p null or p->right is null
    node<T> *q = p->right;
    p->right = q->left;
    q->left = p;
    p = q;
}

template <class T>
void AVLTree<T>::rotateRight(node<T> *&p)
{
    // TODO: throw error if p null or p->left is null
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
