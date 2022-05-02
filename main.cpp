/**
 * @file main.cpp
 * @author Mike Boyle
 * @brief Test driver for Tree Project
 * @date 2022-05-19
 *
 */
#include <iostream>
#include <iostream>
#include <fstream>
#include "StyleChecker.h"

using namespace std;

int main()
{
    string fileName = "in.txt";
    cout << "Enter a file name: ";
    getline(cin, fileName);

    StyleChecker sc(fileName);
    sc.analyze();
    cout << "Here is your report. A copy is also saved to " << sc.getOutFilePath() << "." << endl;

    string paragraph;
    string outFilePath = sc.getOutFilePath();
    fstream file(outFilePath, ios::in);

    if (file.is_open())
    {
        while (getline(file, paragraph))
            cout << paragraph << endl;
    }
    else
        cout << "Could not open file " << outFilePath << endl;

    return 0;
}
