#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = 200010;
const int INF = 0x3f3f3f3f;

int sum[MAXT], lmax[MAXT], rmax[MAXT], mmax[MAXT], pmax[MAXT], mint[MAXT];
int val[MAXN];
int n, m;

int id(int l, int r) {
    return (l + r) | (l != r);
}
#define x id(l, r)
#define mid ((l + r) >> 1)
#define ll id(l, mid)
#define rr id(mid + 1, r)

void setVal(int l, int r, int v) {
    sum[x] = mint[x] = v;
    lmax[x] = rmax[x] = mmax[x] = pmax[x] = max(0, v);
}

void update(int l, int r) {
    sum[x] = sum[ll] + sum[rr];
    lmax[x] = max(lmax[ll], sum[ll] + lmax[rr]);
    rmax[x] = max(rmax[rr], rmax[ll] + sum[rr]);
    mmax[x] = max(rmax[ll] + lmax[rr], max(mmax[ll], mmax[rr]));
    pmax[x] = max(lmax[ll] + rmax[rr], max(pmax[ll] + sum[rr], sum[ll] + pmax[rr]));
    mint[x] = min(mint[ll], mint[rr]);
    //printf("debug %d %d\n", mmax[x], pmax[x]);
}

void build(int l, int r) {
    if(l == r) {
        setVal(l, r, val[l]);
    } else {
        build(l, mid);
        build(mid + 1, r);
        update(l, r);
    }
}

void modify(int l, int r, int p, int v) {
    if(l == r) {
        setVal(l, r, v);
    } else {
        if(p <= mid) modify(l, mid, p, v);
        if(mid < p) modify(mid + 1, r, p, v);
        update(l, r);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &val[i]);
    build(0, n - 1);

    scanf("%d", &m);
    for(int i = 0, p, v, rt = id(0, n - 1); i < m; ++i) {
        scanf("%d%d", &p, &v);
        modify(0, n - 1, p - 1, v);
        if(mint[rt] >= 0) printf("%d\n", sum[rt] - mint[rt]);
        else printf("%d\n", max(mmax[rt], pmax[rt]));
    }
}
