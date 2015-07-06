#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1010;

struct Node {
    int y, st, ed;
    void read() {
        scanf("%d%d%d", &y, &st, &ed);
    }
    bool operator < (const Node &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return ed < rhs.ed;
    }
};

int length(const Node &a, const Node &b) {
    if(a.y == b.y) return b.st - a.ed;
    return a.ed + b.st;
}

Node a[MAXN];
int dp[MAXN][MAXN];
int n, t, ans;

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    ans = 0;
    for(int i = 1; i <= n; ++i) {
        if((dp[i][1] = 2 * a[i].ed - a[i].st) <= t) ans = max(ans, 1);
        for(int j = 2; j <= i; ++j) {
            for(int k = j - 1; k < i; ++k)
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + length(a[k], a[i]));
            dp[i][j] += 2 * (a[i].ed - a[i].st);
            if(dp[i][j] <= t) ans = max(ans, j);
        }
    }
}

int main() {
    while(scanf("%d%d", &n, &t) != EOF && n + t) {
        for(int i = 1; i <= n; ++i) a[i].read();
        sort(a + 1, a + n + 1);
        solve();
        printf("%d\n", ans);
    }
}
