#ifndef UNTITLED_WRITEINCSV_H
#define UNTITLED_WRITEINCSV_H

#include <string>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;


using std::string;
using std::vector;
using std::pair;

class WriteInCSV {
private:
    string fileName;
    ofstream *file;

public:
    explicit WriteInCSV(const string &fileName){
        this->fileName = fileName;
        this->file = new ofstream();
    }

    void open();

    void close();

    void createLine(const vector<string> &word);

    void writeToFile(const string &line);
};

#endif //UNTITLED_WRITEINCSV_H
