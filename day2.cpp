//
// Created by darian on 02.12.24.
//
#include <bits/stdc++.h>
using namespace std;

bool brute_force_test(vector<int> &numbers) {
    bool out = false;
    for (int j{}; j < numbers.size(); j++) {
        int value = numbers[j];
        bool safe = true;
        int inc = 0;
        numbers.erase(numbers.begin() + j);
        for (int i = 1; i < numbers.size(); i++) {
            if (inc == 0 && numbers[i-1] < numbers[i]) inc = 1;
            if (inc == 0 && numbers[i-1] > numbers[i]) inc = -1;
            if (numbers[i-1] ==  numbers[i]) {
                safe = false;
            }
            if (abs(numbers[i-1] -  numbers[i]) > 3) {
                safe = false;
            }
            if (inc == 1 && numbers[i-1] >  numbers[i]) {
                safe = false;
            }
            if (inc == -1 && numbers[i-1] <  numbers[i]) {
                safe = false;
            }
        }
        numbers.insert(numbers.begin() + j, value);
        out |= safe;
    }
    return out;
}

int main() {
    int count = 0;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        stringstream ss_line(line);
        vector<int> number_line;
        int number;
        bool safe = true;
        int inc = 0;
        int counter_bad = 0;
        while (ss_line >> number) {
            number_line.push_back(number);
        }
        safe = brute_force_test(number_line);
        if (safe) count++;
        cout << count << endl;
    }
}