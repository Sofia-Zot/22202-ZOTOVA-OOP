#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using std::string;
using std::vector;

class Parser {
private:
    static bool isSeparator(char c);

public:
    static vector<string> splitLineIntoWords(string& line);
};

#endif //UNTITLED_PARSER_H
