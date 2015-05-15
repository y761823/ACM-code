/*
ID: y7618231
LANG: C++
TASK: spin
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 365;
const int INF = 0x3f3f3f3f;

vector<pair<int, int> > wheel[5];
int spd[5];
int cnt[MAXN];
int n = 5;

void set(int l, int r) {
    if(l > r) {
        for(int i = l; i < 360; ++i) cnt[i]++;
        for(int i = 0; i <= r; ++i) cnt[i]++;
    } else {
        for(int i = l; i <= r; ++i) cnt[i]++;
    }
}

void add(int &a, int &b, int c) {
    (a += c) %= 360;
    (b += c) %= 360;
}

int solve() {
    for(int t = 0; t < 360; ++t) {
        memset(cnt, 0, sizeof(cnt));
        vector<pair<int, int> >::iterator it;
        for(int i = 0; i < n; ++i)
            for(it = wheel[i].begin(); it != wheel[i].end(); ++it)
                set(it->first, it->second);
        for(int i = 0; i < 360; ++i) if(cnt[i] == 5) return t;

        for(int i = 0; i < n; ++i)
            for(it = wheel[i].begin(); it != wheel[i].end(); ++it)
                add(it->first, it->second, spd[i]);
    }
    return -1;
}

int main() {
#ifndef OYK_JUDGE
    freopen("spin.in", "r", stdin); freopen("spin.out", "w", stdout);
#endif // OYK_JUDGE
    for(int i = 0, a, b, c; i < n; ++i) {
        scanf("%d%d", &spd[i], &c);
        while(c--) scanf("%d%d", &a, &b), wheel[i].push_back(make_pair(a, (a + b) % 360));
    }
    int res = solve();
    if(res != -1) printf("%d\n", res);
    else puts("none");
}
