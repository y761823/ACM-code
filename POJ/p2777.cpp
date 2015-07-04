#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = 200010;
const int INF = 0x3f3f3f3f;

int color[MAXT], cover[MAXT];
int n, m, t;

int id(int l, int r) {
    return (l + r) | (l != r);
}
#define x id(l, r)
#define mid ((l + r) >> 1)
#define ll id(l, mid)
#define rr id(mid + 1, r)

void pushdown(int l, int r) {
    if(cover[x]) {
        cover[ll] = cover[rr] = cover[x];
        color[ll] = color[rr] = 1 << (cover[x] - 1);
        cover[x] = 0;
    }
}

void update(int l, int r) {
    color[x] = color[ll] | color[rr];
}

void modify(int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        cover[x] = val;
        color[x] = 1 << (val - 1);
    } else {
        pushdown(l, r);
        if(a <= mid) modify(l, mid, a, b, val);
        if(mid < b) modify(mid + 1, r, a, b, val);
        update(l, r);
    }
}

int query(int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return color[x];
    } else {
        pushdown(l, r);
        int res = 0;
        if(a <= mid) res |= query(l, mid, a, b);
        if(mid < b) res |= query(mid + 1, r, a, b);
        return res;
    }
}

int main() {
    scanf("%d%d%d", &n, &t, &m);
    modify(0, n - 1, 0, n - 1, 1);
    char op;
    for(int i = 0, a, b, c; i < m; ++i) {
        scanf(" %c%d%d", &op, &a, &b);
        if(a > b) swap(a, b);
        if(op == 'C') {
            scanf("%d", &c);
            modify(0, n - 1, a - 1, b - 1, c);
        } else {
            printf("%d\n", __builtin_popcount(query(0, n - 1, a - 1, b - 1)));
        }
    }
}
