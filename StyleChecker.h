/**
 * @file StyleChecker.h
 * @author Mike Boyle
 * @brief header file for style checker
 * @date 2022-05-19
 *
 */

#ifndef STYLE_CHECKER_H
#define STYLE_CHECKER_H

#include "AVLTree.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class StyleChecker
{
private:
    string inFilePath;
    string outFilePath;
    fstream outFile;

    AVLTree<string> paragraphs;
    AVLTree<string> sentences;
    AVLTree<string> words;
    AVLTree<string> longWords; // words longer than 3 letters

    int numWords;
    int totalWordLength;
    int numLongWords;
    int numOverusedWords;
    vector<string> overusedWords;
    char currIndexHeading;

    // isSentenceDelimiter returns true if the character is '.', '!', or '?'
    bool isSentenceDelimiter(const char &);

    // parseFile opens the file and inserts lines (paragraphs)
    // into the paragraphs tree
    void parseFile();

    // parseParagraphs traverses the paragraphs tree
    // and inserts sentences into the sentences tree
    void parseParagraphs();

    // parseSentences traverses the sentences tree
    // and inserts words into the words tree
    void parseSentences();

    // parseWords traverses the words tree
    // and does some analysis on each word
    void parseWords();

    void analyzeLongWords();

    void analyzeText();

    void handleParagraph(const string &);
    void handleSentence(const string &);
    void analyzeLongWordData(treeNodeData<string> *);
    string tokenizeWord(const string &);
    void printIndex();

public:
    StyleChecker(const string &, const string & = "report.txt");
    ~StyleChecker();
    string getOutFilePath();
    void analyze();
};

#endif
