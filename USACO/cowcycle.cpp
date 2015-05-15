/*
ID: y7618231
PROG: cowcycle
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
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(i = s; i <= t; ++i)

const int MAXN = 77;

int F, R;
int ansf[5], ansr[10];
double minans = 1e100;
int f[5], r[10];
int f1, f2, r1, r2;
int minf, maxf, minr, maxr;

void calc() {
    static double tmp[50];
    assert(f[F - 1] * r[R - 1] >= 3 * f[0] * r[0]);
    int cnt = 0;
    for(int i = 0; i < F; ++i)
        for(int j = 0; j < R; ++j) tmp[cnt++] = (double)f[i] / r[j];
    sort(tmp, tmp + cnt);
    cnt--;
    for(int i = 0; i < cnt; ++i) tmp[i] = tmp[i + 1] - tmp[i];
    double avg = accumulate(tmp, tmp + cnt, 0.0) / double(cnt);
    double res = 0;
    for(int i = 0; i < cnt; ++i)
        res += (tmp[i] - avg) * (tmp[i] - avg);
    res /= cnt;
    if(res < minans) {
        minans = res;
        memcpy(ansf, f, sizeof(f));
        memcpy(ansr, r, sizeof(r));
    }
}

void dfs2(int dep, int pre) {
    if(dep >= R - 1) calc();
    else FOR(r[dep], pre, maxr - 1) dfs2(dep + 1, r[dep] + 1);
}

void dfs1(int dep, int pre) {
    if(dep >= F - 1) dfs2(1, r[0] + 1);
    else FOR(f[dep], pre, maxf - 1) dfs1(dep + 1, f[dep] + 1);
}

void print(int a[], int n) {
    for(int i = 0; i < n; ++i) {
        if(i) putchar(' ');
        printf("%d", a[i]);
    }
    puts("");
}

void solve() {
    FOR(minf, f1, f2) FOR(maxf, minf + (F != 1), f2)
    FOR(minr, r1, r2) FOR(maxr, minr + (R != 1), r2)
    if(maxf * maxr >= 3 * minf * minr) {
        f[0] = minf, f[F - 1] = maxf;
        r[0] = minr, r[R - 1] = maxr;
        dfs1(1, f[0] + 1);
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("cowcycle.in", "r", stdin); freopen("cowcycle.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &F, &R);
    scanf("%d%d%d%d", &f1, &f2, &r1, &r2);
    solve();
    print(ansf, F);
    print(ansr, R);
}
