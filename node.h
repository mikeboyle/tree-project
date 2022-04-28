/**
 * @file node.h
 * @author Mike Boyle
 * @brief header file for AVL Tree node
 * @date 2022-05-19
 *
 */

template <class T>
struct node
{
    T info;
    node *left;
    node *right;
    int balanceFactor;
};
