//
// Created by darian on 12/13/2024.
//
#include <bits/stdc++.h>
using namespace std;

struct ButtonPrize {
    int ax = 0;
    int ay = 0;
    int bx = 0;
    int by = 0;
    int target_x = 0;
    int target_y = 0;
};

pair<int, int> get_button_fields(string &button) {
    int y = button.back() - '0' + (button[button.size() - 2] - '0') * 10;
    int x = (button[button.size() - 7] - '0') + (button[button.size() - 8] - '0') * 10;
    return {x, y};
}

pair<int, int> get_target(string &last_line) {
    int x, y;
    stringstream ss(last_line);
    string val;
    ss >> val; //prize:
    ss >> val;
    val.pop_back(); //remove ,
    val.erase(val.begin()); // remove X
    val.erase(val.begin()); // remove =
    x = stoi(val);
    ss >> val;
    val.erase(val.begin()); // remove Y
    val.erase(val.begin()); // remove =
    y = stoi(val);
    return {x, y};
}

ButtonPrize parse_input(vector<string> &in_line) {
    ButtonPrize bp;
    tie(bp.ax, bp.ay) = get_button_fields(in_line[0]);
    tie(bp.bx, bp.by) = get_button_fields(in_line[1]);
    tie (bp.target_x, bp.target_y) = get_target(in_line[2]);
    //maybe change inputs to divide by lcm
    return bp;
}


int solve_one_input(ButtonPrize &bp) {
    if ((bp.target_x > 100 * bp.ax + 100 * bp.bx)) return 0;
    if ((bp.target_y > 100 * bp.ay + 100 * bp.by)) return 0;

    vector<vector<int>> dp(bp.target_x + 1, vector<int>(bp.target_y + 1, INT32_MAX / 2));
    dp[0][0] = 0;
    for (int x{}; x <= bp.target_x; x++) {
        for (int y{}; y <= bp.target_y; y++) {
            if (x - bp.ax >= 0 && y - bp.ay >= 0) dp[x][y] = min(dp[x][y], 3 + dp[x - bp.ax][y - bp.ay]);
            if (x - bp.bx >= 0 && y - bp.by >= 0) dp[x][y] = min(dp[x][y], 1 + dp[x - bp.bx][y - bp.by]);
        }
    }
    int res = dp[bp.target_x][bp.target_y];
    if (res == INT32_MAX / 2) res = 0;
    return res;
}

int main() {
    vector<vector<string>> in;
    string line;
    int count = 0;
    in.emplace_back();
    while (getline(cin, line) && !line.empty()) {
        do  {
            in[count].push_back(line);
        } while (getline(cin, line) && !line.empty());
        count++;
        in.push_back({});
    }
    in.pop_back();
    int res = 0;
    for (auto &v: in) {
        ButtonPrize bp = parse_input(v);
        int ans = solve_one_input(bp);
        res += ans;
        cout << res << endl;
    }
    cout << res << endl;
}
