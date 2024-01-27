#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Function to convert a string to lowercase
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to display the top N most used words
void displayTopWords(const map<string, int>& wordCount, int topN) {
    // Create a vector of pairs to sort by word occurrences
    vector<pair<string, int>> sortedWords(wordCount.begin(), wordCount.end());

    // Sort the vector based on word occurrences in descending order
    sort(sortedWords.begin(), sortedWords.end(),
         [](const auto& a, const auto& b) {
             return a.second > b.second;
         });

    // Display the top N words
    cout << "\nTop " << topN << " Most Used Words:\n";
    for (size_t i = 0; i < min(sortedWords.size(), static_cast<size_t>(topN)); ++i) {
        cout << sortedWords[i].first << ": " << sortedWords[i].second << endl;
    }
}

int main() {
    // Prompt the user for the file name
    cout << "Enter the name of the text file: ";
    string fileName;
    cin >> fileName;

    // Open and read the user-specified text file
    ifstream inputFile(fileName);

    // Check if the file is open
    if (!inputFile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    // Map to store word occurrences
    map<string, int> wordCount;

    // Read words from the file
    string word;
    while (inputFile >> word) {
        // Convert word to lowercase and increment word count in the map
        wordCount[toLowercase(word)]++;
    }

    // Close the file
    inputFile.close();

    // Display UI
    int choice;
    do {
        cout << "\n===== Menu =====\n";
        cout << "1. Display Total Word Count\n";
        cout << "2. Display Unique Word Count\n";
        cout << "3. Display All Word Occurrences\n";
        cout << "4. Display Top 5 Most Used Words\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nTotal Word Count: " << wordCount.size() << endl;
                break;

            case 2:
                cout << "Unique Word Count: " << wordCount.size() << endl;
                break;

            case 3:
                cout << "\nWord Occurrences:\n";
                for (const auto& entry : wordCount) {
                    cout << entry.first << ": " << entry.second << endl;
                }
                break;

            case 4:
                displayTopWords(wordCount, 5);
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 0);

    return 0;
}
