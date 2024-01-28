/**********************************************************************************/
/* Name: Alec Day
*  Teacher: Brother Godderidge
*  Date: January 27th, 2024
*
*  Description: This code is used to Read and Analyze files and generate some basic
*  statistics on what is inside of the file such as; General Word Count, word specific 
*  count (how man times the word showed up), and a statistical summary including
*  average word variation, standard deviation count, and average word size
/************************************************************************************/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>  // For setprecision and fixed
#include <cmath>    // For sqrt function

using namespace std;

/**********************************************************************************
 * Function to convert a string to lowercase, uses 'const string& str' in order 
 * to make sure the original string passed won't be modified, and stops the program
 * from copying potentially large objects that would take up too much space and
 * cause the program to run slower 
 * ********************************************************************************/
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

/**********************************************************************************
 * Function to display the top N most used words. Creates a vector of pairs to 
 * sort by word occurrences. Sorts the vector based on word occurrences in 
 * descending order, and displays the top N words
 * ********************************************************************************/
void displayTopWords(const map<string, int>& wordCount, int topN) {
    vector<pair<string, int>> sortedWords(wordCount.begin(), wordCount.end());

    sort(sortedWords.begin(), sortedWords.end(),
         [](const auto& a, const auto& b) {
             return a.second > b.second;
         });

    cout << "\nTop " << topN << " Most Used Words:\n";
    for (size_t i = 0; i < min(sortedWords.size(), static_cast<size_t>(topN)); ++i) {
        cout << sortedWords[i].first << ": " << sortedWords[i].second << endl;
    }
}

/************************************************************************************
 * Function to calculate average word size. calculateAverageWordSize computes 
 * the average word size (in characters) based on the length of each word and 
 * its frequency in the wordCount map. It returns a double representing the 
 * average word size
 * *********************************************************************************/
double calculateAverageWordSize(const map<string, int>& wordCount) {
    double totalSize = 0.0;
    double totalWords = 0.0;

    for (const auto& entry : wordCount) {
        totalSize += entry.first.length() * entry.second;
        totalWords += entry.second;
    }

    return (totalWords > 0) ? (totalSize / totalWords) : 0.0;
}

/************************************************************************************
 * Function to display statistical summary. 
 * *********************************************************************************/
void displaySummary(const map<string, int>& wordCount) {
    cout << "\n===== Summary =====\n";
    cout << "Total Word Count: " << wordCount.size() << endl;

    if (!wordCount.empty()) {
        // Calculate average word frequency
        double averageFrequency = 0.0;
        for (const auto& entry : wordCount) {
            averageFrequency += entry.second;
        }
        averageFrequency /= wordCount.size();

        // Calculate variability of word frequency (standard deviation)
        double variabilitySum = 0.0;
        for (const auto& entry : wordCount) {
            double diff = entry.second - averageFrequency;
            variabilitySum += diff * diff;
        }
        double wordFrequencyVariability = sqrt(variabilitySum / wordCount.size());

        // Calculate average word size
        double averageWordSize = calculateAverageWordSize(wordCount);

        cout << fixed << setprecision(2);  // Set precision for floating-point output
        cout << "Average Word Frequency: " << averageFrequency << endl;
        cout << "Word Frequency Variability: " << wordFrequencyVariability << endl;
        cout << "Average Word Size: " << averageWordSize << " characters\n";

        // Explanation of Average Word Frequency
        cout << "\nAverage Word Frequency represents the average number of times each word appears in the text.\n"
             << "For example, if the average frequency is 5, it means that, on average, each word appears 5 times.\n";

        // Explanation of variability (standard deviation)
        cout << "\nWord Frequency Variability (standard deviation) measures how much word frequencies deviate from the average.\n"
             << "A lower variability indicates that the words tend to be close to the mean (less variability in vocabulary),\n"
             << "while a higher variability indicates a wider range of frequency values (more variability in vocabulary).\n";
    } else {
        cout << "No words found in the file.\n";
    }
}

/****************************************************************************************
 * Main Function; Opens and reads the user-specified text file, checks if the file is 
 * open, uses a Map to store word occurrences, reads words from the file, closes the file,
 * and displays a UI to the user. The user can chose from a list of options which is 
 * stored inside a switch statement. The options call each of the functions above
*****************************************************************************************///     
int main() {
    cout << "Enter the name of the text file: ";
    string fileName;
    cin >> fileName;

    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    map<string, int> wordCount;

    string word;
    while (inputFile >> word) {
        // Convert word to lowercase and increment word count in the map
        wordCount[toLowercase(word)]++;
    }

    inputFile.close();

    int choice;
    do {
        cout << "\n===== Menu =====\n";
        cout << "1. Display Total Word Count\n";
        cout << "2. Display All Word Occurrences\n";
        cout << "3. Display Top 5 Most Used Words\n";
        cout << "4. Display Summary Statistics\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nTotal Word Count: " << wordCount.size() << endl;
                break;

            case 2:
                cout << "\nWord Occurrences:\n";
                for (const auto& entry : wordCount) {
                    cout << entry.first << ": " << entry.second << endl;
                }
                break;

            case 3:
                displayTopWords(wordCount, 5);
                break;

            case 4:
                displaySummary(wordCount);
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