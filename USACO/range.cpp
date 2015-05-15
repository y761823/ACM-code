/*
ID: y7618231
PROG: range
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

const int MAXN = 256;

char mat[MAXN][MAXN];
int dp[MAXN][MAXN], cnt[MAXN];
int n;

void solve() {
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) if(mat[i][j] == '1') {
            dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            cnt[1]++, cnt[dp[i][j] + 1]--;
        }
    partial_sum(cnt + 1, cnt + n + 1, cnt + 1);
    int ed = n;
    while(ed > 1 && !cnt[ed]) --ed;
    for(int i = 2; i <= ed; ++i)
        printf("%d %d\n", i, cnt[i]);
}

int main() {
#ifndef OYK_JUDGE
    freopen("range.in", "r", stdin); freopen("range.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
    solve();
}
