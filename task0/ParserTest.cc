#include <gtest/gtest.h>
#include "Parser.h"
#include "Parser.cpp"
#include <vector>

using std::string;
using std::vector;

TEST(Parser, 1) {
    string line = "a? a. a a";
    auto words = Parser::splitLineIntoWords(line);
    vector<string> result = {"a", "a", "a", "a"};
    EXPECT_EQ(words.size(), 4);
    EXPECT_EQ(result, words);
}

TEST(Parser, 2) {
    string line = "a,<><.,. ((a) a. a)";
    auto words = Parser::splitLineIntoWords(line);
    vector<string> result = {"a", "a", "a", "a"};
    EXPECT_EQ(words.size(), 4);
    EXPECT_EQ(result, words);
}

TEST(Parser, 3) {
    string line = "a, b/ c. d";
    auto words = Parser::splitLineIntoWords(line);
    vector<string> result = {"a", "b", "c", "d"};
    EXPECT_EQ(words.size(), 4);
    EXPECT_EQ(words, result);
}

TEST(Parser, 4) {
    string line = " ";
    auto words = Parser::splitLineIntoWords(line);
    vector<string> result = { };
    EXPECT_EQ(words.size(), 0);
    EXPECT_EQ(words, result);
}

TEST(Parser, 5) {
    string line = "#$ % & <> __";
    auto words = Parser::splitLineIntoWords(line);
    vector<string> result = { };
    EXPECT_EQ(words.size(), 0);
    EXPECT_EQ(words, result);
}