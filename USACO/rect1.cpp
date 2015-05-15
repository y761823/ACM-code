/*
ID: y7618231
PROG: rect1
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 1010;

int a, b, n;
struct Rect {
    int l, r, b, t, c;
    void read() {
        scanf("%d%d%d%d%d", &l, &b, &r, &t, &c);
    }
    Rect() {}
    Rect(int l, int r, int b, int t, int c):
        l(l), r(r), b(b), t(t), c(c) {}
} rect[MAXN];

int col[2555];

void cal(Rect p, int k) {
    while(k < n && (rect[k].r <= p.l || p.r <= rect[k].l || rect[k].t <= p.b || p.t <= rect[k].b)) ++k;
    if(k == n) {col[p.c] += (p.r - p.l) * (p.t - p.b); return ;}
    if(p.l < rect[k].l) cal(Rect(p.l, rect[k].l, p.b, p.t, p.c), k + 1), p.l = rect[k].l;
    if(rect[k].r < p.r) cal(Rect(rect[k].r, p.r, p.b, p.t, p.c), k + 1), p.r = rect[k].r;
    if(p.b < rect[k].b) cal(Rect(p.l, p.r, p.b, rect[k].b, p.c), k + 1);
    if(rect[k].t < p.t) cal(Rect(p.l, p.r, rect[k].t, p.t, p.c), k + 1);
}

void solve() {
    scanf("%d%d%d", &a, &b, &n);
    for(int i = 0; i < n; ++i) rect[i].read();
    for(int i = 0; i < n; ++i)
        cal(rect[i], i + 1);
    col[1] += a * b - accumulate(col + 1, col + 2500 + 1, 0);
    for(int i = 1; i <= 2500; ++i)
        if(col[i]) printf("%d %d\n", i, col[i]);
}

int main() {
#ifndef OYK_JUDGE
    freopen("rect1.in", "r", stdin); freopen("rect1.out", "w", stdout);
#endif
    solve();
}
