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

const int NUM_DELIMITERS = 4;
const char DELIMITERS[NUM_DELIMITERS] = {'.', '!', '?', '\n'};

StyleChecker::StyleChecker(const string &in, const string &out)
{
    inFilePath = in;
    outFilePath = out;

    numSentences = 0;
    totalSentenceLength = 0;
    numWords = 0;
    totalWordLength = 0;
}

StyleChecker::~StyleChecker()
{
}

void StyleChecker::handleParagraph(const string &paragraph)
{
    // split paragraph into sentences
    int start = 0;
    int sentenceLength;
    string sentence;
    char curr;
    bool delimiterFound;
    int j;

    for (int i = 0; i < paragraph.length(); i++)
    {
        curr = paragraph[i];
        j = 0;
        delimiterFound = false;
        while (j < NUM_DELIMITERS && !delimiterFound)
        {
            if (curr == DELIMITERS[j] && (i == paragraph.length() - 1 || paragraph[i + 1] == ' '))
            {
                delimiterFound = true;
                if (paragraph[start] == ' ')
                    start++;

                numSentences++;
                sentenceLength = i - start;
                totalSentenceLength += sentenceLength;
                sentence = paragraph.substr(start, sentenceLength);
                handleSentence(sentence);
                start = i + 1;
            }
            else
                j++;
        }
    }
}

void StyleChecker::handleSentence(const string &sentence)
{
    cout << "Found a sentence of length " << sentence.length() << endl;
    cout << sentence << endl;

    string word, token;
    stringstream ss;
    ss.str(sentence);
    int tokenLength;

    while (getline(ss, word, ' '))
    {
        token = tokenizeWord(word);
        tokenLength = token.length();
        if (tokenLength > 0)
        {
            cout << "token found! " << token << " length = " << token.length() << endl;
            numWords++;
            totalWordLength += tokenLength;
            // handleToken(token);
        }
    }
    cout << endl;
}

void StyleChecker::handleToken(const string &token)
{
    cout << token << " ";
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

void StyleChecker::analyzeFile()
{
    string paragraph;
    fstream file(inFilePath, ios::in);

    if (file.is_open())
    {
        cout << "Opened " << inFilePath << "!" << endl;
        while (getline(file, paragraph))
        {
            cout << "Next paragraph length = " << paragraph.length() << endl;
            cout << paragraph << endl;
            handleParagraph(paragraph);
        }
    }
    else
        cout << "Could not open file " << inFilePath << endl;
}