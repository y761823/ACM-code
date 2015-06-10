//据说这样搞可以AC？
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

struct Node {
    int l, r, pow, id;
    bool operator < (const Node &rhs) const {
        if(r != rhs.r) return r < rhs.r;
        return l < rhs.l;
    }
    bool operator == (const Node &rhs) const {
        return l == rhs.l && r == rhs.r;
    }
};

int n;
Node a[MAXN];
int dp[MAXN], pre[MAXN], last[MAXN];
bool use[MAXN], ans[MAXN];

void solve() {
    memset(dp, 0, sizeof(dp));
    int cur = 0;
    for(int i = 1; i <= n; ++i) {
        pre[i] = i - 1;
        dp[i] = dp[i - 1];
        last[i] = -1;
        while(cur < n && a[cur].r == i) {
            if(dp[i] < dp[a[cur].l - 1] + a[cur].pow) {
                pre[i] = a[cur].l - 1;
                dp[i] = dp[a[cur].l - 1] + a[cur].pow;
                last[i] = cur;
            }
            ++cur;
        }
    }
}

void output() {
    int cur = n;
    while(cur > 0) {
        if(last[cur] != -1) use[last[cur]] = true;
        cur = pre[cur];
    }
    for(int i = n - 1; i > 0; --i)
        if(use[i] && a[i] == a[i - 1]) use[i - 1] = true;
    printf("%d", n - dp[n]);
    for(int i = 0; i < n; ++i) ans[a[i].id] = !use[i];
    for(int i = 1; i <= n; ++i) if(ans[i]) printf(" %d", i);
    puts("");
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[i].l = x + 1;
            a[i].r = n - y;
            if(x + y >= n) a[i].r = n + 1;
            a[i].pow = 1;
            a[i].id = i + 1;
        }
        sort(a, a + n);
        for(int i = 0; i < n - 1; ++i)
            if(a[i] == a[i + 1]) a[i + 1].pow += a[i].pow;
        for(int i = 0; i < n; ++i)
            a[i].pow = min(a[i].pow, a[i].r - a[i].l + 1);
        solve();
        output();
    }
}
