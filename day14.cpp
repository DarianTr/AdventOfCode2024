//
// Created by darian on 14.12.24.
//
#include  <bits/stdc++.h>
using namespace std;


struct Robot {
    int px = 0;
    int py = 0;
    int vx = 0;
    int vy = 0;
};

pair<int, int> move(const Robot &r, int time, int maxx, int maxy) {
    int x = (r.px + time * r.vx) % maxx;
    int y = (r.py + time * r.vy) % maxy;
    if (x < 0) x = maxx + x;
    if (y < 0) y = maxy + y;
    return {x, y};
}

void generatePBM(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    int height = matrix.size();
    int width = matrix[0].size();

    file << "P1\n";
    file << width << " " << height << "\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << (matrix[y][x] == 0 ? "0 " : "1 ");
        }
        file << "\n";
    }

    file.close();
    std::cout << "PBM image saved to " << filename << "\n";
}

void file_gen(vector<vector<int>> v, int maxx, int maxy, int time, vector<Robot> &r, string& name) {
    for (const auto &ro: r) {
        auto [x,y] = move(ro, time, maxx, maxy);
        v[y][x]++;
    }
    generatePBM(v, name);
}






int solve(vector<vector<int>> &v, int maxx, int maxy) {
    //part 1
    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    for (int i{}; i < maxx / 2; i++) {
        for (int j{}; j < maxy / 2; j++) sum1 += v[j][i];
    }
    for (int i = maxx / 2 + 1; i < maxx; i++) {
        for (int j{}; j < maxy / 2; j++) sum2 += v[j][i];
    }
    for (int i{}; i < maxx / 2; i++) {
        for (int j = maxy / 2 + 1; j < maxy; j++) sum3 += v[j][i];
    }
    for (int i = maxx / 2 + 1; i < maxx; i++) {
        for (int j = maxy / 2 + 1; j < maxy; j++) sum4 += v[j][i];
    }
    return sum1*sum2*sum3*sum4;
}

bool check (vector<vector<int>> v, int maxx, int maxy, int time, vector<Robot> &r) {
    for (const auto &ro: r) {
        auto [x,y] = move(ro, time, maxx, maxy);
        v[y][x]++;
    }
    for (int i{}; i < maxy - 10; i++) {
        for (int j{}; j < maxx; j++) {
           bool flag = true;
           for (int k{}; k < 10; k++) {
               if (v[i + k][j] == 0) { flag = false; break; }
           }
           if (flag) {
                cout << i << " " << j << endl;
                return true;
           }
        }
    }
    return false;
}

void view (vector<vector<int>> v, int maxx, int maxy, int time, vector<Robot> &r) {
    for (const auto &ro: r) {
        auto [x,y] = move(ro, time, maxx, maxy);
        v[y][x]++;
    }
    cout << "viewed" << endl;
}

int main() {
    vector<Robot> robots;
    int maxx = 101;
    int maxy = 103;
    int time = 100;
    vector<vector<int>> robots_per_field(maxy, vector<int>(maxx));
    vector<string> in;
    string line;
    while (getline(cin, line) && !line.empty()) {
        Robot r;
        stringstream ss(line);
        string part;
        ss >> part;
        part.erase(part.begin());
        part.erase(part.begin()); //removes p=
        string num;
        stringstream ss1(part);
        getline(ss1, num, ',');
        r.px = stoi(num);
        getline(ss1, num);
        r.py = stoi(num);
        ss >> part;
        part.erase(part.begin());
        part.erase(part.begin()); //removes v=
        stringstream ss2(part);
        getline(ss2, num, ',');
        r.vx = stoi(num);
        getline(ss2, num);
        r.vy = stoi(num);
        robots.push_back(r);
// part 1
//        auto [x, y] = move(r, time, maxx, maxy);
//        robots_per_field[y][x]++;
    }

    for (int i{}; i < 10000; i++) {
        string name = "file";
        string num = to_string(i);
        name += num + ".bpm";
        file_gen(robots_per_field, maxx, maxy, i, robots, name);
    }


//    cout << solve(robots_per_field, maxx, maxy) << endl;
}