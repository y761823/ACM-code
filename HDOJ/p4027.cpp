////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-28 00:04:08
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4027
////Problem Title: 
////Run result: Accept
////Run time:1109MS
////Run memory:16492KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
typedef long double LDB;

const int MAXN = 100010;
const int MAXT = MAXN << 2;
const int MAXP = 7;

LL sum[MAXT][MAXP];
int cnt[MAXT];
LL init[MAXN];
int n, m, a, b, c;

struct SegmentTree {
    #define ll (x << 1)
    #define rr (ll | 1)
    #define mid ((l + r) >> 1)

    inline int get(int t) {
        return min(t, MAXP - 1);
    }

    void pushdown(int x) {
        if(cnt[x]) {
            cnt[ll] += cnt[x];
            cnt[rr] += cnt[x];
            cnt[x] = 0;
        }
    }

    void update(int x) {
        for(int i = 0; i < MAXP; ++i) {
            sum[x][i] = sum[ll][get(i + cnt[ll])] + sum[rr][get(i + cnt[rr])];
        }
    }

    void build(int x, int l, int r) {
        cnt[x] = 0;
        if(l == r) {
            sum[x][0] = init[l];
            for(int i = 1; i < MAXP; ++i) sum[x][i] = LL(sqrtl((LDB)sum[x][i - 1]) + 1e-10);
        } else {
            build(ll, l, mid);
            build(rr, mid + 1, r);
            update(x);
        }
    }

    void modify(int x, int l, int r) {
        if(a <= l && r <= b) {
            cnt[x]++;
        } else {
            pushdown(x);
            if(a <= mid) modify(ll, l, mid);
            if(mid < b) modify(rr, mid + 1, r);
            update(x);
        }
    }

    LL query(int x, int l, int r, int p = 0) {
        if(a <= l && r <= b) {
            return sum[x][get(p + cnt[x])];
        } else {
            LL res = 0;
            if(a <= mid) res += query(ll, l, mid, p + cnt[x]);
            if(mid < b) res += query(rr, mid + 1, r, p + cnt[x]);
            return res;
        }
    }
} T;

LL readLL() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    LL res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

int main() {
    int kase = 0;
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i) init[i] = readLL();
        T.build(1, 1, n);
        printf("Case #%d:\n", ++kase);
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &c, &a, &b);
            if(a > b) swap(a, b);
            if(c == 0) T.modify(1, 1, n);
            else printf("%I64d\n", T.query(1, 1, n));
        }
        puts("");
    }
}