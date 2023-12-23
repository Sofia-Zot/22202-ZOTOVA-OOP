#include <string>
#include <vector>

#include "Parser.h"

using namespace std;

std::vector<std::string> Parser::splitLineIntoWords(std::string& line) {
    vector<string> words;
    if (line.empty()) {
        return words;
    }
    size_t beginWord = 0;
    size_t endWord = line.size() - 1;
    while (beginWord <= endWord) {
        while (beginWord <= endWord && isSeparator(line[beginWord])) {
            beginWord++;
        }
        for (size_t i = beginWord; i <= endWord; i++) {
            if (isSeparator(line[i])) {
                words.push_back(line.substr(beginWord, i - beginWord));
                beginWord = i + 1;
                break;
            } else if (i == endWord && !isSeparator(line[i])) {
                words.push_back(line.substr(beginWord, i - beginWord + 1));
                beginWord = i + 1;
            }
        }
    }
    return words;
}

bool Parser::isSeparator(char c) {
    return (!((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)));
}
