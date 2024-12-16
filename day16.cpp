//
// Created by darian on 16.12.24.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;


pair<int, int> dir[4] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

struct INT {
    int value = INT32_MAX;
};

struct MapIndex {
    int x = 0;
    int y = 0;
    int dir = 0;
    bool operator<(const MapIndex &m) const {
        if (x != m.x) return x < m.x;
        else if (m.y != y) return y < m.y;
        else return dir < m.dir;
    }
};

struct QElement {
    int score = 0;
    MapIndex mi;
    bool operator<(const QElement &a) const {
        return score > a.score;
    }
};



int dijkstra(vector<string> &m, pair<int, int> start, char target, int start_dir) {
    map<MapIndex, INT> map;
    priority_queue<QElement> pq;
    int lowestEnd = INT32_MAX;
    pq.push({0, start.first, start.second, 0});
    while (!pq.empty()) {
        auto a = pq.top();
        pq.pop();
        if (map.count(a.mi) && map.at(a.mi).value <= a.score) continue;
        if (!map.count(a.mi)) map[a.mi] = {a.score};
        if (m[a.mi.x][a.mi.y] == target) {
            lowestEnd = min(lowestEnd, a.score);
        }
        if (m[a.mi.x + dir[a.mi.dir].first][a.mi.y+ dir[a.mi.dir].second] != '#') pq.push({a.score + 1, a.mi.x + dir[a.mi.dir].first, a.mi.y+ dir[a.mi.dir].second, a.mi.dir});
        for (int d = 1; d < 4; d++) {
            int dirs = (a.mi.dir + d) % 4;
            pq.push({a.score + 1000, a.mi.x, a.mi.y, dirs});
        }
    }
    return lowestEnd;
}

int part2(vector<string> &m, pair<int, int> start) {
    map<pair<int, int>, INT> mapE;
    map<pair<int, int>, INT> mapS;
    for (int x1{}; x1 < m.size(); x1++) {
        for (int y1{}; y1 < m[0].size(); y1++) {
            if (m[x1][y1] == '#') continue;
            int mres = INT32_MAX/3, mres2 =INT32_MAX/3;
            for (int i{}; i < 4; i++) {
                int res = dijkstra(m, {x1, y1}, 'S', i);
                int res2 = dijkstra(m, {x1, y1}, 'E', (i + 2)%4);
                if (res + res2 <= mres + mres2) {
                    mres = res;
                    mres2 = res2;
                }
            }
            if (mres == INT32_MAX/3 || mres2 == INT32_MAX/3) continue;
            mapS[{x1, y1}] = {mres};
            mapE[{x1, y1}] = {mres2};
        }
    }
    int count = 0;
    for (int x1{}; x1 < m.size(); x1++) {
        for (int y1{}; y1 < m[0].size(); y1++) {
            if (mapS[{x1, y1}].value + mapE[{x1, y1}].value == mapE[start].value) {
                count++;
                m[x1][y1] = 'O';
            }
        }
    }
    return count;
}

pair<int, int> get_start(vector<string> &m) {
    for (int i{}; i < m.size(); i++) {
        for (int j{}; j < m[0].size(); j++) {
            if (m[i][j] == 'S') return {i, j};
        }
    }
    return {-1, -1};
}

int main() {
    vector<string> maze;
    string line;
    while (getline(cin, line) && !line.empty()) maze.push_back(line);
//    cout << dijkstra(maze, get_start(maze), 'E') << endl; part 1
    cout << part2(maze, get_start(maze)) << endl;
}