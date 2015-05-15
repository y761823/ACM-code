/*
ID: y7618231
PROG: rockers
LANG: C++11
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
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 22;

int dp[MAXN][MAXN];
int a[MAXN];
int n, T, m;

void update_max(int &a, int b) {
    if(a < b) a = b;
}

int solve() {
    for(int i = 0; i < n; ++i) {
        int cost = a[i];
        for(int p = m; p > 0; --p) {
            for(int j = T; j >= cost; --j) {
                update_max(dp[p][j], dp[p][j - cost] + 1);
                update_max(dp[p][j], dp[p - 1][T] + 1);
            }
        }
    }
    return dp[m][T];
}

int main() {
#ifndef OYK_JUDGE
    freopen("rockers.in", "r", stdin); freopen("rockers.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d", &n, &T, &m);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    printf("%d\n", solve());
}
