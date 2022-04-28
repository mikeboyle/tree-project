/**
 * @file main.cpp
 * @author Mike Boyle
 * @brief header file for AVL Tree
 * @date 2022-05-19
 *
 */
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include "node.h"
#include <functional>
#include <string>

using namespace std;

template <class T>
class AVLTree
{
private:
    node<T> *root;
    // insertNode inserts a node in the tree
    void insertNode(node<T> *&, const T &, bool &);
    // inOrder traverses the tree in order and executes a function on the node
    void inOrder(node<T> *, function<void(node<T> *)>);
    // preOrder traverses the tree preorder and executes a function on the node
    void preOrder(node<T> *, function<void(node<T> *)>);
    // postOrder traverses the tree post order and executes a function on the node
    void postOrder(node<T> *, function<void(node<T> *)>);
    // destroyTree deletes all of the nodes in the list
    void destroyTree();
    // copyTree copies the tree
    void copyTree(const AVLTree<T> &);

    // ROTATION FUNCTIONS

    // rotateLeft rotates the node to the left
    // by promoting the node p's right child to be p's parent
    void rotateLeft(node<T> *&);
    // rotateRight rotates the node to the right
    // by promoting the node p's left child to be p's parent
    void rotateRight(node<T> *&);

    void balanceLeft(node<T> *&);
    void balanceRight(node<T> *&);

public:
    AVLTree();
    ~AVLTree();
    // insert adds a node to the tree
    void insert(const T &);
    // printInOrder prints the tree elements inorder
    void printInOrder();
    // printPreOrder prints the tree elements preorder
    void printPreOrder();
    // printPostOrder prints the tree elements postorder
    void printPostOrder();
};

#endif