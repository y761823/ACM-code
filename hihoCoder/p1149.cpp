#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1010;
const int MOD = 100007;

char s[MAXN];
int dp[MAXN][MAXN];
int T, n;

int solve() {
    for(int i = 0; i < n; ++i) dp[i][i] = 1;
    for(int step = 1; step < n; ++step) {
        for(int l = 0; l + step < n; ++l) {
            int r = l + step;
            dp[l][r] = (dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + MOD) % MOD;
            if(s[l] == s[r]) {
                dp[l][r] = (dp[l][r] + dp[l + 1][r - 1] + 1) % MOD;
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", s);
        n = strlen(s);
        printf("Case #%d: %d\n", t, solve());
    }
}
