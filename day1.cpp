//
// Created by darian on 01.12.24.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> first;
    vector<int> second;

    int a, b;
    while (cin >> a) {
        cin >> b;
        first.push_back(a);
        second.push_back(b);
    }


// part two
    map<int, int> count_second;

    for (int i{}; i < first.size(); i++) {
        count_second[second[i]]++;
    }

    int val = 0;
    for (int i{}; i < first.size(); i++) {
        val += first[i] * count_second[first[i]];
    }
    cout << val << endl;


// part one
//    std::sort(first.begin(), first.end());
//    std::sort(second.begin(), second.end());
//
//    int diff = 0;
//    for (int i{}; i < first.size(); i++) {
//        diff += abs(second[i] - first[i]);
//    }
//    cout << diff << endl;
    return 0;
}