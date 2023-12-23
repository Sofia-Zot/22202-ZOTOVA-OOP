#ifndef UNTITLED_STATISTICSTORAGE_H
#define UNTITLED_STATISTICSTORAGE_H

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;
using std::map;

class StatisticStorage {
private:
    std::map<std::string, int> statistics;
    int total = 0;
public:
    void addWord(const std::string& word);
    bool hasWord(const std::string& word) const;
    std::vector<std::pair<std::string, int>> sortStatistics();
    int getTotal() const;
    void clear();
};
#endif //UNTITLED_STATISTICSTORAGE_H
