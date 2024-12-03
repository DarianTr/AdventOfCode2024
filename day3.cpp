//
// Created by darian on 03.12.24.
//
#include "bits/stdc++.h"
using namespace std;

int main() {
// part 1
//    string in;
//    int value = 0;
//    regex const number{R"([0-9]+)"};
//    regex const mul{R"(mul\([0-9]{1,3},[0-9]{1,3}\))"};
//    while (getline(cin, in)) {
//        if (in.empty()) break;
//        smatch m;
//        while (regex_search(in, m, mul)) {
//            smatch m1;
//            string m_copy = m.str();
//            int add = 1;
//            while (regex_search(m_copy, m1, number)) {
//                add *= stoi(m1.str());
//                m_copy = m1.suffix();
//            }
//            in = m.suffix();
//            value += add;
//        }
//    }
//    cout << value << endl;
// part2
    string in;
    int value = 0;
    string number_s{R"(\d{1,3})"};
    string mul_s{R"(mul\(\d{1,3},\d{1,3}\))"};
    string dos_s{R"(do\(\))"};
    string donts_s{R"(don\'t\(\))"};

    string all_s = "((" + mul_s + ")|(" + dos_s + ")|(" + donts_s + "))";

    regex const number(number_s);
    regex const mul(mul_s);
    regex const dos(dos_s);
    regex const donts(donts_s);
    regex const all(all_s);

    int count = 0;
    bool flag = true;
    while (getline(cin, in)) {
        if (in.empty()) break;
        for (sregex_iterator it(in.begin(), in.end(), all), end_it; it != end_it; ++it) {
            string matched = it->str();
            if (matched == "don't()"){
                flag = false;
            } else if (matched == "do()") {
                flag = true;
                count++;
            } else if (flag && matched.find("mul(") == 0){
                smatch m1;
                string m_copy = matched;
                int add = 1;
                while (regex_search(m_copy, m1, number)) {
                    add *= stoi(m1.str());
                    m_copy = m1.suffix();
                }
                value += add;
            }
        }
    }
    cout << value << endl;
}