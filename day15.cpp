//
// Created by darian on 15.12.24.
//
#include "bits/stdc++.h"
using namespace std;

pair<int, int> dir[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

pair<int, int> get_start_position(vector<string> &m) {
    for (int i{}; i < m.size(); i++) {
        for (int j{}; j < m[0].size(); j++) {
            if (m[i][j] == '@') return {i, j};
        }
    }
    return {-1, -1};
}

bool move_touching(vector<string> &m, pair<int, int> pos1, pair<int, int> pos2, int d) {
    if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == '.' && m[pos2.first + dir[d].first][pos2.second + dir[d].second] == '.') {
        m[pos1.first + dir[d].first][pos1.second + dir[d].second] = m[pos1.first][pos1.second];
        m[pos2.first + dir[d].first][pos2.second + dir[d].second] = m[pos2.first][pos2.second];
        m[pos1.first][pos1.second] = '.';
        m[pos2.first][pos2.second] = '.';
    } else if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == '#' || m[pos2.first + dir[d].first][pos2.second + dir[d].second] == '#') {
        return false;
    } else {
        if (d > 1 ) {
            pair<int, int> p1 = {pos1.first + dir[d].first, pos1.second + dir[d].second - 1};
            pair<int, int> p2 = {pos1.first + dir[d].first, pos1.second + dir[d].second};
            pair<int, int> p3 = {pos1.first + dir[d].first, pos1.second + dir[d].second + 1};

            bool res = true;

            if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == ']') res &= move_touching(m, p1, p2, d);
            if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == '[') res &= move_touching(m, p2, p3, d);

            pair<int, int> p11 = {pos2.first + dir[d].first, pos2.second + dir[d].second - 1};
            pair<int, int> p22 = {pos2.first + dir[d].first, pos2.second + dir[d].second};
            pair<int, int> p33 = {pos2.first + dir[d].first, pos2.second + dir[d].second + 1};

            if (m[pos2.first + dir[d].first][pos2.second + dir[d].second] == ']') res &= move_touching(m, p11, p22, d);
            if (m[pos2.first + dir[d].first][pos2.second + dir[d].second] == '[') res &= move_touching(m, p22, p33, d);


            if (res) move_touching(m, pos1, pos2, d);
            else return false;
        } else {
            auto pos3 = pos2;
            pos3.first += dir[d].first;
            pos3.second += dir[d].second;
            if (pos1 != pos3) swap(pos1, pos2);
            if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == '.') {
                m[pos1.first + dir[d].first][pos1.second + dir[d].second] = m[pos1.first][pos1.second];
                m[pos2.first + dir[d].first][pos2.second + dir[d].second] = m[pos2.first][pos2.second];
                m[pos2.first][pos2.second] = '.';
            }
            else if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == ']' || m[pos1.first + dir[d].first][pos1.second + dir[d].second] == '[' ) {
                if (move_touching(m, {pos1.first + 2*dir[d].first, pos1.second + 2*dir[d].second}, {pos1.first + dir[d].first, pos1.second + dir[d].second}, d)) {
                    move_touching(m, pos1, pos2, d);
                } else {
                    return false;
                }
            }
            else if (m[pos1.first + dir[d].first][pos1.second + dir[d].second] == '#') return false;
        }
    }
    return true;
}

bool move22(vector<string> &m, pair<int, int> &pos, int d) {
    switch (m[pos.first + dir[d].first][pos.second + dir[d].second]) {
        case '#':
            return false;
        case '.':
            m[pos.first][pos.second] = '.';
            pos.first += dir[d].first;
            pos.second += dir[d].second;
            m[pos.first][pos.second] = '@';
            break;
        case ']':
            if (move_touching(m, {pos.first + dir[d].first, pos.second + dir[d].second}, {pos.first + dir[d].first, pos.second + dir[d].second - 1}, d)) {
                move22(m, pos, d);
                return true;
            } else {
                return false;
            }
        case '[':
            if (move_touching(m, {pos.first + dir[d].first, pos.second + dir[d].second}, {pos.first + dir[d].first, pos.second + dir[d].second + 1}, d)) {
                move22(m, pos, d);
                return true;
            } else {
                return false;
            }
    }
    return true;
}

//part 1
void move2(vector<string> &m, pair<int, int> &pos, int direction) {
    if (m[pos.first + dir[direction].first][pos.second + dir[direction].second] == '.') {
        m[pos.first][pos.second] = '.';
        pos.first += dir[direction].first;
        pos.second += dir[direction].second;
        m[pos.first][pos.second] = '@';
    } else if (m[pos.first + dir[direction].first][pos.second + dir[direction].second] == '#') {
        return;
    } else {
        pair<int, int> pos2 = {pos.first, pos.second};
        if (m[pos2.first + dir[direction].first][pos2.second + dir[direction].second] == 'O') {
            pos2.first += dir[direction].first;
            pos2.second += dir[direction].second;
        }
        if (m[pos2.first + dir[direction].first][pos2.second + dir[direction].second] == '.') {
            m[pos2.first + dir[direction].first][pos2.second + dir[direction].second] = 'O';
            m[pos.first][pos.second] = '.';
            pos.first += dir[direction].first;
            pos.second += dir[direction].second;
            m[pos.first][pos.second] = '@';
        } else {
            return;
        }

    }
}

vector<string> get_new_map(vector<string> &m) {
    vector<string> new_m(m.size());
    for (int i{}; i < m.size(); i++) {
        for (int j{}; j < m.size(); j++) {
            if (m[i][j] == '.') new_m[i] += "..";
            if (m[i][j] == 'O') new_m[i] += "[]";
            if (m[i][j] == '#') new_m[i] += "##";
            if (m[i][j] == '@') new_m[i] += "@.";
        }
    }
    return new_m;
}

int get_sum(vector<string> &m) {
    int sum = 0;
    for (int i{}; i < m.size(); i++) {
        for (int j{}; j < m[0].size(); j++) {
            if (m[i][j] == '[') sum += (100 * i + j);
        }
    }
    return sum;
}

int main() {
    vector<string> map;
    string line;
    while (getline(cin, line) && !line.empty()) {
        map.push_back(line);
    }
    map = get_new_map(map);
    auto pos = get_start_position(map);
    while (getline(cin, line) && !line.empty()) {
        for (auto move: line) {
            vector<string> mcopy(map.begin(), map.end());
            switch (move) {
                case '<':
                    if (!move22(map, pos, 0)) {
                        map = mcopy;
                    }
                    break;
                case '>':
                    if (!move22(map, pos, 1)) {
                        map = mcopy;
                    }
                    break;
                case '^':
                    if (!move22(map, pos, 2)) {
                        map = mcopy;
                    }
                    break;
                case 'v':
                    if (!move22(map, pos, 3)) {
                        map = mcopy;
                    }
                    break;
            }
        }
    }
    cout  << get_sum(map) << endl;
}