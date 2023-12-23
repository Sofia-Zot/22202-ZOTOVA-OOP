#ifndef UNTITLED_FILEREADER_H
#define UNTITLED_FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;

class FileReader {
private:
    string fileName;
    ifstream *file;
public:
    FileReader(const string &fileName);

    void open();

    string next();

    bool hasNext();

    void close();

    void reset();
};

#endif //UNTITLED_FILEREADER_H
