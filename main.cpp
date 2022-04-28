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
    tree.printPostOrder();
    tree.testRotateLeft();
    tree.printPostOrder();

    AVLTree<int> tree2;
    tree2.insert(8);
    tree2.insert(7);
    tree2.insert(6);
    tree2.printPostOrder();
    tree2.testRotateRight();
    tree2.printPostOrder();
    return 0;
}