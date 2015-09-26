#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MOD = 1e9 + 7;

int tree[MAXN << 2];
int T, n, m;

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)

void build(int x, int l, int r) {
    if(l != r) {
        if(l <= mid) build(ll, l, mid);
        if(mid < r) build(rr, mid + 1, r);
    }
    tree[x] = 1;
}

void modify(int x, int l, int r, int pos, int val) {
    if(l == r) {
        tree[x] = val;
    } else {
        if(pos <= mid) modify(ll, l, mid, pos, val);
        if(mid < pos) modify(rr, mid + 1, r, pos, val);
        tree[x] = (LL)tree[ll] * tree[rr] % m;
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        build(1, 1, n);
        printf("Case #%d:\n", t);
        for(int i = 1, op, x; i <= n; ++i) {
            scanf("%d%d", &op, &x);
            if(op == 1) {
                modify(1, 1, n, i, x);
            } else {
                modify(1, 1, n, x, 1);
            }
            printf("%d\n", tree[1]);
        }
    }
}
