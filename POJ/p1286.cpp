#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 25;

int n, m = 3;
bool vis[MAXN];

LL power(LL x, int p) {
    LL ret = 1;
    while(p) {
        if(p & 1) ret *= x;
        x *= x;
        p >>= 1;
    }
    return ret;
}

LL solve() {
    LL ans = 0;
    for(int step = 0; step < n; ++step) {
        memset(vis, 0, sizeof(vis));
        int t = 0;
        for(int i = 0; i < n; ++i) {
            if(vis[i]) continue;
            for(int j = i; !vis[j]; j = (j + step) % n) vis[j] = true;
            ++t;
        }
        ans += power(m, t);
    }
    if(n & 1) ans += n * power(m, (n + 1) / 2);
    else ans += (n / 2) * power(m, n / 2 + 1) + (n / 2) * power(m, n / 2);
    return n == 0 ? 0 : ans / (2 * n);
}

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == -1) break;
        printf("%I64d\n", solve());
    }
}
