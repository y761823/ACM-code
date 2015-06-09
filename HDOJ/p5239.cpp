#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int MAXT = 200010;
const ULL MOD = 9223372034707292160ULL;

ULL add(ULL a, ULL b) {
    ULL c = a + b;
    if(c >= MOD) c -= MOD;
    return c;
}

ULL mul(ULL a, ULL b) {
    ULL res = 0;
    while(b) {
        if(b & 1) res = add(res, a);
        a = add(a, a);
        b >>= 1;
    }
    return res;
}

int root(int l, int r) { return (l + r) | (l != r); }
#define x root(l, r)
#define mid ((l + r) >> 1)
#define ll root(l, mid)
#define rr root(mid + 1, r)
ULL val[MAXT], sum[MAXT];
bool stable[MAXT];
int T, n, m;

void update(int l, int r) {
    sum[x] = add(sum[ll], sum[rr]);
    stable[x] = (stable[ll] && stable[rr]);
}

void build(int l, int r) {
    if(l == r) {
        scanf("%I64u", &val[x]);
        sum[x] = val[x];
        stable[x] = false;
    } else {
        build(l, mid);
        build(mid + 1, r);
        update(l, r);
    }
}

void modify(int l, int r, int a, int b) {
    if(stable[x]) return ;
    if(l == r) {
        ULL t = mul(val[x], val[x]);
        stable[x] = (t == val[x]);
        sum[x] = val[x] = t;
    } else {
        if(a <= mid) modify(l, mid, a, b);
        if(mid < b) modify(mid + 1, r, a, b);
        update(l, r);
    }
}

ULL query(int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return sum[x];
    } else {
        ULL res = 0;
        if(a <= mid) res = add(res, query(l, mid, a, b));
        if(mid < b) res = add(res, query(mid + 1, r, a, b));
        return res;
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        build(0, n - 1);
        ULL s = 0;
        printf("Case #%d:\n", t);
        for(int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            s = add(s, query(0, n - 1, a - 1, b - 1));
            modify(0, n - 1, a - 1, b - 1);
            printf("%I64u\n", s);
        }
    }
}
