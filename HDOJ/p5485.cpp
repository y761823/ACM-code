#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <tuple>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 1010;
const int MOD = 105225319;

int c[MAXN][MAXN], v[MAXN * MAXN];
int f[MAXN], g[MAXN], dp[MAXN];
int T, n, m;

int inv(int a) {
    if(a == 1) return 1;
    return LL(MOD - MOD / a) * inv(MOD % a) % MOD;
}

int inv2 = inv(2);

void init() {
    v[0] = 1;
    for(int i = 1; i <= n * n; ++i)
        v[i] = (LL)v[i - 1] * (m + 1) % MOD;
    for(int i = 1; i <= n; ++i) {
        g[i] = 0;
        for(int k = 0; k <= i; ++k)
            g[i] = (g[i] + (LL)c[i][k] * v[k * (i - k)]) % MOD;
    }
    for(int i = 1; i <= n; ++i) {
        f[i] = 0;
        for(int k = 1; k < i; ++k)
            f[i] = (f[i] + (LL)c[i - 1][k - 1] * f[k] % MOD * g[i - k]) % MOD;
        f[i] = (g[i] - f[i] + MOD) % MOD;
    }
    for(int i = 1; i <= n; ++i)
        f[i] = (LL)f[i] * inv2 % MOD;
}

int solve() {
    if(n == 1) return 0;
    init();
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= n; ++i) {
        dp[i] = 0;
        for(int k = 1; k <= i; ++k)
            dp[i] = (dp[i] + (LL)c[i - 1][k - 1] * f[k] % MOD * dp[i - k]) % MOD;
    }
    return dp[n];
}

int main() {
    for(int i = 0; i <= 1000; ++i) {
        c[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }

    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        printf("Case #%d: %d\n", t, solve());
    }
}
