/*
ID: y7618231
PROG: game1
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
#include <numeric>
#include <queue>
#include <tuple>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 110;

int dp[MAXN][MAXN];
int a[MAXN], sum[MAXN], n;

void solve() {
    FOR(step, 1, n - 1) {
        FOR(i, 1, n - step) {
            int j = i + step;
            dp[i][j] = sum[j] - sum[i - 1] - min(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    printf("%d %d\n", dp[1][n], sum[n] - dp[1][n]);
}

int main() {
#ifndef OYK_JUDGE
    freopen("game1.in", "r", stdin); freopen("game1.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    FOR(i, 1, n) {
        scanf("%d", &a[i]);
        dp[i][i] = a[i];
    }
    partial_sum(a + 1, a + n + 1, sum + 1);
    solve();
}
