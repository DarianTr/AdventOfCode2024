
//
// Created by darian on 12/11/2024.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve2(map<ll, map<ll, ll>> &m, ll n, int max_depths) {
    ll c = 1;
    map<ll, ll> v1;
    map<ll, ll> v2;
    v1[n] = 1;
    for (int d{}; d <= max_depths; d++) {
        m[n][max_depths - d] = c;
        for (auto &[num, count]: v1) {
//            if (m[num].count(d)) {
//                c += m[num][d] - 1; //maybe -1 because the start number is already in c  // memoization wasnt needed
//            } else if (num == 0) {
            if (num == 0) {
                v2[1]+=count;
            } else if (((ll) log10(num) & 1)) {
                ll l = log10(num);
                v2[(num / (ll) pow(10, (l+1)/2))]+=count;
                v2[(num % (ll) pow(10, (l+1)/2))]+=count;
                c += count;
            } else {
                v2[num * 2024]+=count;
            }
        }
        v1 = v2;
        v2 = {};
    }
    return m[n][0] ;
}


int main() {
    vector<ll> in;
    int a;
    while (cin >> a) in.push_back(a);
//part 1
//    vector<ll> next;
//    for (int t{}; t < 25; t++) {
//        for (int i{}; i < in.size(); i++) {
//            if (in[i] == 0) next.push_back(1);
//            else if (((ll) log10(in[i]) & 1)) {
//                int l = log10(in[i]);
//                next.push_back(in[i] / (ll) pow(10, (l+1)/2));
//                next.push_back(in[i] % (ll) pow(10, (l+1)/2));
//            } else {
//                next.push_back(in[i]*2024);
//            }
//        }
//        in = next;
//        next = {};
//    }
//    cout << in.size() << endl;

ll count = 0;
map<ll, map<ll, ll>> m;
vector<int> par;
int max_depth = 75;
for (auto e: in) {
    count += solve2(m, e, max_depth);
}
cout << count << endl;
}