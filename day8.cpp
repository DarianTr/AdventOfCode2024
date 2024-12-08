//
// Created by darian on 08.12.24.
//
#include "bits/stdc++.h"
using namespace std;

bool is_in_map(int size_x, int size_y, int i, int j) {
    return i >= 0 && size_x > i && size_y > j && j >= 0;
}


int main() {
    vector<string> in;
    string line;
    while (getline(cin, line) && !line.empty()) {
        in.push_back(line);
    }
    map<char, set<pair<int, int>>> positions;
    for (int i{}; i < in.size(); i++) {
        for (int j{}; j < in[0].size(); j++) {
            if (in[i][j] != '.') {
                positions[in[i][j]].insert({i, j});
            }
        }
    }
    set<pair<int, int>> result;
    for (auto &[c, pos]: positions) {
        for (auto &e: pos) {
            result.insert(e);
            for (auto &d: pos) {
                if (e == d) continue;
                pair<int, int> e_copy = {e.first, e.second};
                pair<int, int> d_copy = {d.first, d.second};
                int x_dff = e.first - d.first;
                int y_diff = e.second - d.second;
                while (is_in_map(in.size(), in[0].size(), x_dff + e_copy.first, y_diff + e_copy.second)) { // while to if for part 1
                    result.insert({e_copy.first + x_dff, y_diff + e_copy.second});
                    in[e_copy.first + x_dff][y_diff + e_copy.second] = '#';
                    e_copy.first += x_dff;
                    e_copy.second += y_diff;
                };
                while (is_in_map(in.size(), in[0].size(), d_copy.first - x_dff, d_copy.second - y_diff)) { // while to if for part 1
                    result.insert({d_copy.first - x_dff, d_copy.second - y_diff});
                    in[d_copy.first - x_dff][d_copy.second - y_diff] = '#';
                    d_copy.first -= x_dff;
                    d_copy.second -= y_diff;
                };
            }
        }
    }
    cout << result.size() << endl;
}