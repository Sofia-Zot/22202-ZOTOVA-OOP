#include <fstream>
#include <string>

#include "FileReader.h"

using std::string;
using std::ifstream;

FileReader::FileReader(const string &fileName) {
    this->fileName = fileName;
    this->file = new ifstream();
}

void FileReader::open() {
    this->file->open(fileName);
}

string FileReader::next() {
    string line;
    getline(*file, line);
    return line;
}

bool FileReader::hasNext() {
    return !file->eof();
}

void FileReader::close() {
    file->close();
    delete file;
}

void FileReader::reset() {
    file->seekg(0);
}