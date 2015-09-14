#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXV = 50010;
const int MAXC = 50000;
const int INF = 0x3f3f3f3f;

int dp[MAXV];
int n, m, p, T;

template<typename func>
void calc(int vol, int cost, int cnt, func f) {
    for(int i = 1; cnt ; i <<= 1) {
        i = min(i, cnt);
        f(vol * i, cost * i);
        cnt -= i;
    }
}

int solve() {
    memset(dp + 1, 0x3f, p * sizeof(int));
    for(int i = 0, t, u, v; i < n; ++i) {
        scanf("%d%d%d", &t, &u, &v);
        calc(t, u, v, [](int vol, int cost) {
            for(int i = p; i >= 0; --i) {
                int t = min(p, i + vol);
                dp[t] = min(dp[t], dp[i] + cost);
            }
        });
    }
    if(dp[p] == INF) return puts("TAT");
    int minsize = dp[p];
    memset(dp + 1, 0, MAXC * sizeof(int));
    for(int i = 0, x, y, z; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        calc(y, x, z, [](int vol, int cost) {
            for(int i = MAXC; i >= vol; --i)
                dp[i] = max(dp[i], dp[i - vol] + cost);
        });
    }
    int res = 0;
    while(res <= MAXC && dp[res] < minsize) ++res;
    return res <= MAXC ? printf("%d\n", res) : puts("TAT");
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &p);
        solve();
    }
}
