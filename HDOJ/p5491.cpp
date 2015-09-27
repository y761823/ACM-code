#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 100010;

int d, s1, s2, T;
unsigned one = 1;

bool check(unsigned x) {
    int t = __builtin_popcount(x);
    return s1 <= t && t <= s2;
}

unsigned solve() {
    unsigned res = d;
    if(check(res + 1)) return res + 1;
    int cnt = __builtin_popcount(res);
    for(int i = 0; ; ++i) {
        if((res >> i) & 1) break;
        res = res | (one << i);
        cnt++;
        if(s1 <= cnt && cnt <= s2) return res;
    }
    res++;
    cnt = __builtin_popcount(res);
    if(s1 <= cnt && cnt <= s2) return res;
    for(int i = 0; ; ++i) {
        res = res | (one << i);
        cnt++;
        if(s1 <= cnt && cnt <= s2) return res;
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &d, &s1, &s2);
        printf("Case #%d: %u\n", t, solve());
    }
}
