#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

char s1[MAXN], s2[MAXN];
int dp[MAXN][MAXN];
int n, m;

int main() {
    while(scanf("%d%s", &n, s1 + 1) != EOF) {
        scanf("%d%s", &m, s2 + 1);
        dp[0][0] = 0;
        for(int i = 1; i <= n; ++i) dp[i][0] = i;
        for(int j = 1; j <= m; ++j) dp[0][j] = j;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (s1[i] != s2[j]));
            }
        }
        printf("%d\n", dp[n][m]);
    }
}
