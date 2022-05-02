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

using namespace std;

class StyleChecker
{
private:
    AVLTree<string> paragraphs;
    AVLTree<string> sentences;
    AVLTree<string> words;
    AVLTree<string> longWords; // words longer than 3 letters
    string inFilePath;
    string outFilePath;
    int numWords;
    int totalWordLength;
    int numLongWords;
    int numOverusedWords;
    vector<string> overusedWords;

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

public:
    StyleChecker(const string &, const string & = "report.txt");
    ~StyleChecker();
    void analyze();
};

#endif

// Update AVL:
// track total number of nodes (unique words)
// track number of nodes w/ info > 3 letters

// Properties
// private AVLTree
// int total words
// int total unique words (from AVL tree)
// int total unique words more than 3 letters (from AVL tree)
// int total word length
// int num sentences
// int total sentence length
// vector<string> overused words
// array of linked list<string> index

// INPUT FUNCTION
// open file and process input
// split into sentences
// for each sentence..
//  increment num sentences
//  split into words
//  for each word...
//      discard non-letters and convert to lowercase
//      increment total words
//      increment total word length
//      insert into the tree
//  set total unique words, total unique words > 3 (from AVL tree)

// Analysis function
// Traverse tree inorder
// For each node...
//     increment total unique words
//     if length > 3 && count > (total unique >3 words * .05)
//          add to overused words
//     add to index using 0-26 int to map to the array of LLs
//
//
//  Write stat summary and style warnings to file
//  Write the index to the file
//