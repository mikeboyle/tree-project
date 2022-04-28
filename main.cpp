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

void handleInsert(AVLTree<int> &tree, const int &item)
{
    tree.insert(item);
    tree.printPreOrder();
}

int main()
{
    AVLTree<int> tree;
    int items[] = {5, 3, 10, 15, 20, 7};
    for (int i = 0; i < 6; i++)
        handleInsert(tree, items[i]);
    // tree.insert(5);
    // tree.insert(10);
    // tree.insert(15);
    // tree.printPreOrder();
    // tree.insert(20);
    // tree.printPreOrder();
    // tree.insert(30);
    // tree.printPreOrder();
    // tree.insert(40);
    // tree.printPreOrder();

    // AVLTree<int> tree2;
    // tree2.insert(8);
    // tree2.insert(7);
    // tree2.insert(6);
    // tree2.printPreOrder();
    return 0;
}