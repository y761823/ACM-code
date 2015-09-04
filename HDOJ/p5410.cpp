#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int MAXN = 1010;
const int MAXM = 2010;

int dp[MAXM], vis[MAXM];
int w[MAXN], a[MAXN], b[MAXN];
int T, n, m;

bool update_max(int &a, int b) {
    if(a < b) return a = b, true;
    return false;
}

int solve() {
    memset(dp, 0, (m + 1) * sizeof(int));
    for(int i = 0; i < n; ++i) {
        memset(vis, 0, (m + 1) * sizeof(int));
        for(int j = w[i]; j <= m; ++j) {
            int pre = j - w[i];
            update_max(vis[j], max(dp[pre], vis[pre]) + a[i]);
        }
        for(int j = w[i]; j <= m; ++j)
            update_max(dp[j], vis[j] + b[i]);
    }
    return dp[m];
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &m, &n);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &w[i], &a[i], &b[i]);
        }
        printf("%d\n", solve());
    }
}
