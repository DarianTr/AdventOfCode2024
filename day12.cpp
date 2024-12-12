//
// Created by darian on 12.12.24.
//
#include <bits/stdc++.h>
using namespace std;


constexpr bool is_in_map(int n, int m, int i, int j) {
    return i < n && i >= 0 && j < m && j >= 0;
}

pair<int, int> dir[8] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

//long long get_group_edge_count(int i, int j, set<pair<int, int>> &n, vector<vector<bool>> &v, set<pair<int, int>> &c) {
//    bitset<4> a;
//    int co1 = 0;
//    if (c.count({i-1, j})) { a[0] = a[0] & 1; co1++; }
//    if (c.count({i, j-1})) { a[1] = a[1] & 1; co1++; }
//    if (c.count({i, j+1})) { a[2] = a[2] & 1; co1++; }
//    if (c.count({i+1, j})) { a[3] = a[3] & 1; co1++; }
//    if (co1 == 4) {
//        return 4;
//    }
//    int extra_count = 0;
//    if (n.count({i, j+1})) { //horizontal line
//        while (n.count({i, j})) {
//            v[i+1][j+1] = true;
//            int co = 0;
//            if (c.count({i-1, j})) { a[0] = a[0] & 1; co++; }
//            if (c.count({i, j-1})) { a[1] = a[1] & 1; co++; }
//            if (c.count({i, j+1})) { a[2] = a[2] & 1; co++; }
//            if (c.count({i+1, j})) { a[3] = a[3] & 1; co++; }
//            if (co == 3) {
//                extra_count ++;
//            }
//            j++;
//        }
//    } else if (n.count({i + 1, j})) {
//        while (n.count({i, j})) {
//            v[i+1][j+1] = true;
//            int co = 0;
//            if (c.count({i-1, j})) { a[0] = a[0] & 1; co++; }
//            if (c.count({i, j-1})) { a[1] = a[1] & 1; co++; }
//            if (c.count({i, j+1})) { a[2] = a[2] & 1; co++; }
//            if (c.count({i+1, j})) { a[3] = a[3] & 1; co++; }
//            if (co == 3) {
//                extra_count ++;
//            }
//            i++;
//        }
//    }
//    return a.count() + extra_count;
//}

pair<int, int> no_additional_start(vector<vector<char>> &in, set<pair<int, int>> &v) {
    for (int i{}; i < in.size(); i++) {
        for (int j{}; j < in.size(); j++) {
            if (in[i][j] == '!' && !v.count({i, j})) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

long long get_fence_cost(vector<vector<char>> in, set<pair<int, int>> &cluster, char type) {
    long long perimeter = 0;
    set<pair<int, int>> border;
    for (auto [x, y]: cluster) {
        for (auto [xx, yy]: dir) {
            if (!is_in_map(in.size(), in[0].size(), x + xx, y + yy) || in[x + xx][y + yy] != type) {
                border.insert({x, y});
            }
        }
    }
    for (auto &[x, y]: border) {
        in[x][y] = '!';
    }

    int count = 0;
    pair<int, int> start = *border.begin();
    pair<int, int> cur = *border.begin();
    set<pair<int, int>> v;
    while (cur.first != -1) {
        count++;
        int dirs = -1;
        do {
            if (dirs == -1) {
                for (int i{}; i < 4; i++) {
                    if (is_in_map(in.size(), in[0].size(), cur.first + dir[i].first, cur.second + dir[i].second) &&
                        (in[cur.first + dir[i].first][cur.second + dir[i].second] == '!') &&
                        !v.count({cur.first + dir[i].first, cur.second + dir[i].second})) {
                        dirs = i;
                        break;
                    }
                }
            } else {
                if (!is_in_map(in.size(), in[0].size(), cur.first + dir[dirs].first, cur.second + dir[dirs].second) ||
                    in[cur.first + dir[dirs].first][cur.second + dir[dirs].second] != '!') {
                    for (int i{}; i < 8; i++) {
                        if (is_in_map(in.size(), in[0].size(), cur.first + dir[i].first, cur.second + dir[i].second) &&
                            (in[cur.first + dir[i].first][cur.second + dir[i].second] == '!') &&
                            !v.count({cur.first + dir[i].first, cur.second + dir[i].second})) {
                            if (i < 4) {
                                dirs = i;
                                count++;
                            } else {
                                dirs = -1;
                                count++;
                            }
                            break;
                        }
                    }
                    if (in[cur.first + dir[dirs].first][cur.second + dir[dirs].second] != '!') {
                        break;
                    }
                }
            }
            cur = {cur.first + dir[dirs].first, cur.second + dir[dirs].second};
            v.insert(cur);
        } while (start != cur);
        cur = no_additional_start(in, v);
    }
    cout << count << endl;
    return count * cluster.size() / 9;
}

long long get_cluster(vector<vector<bool>> &vis, int i, int j, vector<vector<char>> &in) {
    char type = in[i][j];
    set<pair<int, int>> cluster;
    queue<pair<int, int>> active;
    active.emplace(i, j);
    cluster.insert({i, j});

    while (!active.empty()) {
        auto [ii, jj] = active.front();
        vis[ii][jj] = true;
        active.pop();
        for (auto &[x, y]: dir) {
            if (x == y) break;
            if (!cluster.count({ii+x, jj+y}) && is_in_map(in.size(), in[0].size(), ii+x, jj+y) && in[ii+x][jj+y] == type) {
                active.emplace(ii+x, jj+y);
                cluster.insert(active.back());
            }
        }
    }
    long long cost = get_fence_cost(in, cluster, type);
//    cout << type << ": " << cost << "\n";
    return cost;
}

int main() {
    vector<string> in1;
    string line;
    while (getline(cin, line) && !line.empty()) in1.push_back(line);
    cout << in1.size() << " " << in1[0].size() << endl;
    vector<vector<bool>> vis(in1.size() * 3, vector<bool>(in1[0].size() * 3));
    vector<vector<char>> in(in1.size()*3, vector<char>(in1[0].size() * 3));
    for (int i{}; i < in1.size(); i++) {
        for (int j{}; j < in1[0].size(); j++) {
            in[3*i][3*j] = in1[i][j];
            in[3*i][3*j+1] = in1[i][j];
            in[3*i][3*j+2] = in1[i][j];
            in[3*i+1][3*j] = in1[i][j];
            in[3*i+1][3*j+1] = in1[i][j];
            in[3*i+1][3*j+2] = in1[i][j];
            in[3*i+2][3*j] = in1[i][j];
            in[3*i+2][3*j+1] = in1[i][j];
            in[3*i+2][3*j+2] = in1[i][j];
        }
    }
    long long res = 0;
    for (int i{}; i < in.size(); i++) {
        for (int j{}; j < in[0].size(); j++) {
            if (!vis[i][j]) res += get_cluster(vis, i, j, in);
        }
//        cout << i << "/" << in.size() << endl;
    }
    cout << res << endl;
}