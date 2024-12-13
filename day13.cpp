//
// Created by darian on 12/13/2024.
//
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct ButtonPrize {
    ll ax = 0;
    ll ay = 0;
    ll bx = 0;
    ll by = 0;
    ll target_x = 0;
    ll target_y = 0;
};

pair<ll, ll> get_button_fields(string &button) {
    ll y = button.back() - '0' + (button[button.size() - 2] - '0') * 10;
    ll x = (button[button.size() - 7] - '0') + (button[button.size() - 8] - '0') * 10;
    return {x, y};
}

pair<ll, ll> get_target(string &last_line) {
    ll x, y;
    stringstream ss(last_line);
    string val;
    ss >> val; //prize:
    ss >> val;
    val.pop_back(); //remove ,
    val.erase(val.begin()); // remove X
    val.erase(val.begin()); // remove =
    x = stoll(val);
    ss >> val;
    val.erase(val.begin()); // remove Y
    val.erase(val.begin()); // remove =
    y = stoll(val);
    return {x + 10000000000000, y + 10000000000000};
}

ButtonPrize parse_input(vector<string> &in_line) {
    ButtonPrize bp;
    tie(bp.ax, bp.ay) = get_button_fields(in_line[0]);
    tie(bp.bx, bp.by) = get_button_fields(in_line[1]);
    tie (bp.target_x, bp.target_y) = get_target(in_line[2]);
    return bp;
}

bool check_for_linear_dependence(ButtonPrize &bp) {
    return bp.ax * bp.by == bp.ay * bp.bx; //XA/XB = YA/YB
}

ll solve_one_input(ButtonPrize &bp) {
    // part 1
//    if ((bp.target_x > 100 * bp.ax + 100 * bp.bx)) return 0;
//    if ((bp.target_y > 100 * bp.ay + 100 * bp.by)) return 0;
//    vector<vector<int>> dp(bp.target_x + 1, vector<int>(bp.target_y + 1, INT32_MAX / 2));
//    dp[0][0] = 0;
//    for (int x{}; x <= bp.target_x; x++) {
//        for (int y{}; y <= bp.target_y; y++) {
//            if (x - bp.ax >= 0 && y - bp.ay >= 0) dp[x][y] = min(dp[x][y], 3 + dp[x - bp.ax][y - bp.ay]);
//            if (x - bp.bx >= 0 && y - bp.by >= 0) dp[x][y] = min(dp[x][y], 1 + dp[x - bp.bx][y - bp.by]);
//        }
//    }
//    int res = dp[bp.target_x][bp.target_y];
//    if (res == INT32_MAX / 2) res = 0;
//    return res;

    bool is_scaled = check_for_linear_dependence(bp);
    if (!is_scaled) {
        ll b_num = bp.target_y * bp.ax - bp.ay * bp.target_x;
        ll b_denom = bp.by * bp.ax - bp.ay * bp.bx;

        bool is_interger = (b_num / b_denom) * b_denom == b_num;
        if (!is_interger) return 0; //no integer solution
        return (b_num / b_denom) + 3 * ((bp.target_x - bp.bx * (b_num / b_denom)) / bp.ax);
    } else {
        cerr << "cannot handle" << endl;
        return 0;
    }
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
    ll res = 0;
    for (auto &v: in) {
        ButtonPrize bp = parse_input(v);
        ll ans = solve_one_input(bp);
        res += ans;
        cout << (uint64_t) res << endl;
    }
    cout << (uint64_t) res << endl;
}
