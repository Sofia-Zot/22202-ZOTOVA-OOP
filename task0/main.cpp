#include <vector>
#include "FileReader.h"
#include "Parser.h"
#include "StatisticStorage.h"
#include "WriteInCSV.h"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 0;
    }


    string inputFile = string(argv[1]);
    string outputFile = string(argv[2]);
    FileReader fileReader(inputFile);
    fileReader.open();

    StatisticStorage storage;

    while (fileReader.hasNext()) {
        string str = fileReader.next();
        vector<string> words = Parser::splitLineIntoWords(str);
        for (auto &word: words) {
            storage.addWord(word);
        }
    }
    fileReader.close();

    auto sorted = storage.sortStatistics();
    int total = storage.getTotal();

    WriteInCSV csvWriter(outputFile);
    csvWriter.open();
    for (auto &item : sorted) {
        long double frequency = (long double) item.second / total;
        vector<string> word;
        word.emplace_back(item.first);
        word.emplace_back(to_string(item.second));
        word.emplace_back(to_string(frequency));
        csvWriter.createLine(word);
    }

    csvWriter.close();
    return 0;
}
