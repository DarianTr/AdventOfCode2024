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
// part 1
//    vector<int> file_and_free_spaces; //-1 := .
//    int currentId = 0;
//    for (int i{}; i < line.size(); i++) {
//        int count = line[i] - '0';
//        const bool isOdd = i & 1;
//        for (int j{}; j < count; j++) {
//            if (isOdd) {
//                file_and_free_spaces.push_back(-1);
//            } else {
//                file_and_free_spaces.push_back(currentId);
//            }
//        }
//        if (!isOdd) {
//            currentId++;
//        }
//    }
//
//    cout  << "read:" << currentId << endl;
//    //compressing
//
//    while (file_and_free_spaces.back() == -1) file_and_free_spaces.pop_back();
//
//    for (int i{}; i < file_and_free_spaces.size(); i++) {
//        if (file_and_free_spaces[i] == -1) {
//            file_and_free_spaces[i] = file_and_free_spaces.back();
//            file_and_free_spaces.pop_back();
//            while (file_and_free_spaces.back() == -1) file_and_free_spaces.pop_back();
//        }
//
//    }
//
//    long long checksum = 0;
//    for (long long i{}; i < file_and_free_spaces.size(); i++) {
//        checksum += (i * (long long) file_and_free_spaces[i]);
//    }
//    cout << checksum << endl;

vector<pair<int, int>> input;
int id = 0;
for (int i{}; i < line.size(); i++) {
    int count = line[i] - '0';
    if (i & 1) {
        input.emplace_back(-1, count);
    } else {
        input.emplace_back(id, count);
        id++;
    }
}

for (int i = id-1; i >= 0; --i) {
    int idx = -1;
    for (int j{}; j < input.size(); j++) {
        if (input[j].first == i) {
            idx = j;
            break;
        }
    }
    for (int j{}; j < idx; j++) {
        if ((input[j].first == -1) && (input[j].second >= input[idx].second)) {
            if (input[j].second == input[idx].second) {
                swap(input[j], input[idx]);
            } else {
                int diff = input[j].second - input[idx].second;
                input[j].second = input[idx].second;
                swap(input[j], input[idx]);
                input.insert(input.begin() + j + 1, {-1, diff });
            }
            break;
        }
    }
}

long long checksum = 0;
long long global_counter = 0;
for (long long i{}; i < input.size(); i++) {
    if (input[i].first == -1) {
        global_counter += input[i].second;
        continue;
    }
    for (long long j{}; j < input[i].second; j++) {
        checksum += (global_counter * input[i].first);
        global_counter++;
    }
//    checksum += (i * (long long) input[i].first * (long long) input[i].second);
}
cout << checksum << endl;

}