#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11;
const int MAXM = 105;

int dp[MAXM][MAXN][MAXN][MAXN][MAXN];
int a[MAXN], b[MAXN];
int m, n;

int solve(int rest, int p1, int p2, int p3, int p4) {
    if(rest <= 0) return 0;
    int &res = dp[rest][p1][p2][p3][p4];
    if(res) return res;
    res = 0x3f3f3f3f;
    for(int i = 0; i < n; ++i) {
        if(p1 == i && b[i] >= 1) continue;
        if(p2 == i && b[i] >= 2) continue;
        if(p3 == i && b[i] >= 3) continue;
        if(p4 == i && b[i] >= 4) continue;
        res = min(res, solve(rest - a[i], i, p1, p2, p3) + 1);
    }
    if(!(p1 == n && p2 == n && p3 == n && p4 == n))
        res = min(res, solve(rest, n, p1, p2, p3) + 1);
    return res;
}

int main() {
    scanf("%d%d", &m, &n);
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &a[i], &b[i]);
    printf("%d\n", solve(m, n, n, n, n));
}
