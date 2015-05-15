#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXM = 110;

int dp[MAXN][MAXM], pre[MAXN][MAXM];
char s1[MAXN], s2[MAXM];
int n, m;

void update_max(int &a, const int &b) {
    if(a < b) a = b;
}

int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    n = strlen(s1 + 1);
    m = strlen(s2 + 1);
    for(int i = 1; i <= n; ++i) pre[i][1] = i * (s1[i] == s2[1]);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(dp[i][j] <= dp[i - 1][j]) {
                update_max(pre[i][j], pre[i - 1][j]);
                dp[i][j] = dp[i - 1][j];
            }
            if(s1[i] == s2[j] && dp[i][j] <= dp[i - 1][j - 1] + 1) {
                update_max(pre[i][j], pre[i - 1][j - 1]);
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
        }
    }
    LL ans = 0, t = 0;
    for(int i = 1; i <= n; ++i) {
        if(dp[i][m] != m) continue;
        ans += (pre[i][m] - t) * (n - i + 1);
        t = pre[i][m];
    }
    cout<<ans<<endl;
}
