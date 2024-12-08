//
// Created by darian on 07.12.24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

ll get_log_10(ll num) {
    ll count = 0;
    while (num >= 10) {
        count++;
        num /= 10;
    }
    return count;
}

ll powll_10(ll exp) {
    ll val = 1;
    if (exp == 0) return 1;
    if (exp & 1) {
        val *= 10;
        return val * powll_10(exp-1);
    } else {
        ll res = powll_10(exp / 2);
        val *= (res * res);
        return val;
    }
}

ll pow_10_bf(ll exp) {
    if (exp == 0) return 1;
    return 10 * pow_10_bf(exp-1);
}

bool check_sum(vector<ll> &nums, ll target, ll current, int pos) {
    if (current == target && pos == nums.size()) return true;
    if (current > target || pos >= nums.size()) return false;
    bool add = check_sum(nums, target, current + nums[pos], pos+1);
    bool mul = check_sum(nums, target, current * nums[pos], pos+1);
    ll log_v = get_log_10(nums[pos]) + 1;
    ll concat_value = current * powll_10(log_v) + nums[pos];
    bool concat = check_sum(nums, target, concat_value, pos+1);
    return add || mul | concat;
}

int main() {
    string line;
    ll val = 0;
    while (getline(cin, line) && !line.empty()) {
        stringstream ss(line);
        string target;
        ss >> target;
        target.pop_back();
        ll t = stoll(target);
        vector<ll> num;
        string n;
        while (!ss.eof()) {
            ss >> n;
            num.push_back(stoll(n));
        }
        bool res = check_sum(num, t, num[0], 1);
        if (res) val += t;
    }
    cout << val  << endl;
}