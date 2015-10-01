#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 100010;

int a[MAXN], b[MAXN], tree[10010], lmax[MAXN], rmax[MAXN];
int n, m = 10000;

int lowbit(int x) {
    return x & -x;
}
void modify(int x, int val) {
    while(x) {
        tree[x] = max(tree[x], val);
        x -= lowbit(x);
    }
}
int query(int x) {
    int res = 0;
    while(x <= m) {
        res = max(res, tree[x]);
        x += lowbit(x);
    }
    return res;
}

void init(int n) {
    memset(tree + 1, 0, m * sizeof(int));
    lmax[0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i] == 0 || a[i] == m) {
            lmax[i] = lmax[i - 1];
        } else {
            lmax[i] = a[i] + query(a[i]);
            modify(a[i], lmax[i]);
            lmax[i] = max(lmax[i], lmax[i - 1]);
        }
    }

    memset(tree + 1, 0, m * sizeof(int));
    rmax[n + 1] = 0;
    for(int i = n; i > 0; --i) {
        if(a[i] == 0 || a[i] == m) {
            rmax[i] = rmax[i + 1];
        } else {
            rmax[i] = a[i] + query(a[i]);
            modify(a[i], rmax[i]);
            rmax[i] = max(rmax[i], rmax[i + 1]);
        }
    }
}

int solve() {
    int res = 0;
    for(int i = 0; i < n; ++i) if(b[i] == m) {
        for(int j = 1; j < n; ++j)
            a[j] = b[(i + j) % n];
        init(n - 1);
        res = max(res, max(lmax[1], rmax[n - 1]));
        for(int i = 1; i < n - 1; ++i)
            res = max(res, lmax[i] + rmax[i + 1]);
    }
    return res + m;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) scanf("%d", &b[i]);
        printf("%d\n", solve());
    }
}
