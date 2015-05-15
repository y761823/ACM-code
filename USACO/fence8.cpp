/*
ID: y7618231
PROG: fence8
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <functional>
#include <cctype>
#include <vector>
#include <numeric>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 1024;
const int INF = 0x3f3f3f3f;

int a[MAXN], b[MAXN];
int bsum[MAXN];
int an, bn, ans;

bool dfs(int ap, int bp, int rest) {
    if(rest < 0) return false;
    if(bp < 0) return true;
    bool flag = false;
    for(int i = ap; i < an && !flag; ++i) if(a[i] >= b[bp]) {
        a[i] -= b[bp];
        int next_a = bp && b[bp] == b[bp - 1] ? i : 0;
        int new_rest = rest - (a[i] < b[0] ? a[i] : 0);
        flag = dfs(next_a, bp - 1, new_rest);
        a[i] += b[bp];
    }
    return flag;
}

int solve() {
    if(a[0] < b[0]) return 0;
    int asum = accumulate(a, a + an, 0);
    partial_sum(b, b + bn, bsum);

    int l = 1, r = bn + 1;
    while(l < r) {
        ans = (l + r) >> 1;
        if(dfs(0, ans - 1, asum - bsum[ans - 1])) l = ans + 1;
        else r = ans;
    }
    return l - 1;
}

int main() {
#ifndef OYK_JUDGE
    freopen("fence8.in", "r", stdin); freopen("fence8.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &an);
    for(int i = 0; i < an; ++i) scanf("%d", &a[i]);
    sort(a, a + an, greater<int>());
    scanf("%d", &bn);
    for(int i = 0; i < bn; ++i) scanf("%d", &b[i]);
    sort(b, b + bn);
    printf("%d\n", solve());
}
