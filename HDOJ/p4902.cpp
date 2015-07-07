////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-01 15:38:49
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4902
////Problem Title: 
////Run result: Accept
////Run time:937MS
////Run memory:2756KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)

const int MAXN = 100010;
const int MAXT = MAXN << 2;

int cover[MAXT], maxt[MAXT];
int a[MAXN];
int n, m, T;

void build(int x, int l, int r) {
    if(l == r) {
        maxt[x] = cover[x] = a[l];
    } else {
        build(ll, l, mid);
        build(rr, mid + 1, r);
        cover[x] = -1;
        maxt[x] = max(maxt[ll], maxt[rr]);
    }
}

void pushdown(int x) {
    if(cover[x] != -1) {
        maxt[ll] = cover[ll] = cover[x];
        maxt[rr] = cover[rr] = cover[x];
        cover[x] = -1;
    }
}

void maintain(int x) {
    maxt[x] = max(maxt[ll], maxt[rr]);
}

void modifyCover(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        maxt[x] = cover[x] = val;
    } else {
        pushdown(x);
        if(a <= mid) modifyCover(ll, l, mid, a, b, val);
        if(mid < b) modifyCover(rr, mid + 1, r, a, b, val);
        maintain(x);
    }
}

void modifyGcd(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        if(l == r || (cover[x] != -1 && val < cover[x])) {
            if(val < cover[x]) maxt[x] = cover[x] = __gcd(cover[x], val);
        } else {
            pushdown(x);
            if(val < maxt[ll]) modifyGcd(ll, l, mid, a, b, val);
            if(val < maxt[rr]) modifyGcd(rr, mid + 1, r, a, b, val);
            maintain(x);
        }
    } else {
        pushdown(x);
        if(a <= mid) modifyGcd(ll, l, mid, a, b, val);
        if(mid < b) modifyGcd(rr, mid + 1, r, a, b, val);
        maintain(x);
    }
}

void solve(int x, int l, int r) {
    if(l == r) {
        a[l] = cover[x];
    } else {
        pushdown(x);
        solve(ll, l, mid);
        solve(rr, mid + 1, r);
    }
}

void print() {
    solve(1, 1, n);
    for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
    puts("");
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        build(1, 1, n);
        scanf("%d", &m);
        for(int i = 0, op, l, r, x; i < m; ++i) {
            scanf("%d%d%d%d", &op, &l, &r, &x);
            if(op == 1) modifyCover(1, 1, n, l, r, x);
            if(op == 2) modifyGcd(1, 1, n, l, r, x);
        }
        print();
    }
}
