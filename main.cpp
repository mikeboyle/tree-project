/**
 * @file main.cpp
 * @author Mike Boyle
 * @brief Test driver for Tree Project
 * @date 2022-05-19
 *
 */
#include <iostream>
#include "AVLTree.cpp"

using namespace std;

int main()
{
    cout << "Hello, World!" << endl;
    AVLTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    tree.printPreOrder();
    tree.insert(20);
    tree.printPreOrder();
    tree.insert(30);
    tree.printPreOrder();
    tree.insert(40);
    tree.printPreOrder();

    AVLTree<int> tree2;
    tree2.insert(8);
    tree2.insert(7);
    tree2.insert(6);
    tree2.printPreOrder();
    return 0;
}