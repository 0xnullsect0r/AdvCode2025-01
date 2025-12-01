#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Rotation {
    char direction;
    int distance;
};

int countZeroCrossings(int start, char direction, int distance) {
    int count = 0;
    int current = start;

    for (int i = 0; i < distance; i++) {
        if (direction == 'L') {
            current = (current - 1 + 100) % 100;
        } else {
            current = (current + 1) % 100;
        }

        if (current == 0) {
            count++;
        }
    }

    return count;
}

int main() {
    ifstream input("input.txt");

    if (!input.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    vector<Rotation> rotations;
    string line;

    // Read all rotations
    while (getline(input, line)) {
        if (!line.empty()) {
            Rotation rot;
            rot.direction = line[0];
            rot.distance = stoi(line.substr(1));
            rotations.push_back(rot);
        }
    }

    input.close();

    // Part 1: Count times dial ends at 0
    int current = 50;
    int part1_count = 0;

    for (const auto& rot : rotations) {
        if (rot.direction == 'L') {
            current = (current - rot.distance % 100 + 100) % 100;
        } else {
            current = (current + rot.distance % 100) % 100;
        }

        if (current == 0) {
            part1_count++;
        }
    }

    cout << "Part 1 - Times dial ends at 0: " << part1_count << endl;

    // Part 2: Count all times dial points at 0 (including during rotations)
    current = 50;
    int part2_count = 0;

    for (const auto& rot : rotations) {
        int crossings = countZeroCrossings(current, rot.direction, rot.distance);
        part2_count += crossings;

        // Update current position
        if (rot.direction == 'L') {
            current = (current - rot.distance % 100 + 100) % 100;
        } else {
            current = (current + rot.distance % 100) % 100;
        }
    }

    cout << "Part 2 - Total times dial points at 0: " << part2_count << endl;

    return 0;
}