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
    char currIndexHeading;

    // parseFile opens the file and inserts lines (paragraphs)
    // into the paragraphs tree
    void parseFile();

    // parseParagraphs traverses the paragraphs tree
    // and inserts sentences into the sentences tree
    void parseParagraphs();

    // parseSentences traverses the sentences tree
    // and inserts words into the words tree
    void parseSentences();

    // analyzeLongWords traverses the tree of long words
    // and outputs any long words that are overused
    void analyzeLongWords();

    // analyzeText writes analysis statistics to the output file
    void analyzeText();

    // printIndex prints the index of unique words to the output file
    void printIndex();

    // printIndex entry prints a single entry to the index.
    // It will also print the next heading if needed
    void printIndexEntry(const string &);

    // handleParagraph parses a single paragraph into sentences
    // and adds each sentence to the sentences treee
    void handleParagraph(const string &);

    // handleSentences parses a single paragraph into words,
    // normalizes the words as tokens, and inserts each token
    // into the words tree and longerWords tree
    void handleSentence(const string &);

    // analyzeLongWordData accepts data from a single tree node
    // and determines if the word is overused
    void analyzeLongWordData(treeNodeData<string> *);

    // tokenizeWord strips a word of non-letter characters and lowercases it
    string tokenizeWord(const string &);

    // isSentenceDelimiter returns true if the character is '.', '!', or '?'
    bool isSentenceDelimiter(const char &);

public:
    StyleChecker(const string &, const string & = "report.txt");
    ~StyleChecker();
    string getOutFilePath();
    void analyze();
};

#endif
