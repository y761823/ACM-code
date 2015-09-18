#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 200010;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

char str[MAXN];
int dp[MAXN][2], a[MAXN];
int n, T;

void update_max(int &a, int b, int c = 0) {
    if(b != -1) a = max(a, b + c);
}

int solve() {
    dp[0][0] = (str[0] != '1' ?    0 : -1);
    dp[0][1] = (str[0] != '0' ? a[0] : -1);
    for(int i = 1; i < n; ++i) {
        dp[i][0] = dp[i][1] = -1;
        if(str[i] == '0' || str[i] == '?') {
            update_max(dp[i][0], dp[i - 1][0]);
            update_max(dp[i][0], dp[i - 1][1], a[i]);
        }
        if(str[i] == '1' || str[i] == '?') {
            update_max(dp[i][1], dp[i - 1][1]);
            update_max(dp[i][1], dp[i - 1][0], a[i]);
        }
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", str);
        n = strlen(str);
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        printf("Case #%d: %d\n", t, solve());
    }
}
