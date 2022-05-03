/**
 * @file StyleChecker.cpp
 * @author Mike Boyle
 * @brief Implementation file for Style Checker
 * @date 2022-05-19
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include "StyleChecker.h"

const float OVERUSE_THRESHOLD = 0.05;
const int LENGTH_THRESHOLD = 3;

StyleChecker::StyleChecker(const string &in, const string &out)
{
    inFilePath = in;
    outFilePath = out;

    numWords = 0;
    totalWordLength = 0;
    numLongWords = 0;
    numOverusedWords = 0;
}

StyleChecker::~StyleChecker()
{
}

string StyleChecker::getOutFilePath()
{
    return outFilePath;
}

void StyleChecker::parseParagraphs()
{
    function<void(string)> callback = [this](string p)
    { StyleChecker::handleParagraph(p); };

    paragraphs.inOrder(callback);
}

void StyleChecker::parseSentences()
{
    function<void(string)> callback = [this](string s)
    { StyleChecker::handleSentence(s); };

    sentences.inOrder(callback);
}

void StyleChecker::analyzeLongWords()
{
    function<void(treeNodeData<string> * w)> callback = [this](treeNodeData<string> *w)
    { StyleChecker::analyzeLongWordData(w); };

    outFile << "WORDS USED TOO OFTEN" << endl;

    longWords.inOrder(callback);

    if (numOverusedWords == 0)
        outFile << "None" << endl;
}

bool StyleChecker::isSentenceDelimiter(const char &c)
{
    return c == '.' || c == '!' || c == '?' || c == '\n';
}

void StyleChecker::handleParagraph(const string &paragraph)
{
    // split paragraph into sentences
    char curr;
    int sentenceLength;
    int start = 0;

    for (int i = 0; i < paragraph.length(); i++)
    {
        curr = paragraph[i];
        // If the current character is a sentence delimiter at the end of a sentence
        // (NOT a . in $2.00 for example)
        if (isSentenceDelimiter(curr) && (i == paragraph.length() - 1 || paragraph[i + 1] == ' '))
        {
            if (paragraph[start] == ' ') // Strip space from start of sentence
                start++;

            sentenceLength = i - start;
            sentences.insert(paragraph.substr(start, sentenceLength));
            start = i + 1;
        }
    }
}

void StyleChecker::handleSentence(const string &sentence)
{
    string word, token;
    stringstream ss(sentence);
    int tokenLength;

    while (getline(ss, word, ' '))
    {
        token = tokenizeWord(word);
        tokenLength = token.length();
        if (tokenLength > 0)
        {
            numWords++;
            totalWordLength += tokenLength;
            words.insert(token);
        }
        if (tokenLength > LENGTH_THRESHOLD)
        {
            numLongWords++;
            longWords.insert(token);
        }
    }
}

void StyleChecker::analyzeLongWordData(treeNodeData<string> *node)
{
    string word = node->info;
    int count = node->count;

    if (count > numLongWords * OVERUSE_THRESHOLD)
    {
        numOverusedWords++;
        outFile << numOverusedWords << ") " << word << " (" << count << " times)" << endl;
    }
}

void StyleChecker::printIndex()
{
    function<void(string)> callback = [this](string w)
    { printIndexEntry(w); };

    outFile << endl;
    outFile << "INDEX OF UNIQUE WORDS" << endl;

    words.inOrder(callback);
}

void StyleChecker::printIndexEntry(const string &w)
{
    if (currIndexHeading != w[0])
    {
        currIndexHeading = w[0];
        char upper = toupper(currIndexHeading);
        outFile << endl
                << upper << endl;
    }
    outFile << w << endl;
}

void StyleChecker::analyzeText()
{

    outFile << "FILE NAME: " << inFilePath << endl
            << endl;

    outFile << "STATISTICAL SUMMARY" << endl;
    outFile << "TOTAL NUMBER OF WORDS: " << numWords << endl;
    outFile << "TOTAL NUMBER OF UNIQUE WORDS: " << words.getSize() << endl;
    outFile << "TOTAL NUMBER OF UNIQUE WORDS > 3 LETTERS: " << longWords.getSize() << endl;
    outFile << "AVERAGE WORD LENGTH: " << totalWordLength / numWords << " characters" << endl;
    outFile << "AVERAGE SENTENCE LENGTH: " << numWords / sentences.getSize() << " words" << endl
            << endl;

    analyzeLongWords();
    printIndex();
}

string StyleChecker::tokenizeWord(const string &word)
{
    char curr;
    string s = "";
    for (int i = 0; i < word.length(); i++)
    {
        curr = word[i];
        if (curr >= 97 && curr <= 122) // if lowercase a-z, add to string
            s += curr;
        else if (curr >= 65 && curr <= 90) // if uppercase A-Z, add as lowercase
            s += tolower(curr);
    }

    return s;
}

void StyleChecker::parseFile()
{
    string paragraph;
    fstream file(inFilePath, ios::in);

    if (file.is_open())
    {
        while (getline(file, paragraph))
            paragraphs.insert(paragraph);
        file.close();
    }
    else
        cout << "Could not open file " << inFilePath << endl;

    parseParagraphs();
    parseSentences();
}

void StyleChecker::analyze()
{
    parseFile();

    outFile.open(outFilePath, ios::out);
    if (outFile.is_open())
    {
        analyzeText();
        outFile.close();
    }
    else
        cout << "Could not open file " << outFilePath << endl;

    // reset summary statistics for next run
    numWords = 0;
    totalWordLength = 0;
    numLongWords = 0;
    numOverusedWords = 0;

    char newCurrIdx;
    currIndexHeading = newCurrIdx;

    AVLTree<string> newParagraphs;
    paragraphs = newParagraphs;

    AVLTree<string> newSentences;
    sentences = newSentences;

    AVLTree<string> newWords;
    words = newWords;

    AVLTree<string> newLongWords;
    longWords = newLongWords;
}