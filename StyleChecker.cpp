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

void StyleChecker::parseParagraphs()
{
    paragraphs.inOrder([this](string p)
                       { StyleChecker::handleParagraph(p); });
}

void StyleChecker::parseSentences()
{
    sentences.inOrder([this](string s)
                      { StyleChecker::handleSentence(s); });
}

void StyleChecker::analyzeLongWords()
{
    cout << "WORDS USED TOO OFTEN" << endl;

    longWords.inOrder([this](treeNodeData<string> *w)
                      { StyleChecker::analyzeLongWordData(w); });

    if (numOverusedWords == 0)
        cout << "None" << endl;
}

bool StyleChecker::isSentenceDelimiter(const char &c)
{
    return c == '.' || c == '!' || c == '?' || c == '\n';
}

void StyleChecker::handleParagraph(const string &paragraph)
{
    // split paragraph into sentences
    char curr;
    bool delimiterFound;
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
        cout << numOverusedWords << ") " << word << " (" << count << " times)" << endl;
    }
}

void StyleChecker::analyzeText()
{

    cout << "FILE NAME: " << inFilePath << endl
         << endl;

    cout << "STATISTICAL SUMMARY" << endl;
    cout << "TOTAL NUMBER OF WORDS: " << numWords << endl;
    cout << "TOTAL NUMBER OF UNIQUE WORDS: " << words.getSize() << endl;
    cout << "TOTAL NUMBER OF UNIQUE WORDS > 3 LETTERS: " << longWords.getSize() << endl;
    cout << "AVERAGE WORD LENGTH: " << totalWordLength / numWords << " characters" << endl;
    cout << "AVERAGE SENTENCE LENGTH: " << numWords / sentences.getSize() << " words" << endl
         << endl;

    analyzeLongWords();
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

        parseParagraphs();
        parseSentences();
        analyzeText();
    }
    else
        cout << "Could not open file " << inFilePath << endl;
}

void StyleChecker::analyze()
{
    parseFile();
    // TODO: reset statistics for next run
}