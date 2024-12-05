//
// Created by darian on 05.12.24.
//

#include "bits/stdc++.h"

using namespace std;


void dfs(map<string, set<string>> &g, set<string> &v, const string& s, set<string> &num) {
    v.insert(s);
    for (const auto& e: g[s]) {
        if (!v.count(e) && num.count(e)) dfs(g, v, e, num);
    }
}


bool check_order(map<string, set<string>> &g, vector<string> &numbers, set<string> &num) {
    while (!numbers.empty()) {
        string start = numbers.back();
        numbers.pop_back();
        set<string> v;
        dfs(g, v, start, num);
        for (auto &e: numbers) {
            if (v.count(e)) return false;
        }
    }
    return true;
}



int main() {
    int value = 0;
    map<string, set<string>> graph;
    map<string, int> in;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        graph[std::string() + line[0] + line[1]].insert(std::string() + line[3] + line[4]);
        in[std::string() + line[3] + line[4]]++;
    }

    while (getline(cin, line) && !line.empty()) {
        if (line.empty()) break;
        vector<string> numbers;
        vector<string> copy;
        set<string> num_s;
        stringstream ss(line);
        string num;
        while (!ss.eof()) {
            getline(ss, num, ',');
            num_s.insert(num);
            numbers.push_back(num);
            copy.push_back(num);
        }
        int middle = stoi(numbers[numbers.size() / 2]);
        if (check_order(graph, numbers, num_s)) {
// part 1
//            value += middle;
//            cout << value << endl;
        } else {
// part 2
            auto cmp = [&graph](const string &a, string &b) {
                    return graph[a].count(b);
            };
            std::sort(copy.begin(), copy.end(), cmp);
            value += stoi(copy[copy.size() / 2]);
        }
    }
    cout << value << endl;
    return 0;
}