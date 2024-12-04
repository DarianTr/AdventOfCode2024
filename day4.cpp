#include <bits/stdc++.h>
using namespace std;

string get_horizontal(vector<string> &m, int i, int j) {
    string res;
    if (j < m[i].size() - 3) {
        res +=  m[i][j];
        res += m[i][j+1];
        res += m[i][j+2];
        res += m[i][j+3];
    }
    return res;
}

string get_vertical(vector<string> &m, int i, int j) {
    string res;
    if (i < m.size() - 3) {
        res += m[i][j];
        res += m[i+1][j];
        res += m[i+2][j];
        res += m[i+3][j];
    }
    return res;
}

string get_dia_1(vector<string> &m, int i, int j) {
    string res;
    if (j < m[i].size() - 3 && i < m.size() - 3) {
        res += m[i][j];
        res += m[i+1][j+1];
        res += m[i+2][j+2];
        res += m[i+3][j+3];
    }
    return res;
}

string get_dia_2(vector<string> &m, int i, int j) {
    string res;
    if (j < m[i].size() - 3 && i > 2) {
        res += m[i][j];
        res += m[i-1][j+1];
        res += m[i-2][j+2];
        res += m[i-3][j+3];
    }
    return res;
}


string get_dia_1_2(vector<string> &m, int i, int j) {
    string res;
    if (j < m[i].size() - 2 && i < m.size() - 2) {
        res += m[i][j];
        res += m[i+1][j+1];
        res += m[i+2][j+2];
    }
    return res;
}

string get_dia_2_2(vector<string> &m, int i, int j) {
    string res;
    if (j < m[i].size() - 2 && i > 1) {
        res += m[i][j];
        res += m[i-1][j+1];
        res += m[i-2][j+2];
    }
    return res;
}

bool check_cross(vector<string> &m, int i, int j) {
    if (i+2 >= m.size()) return false;
    if (get_dia_2_2(m, i+2, j) == "MAS" || get_dia_2_2(m, i+2, j) == "SAM") {
        if (get_dia_1_2(m, i, j) == "MAS" || get_dia_1_2(m, i, j) == "SAM") {
            return true;
        }
    }
    return false;
}

int main() {
    vector<string> matrix;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        matrix.push_back(line);
    }
    int count = 0;
    for (int i{};i < matrix.size(); i++) {
        for (int j {}; j < matrix[i].size(); j++) {
//            string test = get_vertical(matrix, i, j);
//            if (test == "XMAS" || test == "SAMX") count++;
//            test = get_horizontal(matrix, i, j);
//            if (test == "XMAS" || test == "SAMX") count++;
//            test = get_dia_1(matrix, i, j);
//            if (test == "XMAS" || test == "SAMX") count++;
//            test = get_dia_2(matrix, i, j);
//            if (test == "XMAS" || test == "SAMX") count++;
            if (check_cross(matrix, i, j)) count++;
        }
    }
    cout << count << endl;
}