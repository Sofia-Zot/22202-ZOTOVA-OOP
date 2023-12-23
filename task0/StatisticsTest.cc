#include <gtest/gtest.h>
#include "StatisticStorage.h"
#include "StatisticStorage.cpp"
#include <map>
#include <vector>
#include <utility>
#include <string>

using namespace std;

TEST(StatisticStorage, addWord) {
    vector<string> words = {"a", "a", "a", "b"};
    StatisticStorage statistic;
    for (auto const &word : words) {
        statistic.addWord(word);
    }
    std::vector<std::pair<std::string, int>> result = {{"a", 3}, {"b", 1}};
    EXPECT_EQ(result, statistic.sortStatistics());
}

TEST(Statistics, sortStatistic) {
    vector<string> words = {"a", "b", "c", "d"};
    StatisticStorage statistic;
    for (auto const &word : words) {
        statistic.addWord(word);
    }
    std::vector<std::pair<std::string, int>> result = {{"a", 1}, {"b", 1}, {"c", 1}, {"d", 1}};
    EXPECT_EQ(result, statistic.sortStatistics());
}