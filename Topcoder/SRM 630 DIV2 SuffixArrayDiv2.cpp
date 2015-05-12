#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
typedef long long LL;

vector<int> build_sa(string s) {
    int n = s.size();
    s.push_back(0);
    vector<int> vec;
    for(int i = 0; i < n; ++i) vec.push_back(i);
    sort(vec.begin(), vec.end(), [&](int a, int b) {
        return s.substr(a) < s.substr(b);
    });
    return vec;
}

class SuffixArrayDiv2 {
public:
    string smallerOne(string s) {
        vector<int> sa = build_sa(s);
        for(size_t i = 0; i < s.size(); ++i) {
            if(s[i] != 'a') {
                s[i]--;
                if(sa == build_sa(s)) return "Exists";
                s[i]++;
            }
        }
        return "Does not exist";
    }
};
