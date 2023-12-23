#include <gtest/gtest.h>
#include "WriteInCSV.h"
#include "WriteInCSV.cpp"
#include <fstream>

TEST(FileWriter, writeToFile) {
    string line = "test";
    WriteInCSV writer("test.txt");
    writer.open();
    writer.writeToFile(line);
    writer.close();
    ifstream file("test.txt");
    string res;
    getline(file, res);
    EXPECT_EQ(res, line);
}