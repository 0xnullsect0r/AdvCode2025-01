#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    cout << "Enter the number of rotation lines, then paste your rotations:" << endl;

    int numLines;
    cin >> numLines;
    cin.ignore();

    vector<string> lines;
    string line;
    for (int i = 0; i < numLines; ++i) {
        getline(cin, line);
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (!line.empty()) lines.push_back(line);
    }

    cout << "\nProcessing " << lines.size() << " rotations...\n" << endl;

    int dial = 50;
    int password = 0;

    cout << "Starting position: " << dial << endl << endl;

    for (size_t i = 0; i < lines.size(); ++i) {
        string &s = lines[i];

        char direction = s[0];
        int distance = stoi(s.substr(1));

        // Apply rotation
        if (direction == 'L') {
            dial -= distance;
        } else if (direction == 'R') {
            dial += distance;
        }

        // Handle wrap-around (ensure dial is in range 0-99)
        dial = ((dial % 100) + 100) % 100;

        cout << "After " << s << ": dial points at " << dial << endl;

        // Check if dial points at 0
        if (dial == 0) {
            password++;
        }
    }

    cout << "\n====================" << endl;
    cout << "Password (times dial hit 0): " << password << endl;
    cout << "Final dial position: " << dial << endl;

    return 0;
}