//
// Created by darian on 09.12.24.
//
#include "bits/stdc++.h"
using namespace std;

int main() {
    string line;
//    getline(cin, line);
    cin >> line;
    cout << line.size() << endl;
    vector<int> file_and_free_spaces; //-1 := .
    int currentId = 0;
    for (int i{}; i < line.size(); i++) {
        int count = line[i] - '0';
        const bool isOdd = i & 1;
        for (int j{}; j < count; j++) {
            if (isOdd) {
                file_and_free_spaces.push_back(-1);
            } else {
                file_and_free_spaces.push_back(currentId);
            }
        }
        if (!isOdd) {
            currentId++;
        }
    }

    cout  << "read:" << currentId << endl;
    //compressing

    while (file_and_free_spaces.back() == -1) file_and_free_spaces.pop_back();

    for (int i{}; i < file_and_free_spaces.size(); i++) {
        if (file_and_free_spaces[i] == -1) {
            file_and_free_spaces[i] = file_and_free_spaces.back();
            file_and_free_spaces.pop_back();
            while (file_and_free_spaces.back() == -1) file_and_free_spaces.pop_back();
        }

    }

    long long checksum = 0;
    for (long long i{}; i < file_and_free_spaces.size(); i++) {
        checksum += (i * (long long) file_and_free_spaces[i]);
    }
    cout << checksum << endl;
}