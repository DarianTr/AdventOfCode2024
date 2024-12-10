//
// Created by darian on 12/10/2024.
//
#include "bits/stdc++.h"
using namespace std;

bool is_in_map(int n, int m, int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

pair<int, int> dir[4] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};

int get_score(vector<string> &in, int i, int j) {
    queue<pair<int, int>> active;
    active.emplace(i, j);
    int count = 0;
    set<pair<int, int>> nines;
    while (!active.empty()) {
        int ii, jj;
        tie(ii, jj) = active.front();
        active.pop();
//        if (!nines.count({ii, jj}) && in[ii][jj] == '9') {
        if (in[ii][jj] == '9') {
            count++;
//            nines.insert({ii, jj});
        }
        for (auto &[x, y]: dir) {
            if (is_in_map(in.size(), in[0].size(), ii+x, jj+y) && in[ii][jj] + 1 == in[ii+x][jj+y]) {
                active.emplace(ii+x, jj+y);
            }
        }
    }
    return count;
}

int main() {
    vector<string> in;
    string line;
    while (getline(cin, line) && !line.empty()) {
        in.push_back(line);
    }

    int sum = 0;
    for (int i{}; i < in.size(); i++) {
        for (int j{}; j < in[0].size(); j++) {
            if (in[i][j] == '0') {
                sum += get_score(in, i, j);
            }
        }
    }
    cout << sum << endl;
}