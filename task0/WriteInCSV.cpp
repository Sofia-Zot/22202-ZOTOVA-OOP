#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

using std::string;
using std::vector;
using std::pair;

#include "WriteInCSV.h"

void WriteInCSV::open() {
    this->file->open(fileName);
}

void WriteInCSV::close() {
    if (file->is_open()) {
        file->close();
    }
    this->file->close();
}

void WriteInCSV::createLine(const vector<string> &word) {
    if (!file->is_open()) {
        return;
    }
    string line;
    for (const auto &item : word) {
        line += item + '\t';
    }
    line[line.size() - 1] = '\n';
    writeToFile(line);
}

void WriteInCSV::writeToFile(const string &line) {
    *file << line;
}