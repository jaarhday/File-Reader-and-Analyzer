#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main() {
    // Open and read the text file
    ifstream inputFile("test.txt");

    // Check if the file is open
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    // Map to store word occurrences
    map<string, int> wordCount;

    // Read words from the file
    string word;
    while (inputFile >> word) {
        // Increment word count in the map
        wordCount[word]++;
    }

    // Display results
    for (const auto& entry : wordCount) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // Close the file
    inputFile.close();

    return 0;
}
