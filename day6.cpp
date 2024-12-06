//
// Created by darian on 12/6/2024.
//
#include "bits/stdc++.h"
using namespace std;


pair<int, int> dir[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

pair<int, int> get_start_position(vector<string> &in) {
    for (int i{}; i < in.size(); i++) {
        for (int j{}; j < in[i].size(); j++) {
            if (in[i][j] == '^') return {i, j};
        }
    }
    return {-1, -1};
}

bool is_in_map(int n, int m, pair<int, int> &pos) {
    return pos.first < n && pos.first >= 0 && pos.second < m && pos.second >= 0;
}

void move(vector<string> &input, pair<int, int> &start) {
    int direction_counter = 0;
    pair<int, int> current_position = start;
    int n = input.size();
    int m = input[0].size();
    while (is_in_map(n, m, current_position)) {
        input[current_position.first][current_position.second] = 'X';
        auto next = make_pair(current_position.first + dir[direction_counter].first, current_position.second + dir[direction_counter].second);
        if (is_in_map(n, m, next) &&  input[next.first][next.second] == '#') {
            direction_counter = (direction_counter + 1) % 4;
        } else {
            current_position = next;
        }
    }
}

bool cycle_checker(vector<string> &input, pair<int, int> &start, set<tuple<int, int, int>> &v) {
    int direction_counter = 0;
    pair<int, int> current_position = start;
    int n = input.size();
    int m = input[0].size();
    while (is_in_map(n, m, current_position)) {
//        input[current_position.first][current_position.second] = 'X';
        v.insert({current_position.first, current_position.second, direction_counter});
        auto next = make_pair(current_position.first + dir[direction_counter].first, current_position.second + dir[direction_counter].second);
        if (is_in_map(n, m, next) &&  input[next.first][next.second] == '#') {
            direction_counter = (direction_counter + 1) % 4;
        } else {
            if (v.count({next.first, next.second, direction_counter})) return true;
            current_position = next;
        }
    }
    return false;
}


int count_x(vector<string> &in) {
    int count = 0;
    for (auto &s: in) {
        for (auto &c: s) {
            if (c == 'X') count++;
        }
    }
    return count;
}

int main() {
    vector<string> input;
    string line;
    while (getline(cin, line) && !line.empty()) {
        input.push_back(line);
    }
    auto start = get_start_position(input);
//    move(input, start);
    int count = 0;
    for (int i{}; i < input.size(); i++) {
        for (int j{}; j < input[0].size(); j++) {
            if ((i == start.first && j == start.second) || input[i][j] == '#') continue;
            input[i][j] = '#';
            set<tuple<int, int, int>> v;
            if (cycle_checker(input, start, v)) count++;
            input[i][j] = '.';
        }
        cout<< i << "/" << input.size() << endl;
    }
//    cout << count_x(input) << endl;
    cout << count << endl;
}