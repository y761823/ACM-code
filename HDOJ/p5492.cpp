#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 33;
const int INF = 0x3f3f3f3f;

int dp[MAXN][MAXN][2000];
int mat[MAXN][MAXN];
int n, m, T;

void update_min(int &a, int b) {
    if(a > b) a = b;
}

int sqr(int x) { return x * x; }

int solve() {
    int maxsum = (n + m - 1) * 30;
    FOR(i, 1, n) FOR(j, 1, m) memset(dp[i][j], 0x3f, (maxsum + 1) * sizeof(int));
    dp[1][1][mat[1][1]] = sqr(mat[1][1]);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            for(int k = 0; k <= maxsum; ++k) if(dp[i][j][k] != INF) {
                update_min(dp[i][j + 1][k + mat[i][j + 1]], dp[i][j][k] + sqr(mat[i][j + 1]));
                update_min(dp[i + 1][j][k + mat[i + 1][j]], dp[i][j][k] + sqr(mat[i + 1][j]));
            }
        }
    }
    int res = INF;
    for(int k = 0; k <= maxsum; ++k) if(dp[n][m][k] != INF)
        update_min(res, (n + m - 1) * dp[n][m][k] - sqr(k));
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%d", &mat[i][j]);
        printf("Case #%d: %d\n", t, solve());
    }
}
