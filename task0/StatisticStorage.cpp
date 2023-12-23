#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::map;

#include "StatisticStorage.h"

void StatisticStorage::addWord(const std::string& word) {
    ++total;
    if (hasWord(word)) {
        ++statistics[word];
    } else {
        statistics[word] = 1;
    }
}

bool StatisticStorage::hasWord(const std::string& word) const {
    return statistics.find(word) != statistics.end();
}

std::vector<std::pair<std::string, int>> StatisticStorage::sortStatistics() {
    std::vector<std::pair<std::string, int>> sortedStatistics(statistics.begin(), statistics.end());
    std::sort(sortedStatistics.begin(), sortedStatistics.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return sortedStatistics;
}

int StatisticStorage::getTotal() const {
    return total;
}

void StatisticStorage::clear() {
    statistics.clear();
    total = 0;
}