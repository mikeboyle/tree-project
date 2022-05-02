/**
 * @file main.cpp
 * @author Mike Boyle
 * @brief Test driver for Tree Project
 * @date 2022-05-19
 *
 */
#include <iostream>
#include "StyleChecker.h"
#include <iostream>

using namespace std;

// void handleInsert(AVLTree<int> &tree, const int &item)
// {
//     tree.insert(item);
//     tree.printPreOrder();
// }

int main()
{
    string fileName = "in.txt";
    // cout << "Enter a file name: " << endl;
    // getline(cin, fileName);

    StyleChecker sc(fileName);
    sc.analyze();
    // AVLTree<int> tree;
    // int items[] = {5, 3, 10, 15, 20, 7};
    // for (int i = 0; i < 6; i++)
    //     handleInsert(tree, items[i]);
    // AVLTree<int> tree2(tree);
    // tree2.printInOrder();
    // tree.printInOrder();
    // AVLTree<int> tree3;
    // tree3.insert(50);
    // tree3.insert(40);
    // tree3.insert(30);
    // tree3.insert(20);
    // tree3.insert(10);
    // tree2 = tree3;
    // tree3.printInOrder();
    // tree2.printInOrder();
    // tree.printInOrder();

    return 0;
}
