#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

vector<int> sons[MAXN];
int dp[MAXN][MAXN], size[MAXN];
int T, n, k;

int inv(int a) {
    if(a == 1) return 1;
    return LL(MOD - MOD / a) * inv(MOD % a) % MOD;
}

int dfs(int u, int f) {
    size[u] = 1;
    for(int v : sons[u]) if(v != f)
        size[u] += dfs(v, u);
    return size[u];
}

int solve() {
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        int v = inv(size[i]);
        dp[i][0] = (LL)dp[i - 1][0] * (size[i] - 1) % MOD;
        dp[i][0] = (LL)dp[i][0] * v % MOD;
        for(int j = 1; j <= i; ++j) {
            dp[i][j] = ((LL)dp[i - 1][j] * (size[i] - 1) + dp[i - 1][j - 1]) % MOD;
            dp[i][j] = (LL)dp[i][j] * v % MOD;
        }
    }
    for(int i = 2; i <= n; ++i)
        dp[n][k] = (LL)dp[n][k] * i % MOD;
    return dp[n][k];
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &k);
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            sons[u].push_back(v);
            sons[v].push_back(u);
        }
        dfs(1, 0);
        printf("Case #%d: %d\n", t, solve());
        for(int i = 1; i <= n; ++i) sons[i].clear();
    }
}
