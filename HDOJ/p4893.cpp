////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-05 16:24:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4893
////Problem Title: 
////Run result: Accept
////Run time:1468MS
////Run memory:4704KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = MAXN << 2;

bool flip[MAXT];
LL tsum[MAXT], tfib[MAXT];
LL fib[MAXN];
int n, m, total;

void initFib(int n) {
    total = n;
    fib[0] = fib[1] = 1;
    for(int i = 2; i <= total; ++i) fib[i] = fib[i - 1] + fib[i - 2];
    //cout<<fib[n]<<endl;
}

LL nearest(LL x) {
    int t = lower_bound(fib, fib + total, x) - fib;
    if(t == 0) return 1;
    return fib[t] - x < x - fib[t - 1] ? fib[t] : fib[t - 1];
}

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)

void pushdown(int x) {
    if(flip[x]) {
        tsum[ll] = tfib[ll];
        flip[ll] = true;
        tsum[rr] = tfib[rr];
        flip[rr] = true;
        flip[x] = false;
    }
}

void update(int x) {
    tsum[x] = tsum[ll] + tsum[rr];
    tfib[x] = tfib[ll] + tfib[rr];
}

void build(int x, int l, int r) {
    if(l == r) {
        tsum[x] = 0;
        tfib[x] = 1;
    } else {
        build(ll, l, mid);
        build(rr, mid + 1, r);
        update(x);
    }
    flip[x] = 0;
}

void modifyk(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        tfib[x] = nearest(tsum[x] += val);
    } else {
        pushdown(x);
        if(a <= mid) modifyk(ll, l, mid, a, b, val);
        if(mid < b) modifyk(rr, mid + 1, r, a, b, val);
        update(x);
    }
}

void modifyFib(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        tsum[x] = tfib[x];
        flip[x] = true;
    } else {
        pushdown(x);
        if(a <= mid) modifyFib(ll, l, mid, a, b);
        if(mid < b) modifyFib(rr, mid + 1, r, a, b);
        update(x);
    }
}

LL query(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return tsum[x];
    } else {
        pushdown(x);
        LL ret = 0;
        if(a <= mid) ret += query(ll, l, mid, a, b);
        if(mid < b) ret += query(rr, mid + 1, r, a, b);
        return ret;
    }
}

int main() {
    initFib(170);
    //while(cin>> n) cout<<nearest(n)<<endl;
    while(scanf("%d%d", &n, &m) != EOF) {
        build(1, 1, n);
        for(int i = 0, op, a, b; i < m; ++i) {
            scanf("%d%d%d", &op, &a, &b);
            if(op == 1) modifyk(1, 1, n, a, a, b);
            if(op == 2) printf("%I64d\n", query(1, 1, n, a, b));
            if(op == 3) modifyFib(1, 1, n, a, b);
        }
    }
}
