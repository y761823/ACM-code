////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-15 15:24:35
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1754
////Problem Title: 
////Run result: Accept
////Run time:1078MS
////Run memory:3160KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 200010;
const int MAXT = MAXN << 2;

int a[MAXN], n, m;
int maxt[MAXT];

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
void update(int x) {
    maxt[x] = max(maxt[ll], maxt[rr]);
}

void build(int x, int l, int r) {
    if(l == r) {
        maxt[x] = a[l];
    } else {
        build(ll, l, mid);
        build(rr, mid + 1, r);
        update(x);
    }
}

void modify(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        maxt[x] = val;
    } else {
        if(a <= mid) modify(ll, l, mid, a, b, val);
        if(mid < b) modify(rr, mid + 1, r, a, b, val);
        update(x);
    }
}

int query(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return maxt[x];
    } else {
        int res = 0;
        if(a <= mid) res = max(res, query(ll, l, mid, a, b));
        if(mid < b) res = max(res, query(rr, mid + 1, r, a, b));
        return res;
    }
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        build(1, 1, n);
        char c;
        for(int i = 0, a, b; i < m; ++i) {
            scanf(" %c%d%d", &c, &a, &b);
            if(c == 'U') modify(1, 1, n, a, a, b);
            if(c == 'Q') printf("%d\n", query(1, 1, n, a, b));
        }
    }
}