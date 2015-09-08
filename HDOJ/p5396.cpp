#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MOD = 1e9 + 7;

int dp[MAXN][MAXN], c[MAXN][MAXN], cnt[MAXN];
char op[MAXN];
int n;

void init_c(int n = 100) {
    for(int i = 0; i <= n; ++i) {
        c[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
}

void init_cnt(int n = 100) {
    cnt[1] = 1;
    for(int i = 2; i <= n; ++i) cnt[i] = (LL)cnt[i - 1] * (i - 1) % MOD;
    //for(int i = 1; i <= 10; ++i) printf("cnt %d %d\n", i, cnt[i]);
}

LL mul(int a, int b) {
    return (LL)a * b % MOD;
}

int solve() {
    for(int step = 1; step < n; ++step) {
        for(int i = 0; i + step < n; ++i) {
            int j = i + step;
            for(int k = i; k < j; ++k) {
                int t = c[step - 1][k - i];
                if(op[k] == '+') {
                    dp[i][j] = (dp[i][j] + (mul(cnt[j - k], dp[i][k]) + mul(cnt[k - i + 1], dp[k + 1][j])) * t) % MOD;
                }
                if(op[k] == '-') {
                    dp[i][j] = (dp[i][j] + (mul(cnt[j - k], dp[i][k]) + mul(cnt[k - i + 1], MOD - dp[k + 1][j])) * t) % MOD;
                }
                if(op[k] == '*') {
                    dp[i][j] = (dp[i][j] + mul(dp[i][k], dp[k + 1][j]) * t) % MOD;
                }
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    init_c();
    init_cnt();
    while(scanf("%d", &n) != EOF) {
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; ++i)
            scanf("%d", &dp[i][i]);
        scanf("%s", op);
        printf("%d\n", solve());
    }
}
