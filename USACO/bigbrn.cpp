/*
ID: y7618231
PROG: bigbrn
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <functional>
#include <set>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPr(i, n) for(int i = n - 1; i >= 0; --i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define FORr(i, s, t) for(int i = t; i >= s; --i)

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

bool mat[MAXN][MAXN];
int dp[MAXN][MAXN];
int n, m;

int solve() {
    FOR(i, 1, n) FOR(j, 1, n) if(!mat[i][j])
        dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
    int res = 0;
    FOR(i, 1, n) FOR(j, 1, n)
        res = max(res, dp[i][j]);
    return res;
}

int main() {
#ifndef OYK_JUDGE
    freopen("bigbrn.in", "r", stdin); freopen("bigbrn.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    for(int i = 0, r, c; i < m; ++i) {
        scanf("%d%d", &r, &c);
        mat[r][c] = true;
    }
    printf("%d\n", solve());
}
