/*
ID: y7618231
PROG: job
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 1010;
const int MAXM = 33;

int a[MAXM], b[MAXM];
int aend[MAXN], bend[MAXN];
int app[MAXM], bpp[MAXM];
int n, am, bm;

void solve_a() {
    REP(i, n) {
        int u = 0;
        REP(j, am) if(app[j] + a[j] < app[u] + a[u]) u = j;
        app[u] += a[u];
        aend[i] = app[u];
    }
    printf("%d", aend[n - 1]);
}

bool check(int res) {
    fill(bpp, bpp + bm, res);
    REP(i, n) {
        int u = 0;
        REP(j, bm) if(bpp[j] - b[j] > bpp[u] - b[u]) u = j;
        bpp[u] -= b[u];
        if(aend[i] > bpp[u]) return false;
    }
    return true;
}

void solve_b() {
    reverse(aend, aend + n);
    int l = 0, r = 60 * n;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }
    printf(" %d\n", l);
}

int main() {
#ifndef OYK_JUDGE
    freopen("job.in", "r", stdin); freopen("job.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d", &n, &am, &bm);
    REP(i, am) scanf("%d", &a[i]);
    REP(i, bm) scanf("%d", &b[i]);
    solve_a();
    solve_b();
}
