#include <gtest/gtest.h>
#include <fstream>
#include "FileReader.h"
#include "FileReader.cpp"

using namespace std;

TEST(FileReader, next) {
    ofstream file("test.txt");
    file << "test";
    file.close();
    FileReader fileReader("test.txt");
    fileReader.open();
    string line = fileReader.next();
    EXPECT_EQ("test", line);
}

TEST(FileReader, hasNext) {
    ofstream file("test.txt");
    file << "test";
    file.close();
    FileReader fileReader("test.txt");
    fileReader.open();
    fileReader.next();
    EXPECT_EQ(false, fileReader.hasNext());
}

