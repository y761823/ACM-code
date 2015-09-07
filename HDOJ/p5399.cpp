#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 110;
const int MOD = 1e9 + 7;

int a[MAXN][MAXN], f[MAXN];
int n, m;

int solve() {
    int cnt = 0;
    for(int i = 1; i <= m; ++i)
        cnt += (a[i][1] == -1);
    if(cnt == 0) {
        for(int i = 1; i <= n; ++i)
            f[i] = i;
        for(int i = m; i > 0; --i)
            for(int j = 1; j <= n; ++j) f[j] = a[i][f[j]];
        for(int i = 1; i <= n; ++i)
            if(f[i] != i) return 0;
        return 1;
    } else {
        LL x = 1;
        for(int i = 1; i <= n; ++i)
            x = x * i % MOD;
        int res = 1;
        for(int i = 1; i < cnt; ++i)
            res = res * x % MOD;
        return res;
    }
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &a[i][j]);
                if(a[i][j] == -1) break;
            }
        }
        int res = solve();
        for(int i = 1; i <= m; ++i) if(~a[i][1]) {
            sort(a[i] + 1, a[i] + n + 1);
            for(int j = 1; j <= n; ++j)
                if(a[i][j] != j) res = 0;
        }
        printf("%d\n", res);
    }
}
