////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-07 22:16:31
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4819
////Problem Title: 
////Run result: Accept
////Run time:2515MS
////Run memory:33924KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 810;
const int MAXT = MAXN << 2;
const int INF = 0x3f3f3f3f;

int n, m, T;

#define ll(x) (x << 1)
#define rr(x) (ll(x) | 1)
#define mid ((l + r) >> 1)
struct SegmentTree {
    int maxt[MAXT][MAXT], mint[MAXT][MAXT];
    int a1, b1, a2, b2;
    int maxr, minr;

    void updatex(int x, int y) {
        maxt[x][y] = max(maxt[ll(x)][y], maxt[rr(x)][y]);
        mint[x][y] = min(mint[ll(x)][y], mint[rr(x)][y]);
    }

    void updatey(int x, int y) {
        maxt[x][y] = max(maxt[x][ll(y)], maxt[x][rr(y)]);
        mint[x][y] = min(mint[x][ll(y)], mint[x][rr(y)]);
    }

    void modify(int x, int y, int l, int r, int val, bool flag) {
        if(a2 <= l && r <= b2) {
            if(flag) maxt[x][y] = mint[x][y] = val;
            else updatex(x, y);
        } else {
            if(a2 <= mid) modify(x, ll(y), l, mid, val, flag);
            if(mid < b2) modify(x, rr(y), mid + 1, r, val, flag);
            updatey(x, y);
        }
    }

    void modify(int x, int l, int r, int val) {
        if(a1 <= l && r <= b1) {
            modify(x, 1, 1, n, val, true);
        } else {
            if(a1 <= mid) modify(ll(x), l, mid, val);
            if(mid < b1) modify(rr(x), mid + 1, r, val);
            modify(x, 1, 1, n, val, false);
        }
    }

    void query(int x, int y, int l, int r) {
        if(a2 <= l && r <= b2) {
            maxr = max(maxr, maxt[x][y]);
            minr = min(minr, mint[x][y]);
        } else {
            if(a2 <= mid) query(x, ll(y), l, mid);
            if(mid < b2) query(x, rr(y), mid + 1, r);
        }
    }

    void query(int x, int l, int r) {
        if(a1 <= l && r <= b1) {
            query(x, 1, 1, n);
        } else {
            if(a1 <= mid) query(ll(x), l, mid);
            if(mid < b1) query(rr(x), mid + 1, r);
        }
    }

    void __modify(int p1, int q1, int p2, int q2, int val) {
        a1 = max(1, p1), b1 = min(n, q1);
        a2 = max(1, p2), b2 = min(n, q2);
        modify(1, 1, n, val);
    }

    int __query(int p1, int q1, int p2, int q2) {
        minr = INF; maxr = 0;
        a1 = max(1, p1), b1 = min(n, q1);
        a2 = max(1, p2), b2 = min(n, q2);
        query(1, 1, n);
        return (maxr + minr) / 2;
    }
} G;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 1, x; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &x);
                G.__modify(i, i, j, j, x);
            }
        }
        printf("Case #%d:\n", t);
        scanf("%d", &m);
        for(int i = 0, a, b, c; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            c = c / 2;
            int tmp = G.__query(a - c, a + c, b - c, b + c);
            G.__modify(a, a, b, b, tmp);
            printf("%d\n", tmp);
            //printf("Debug %d\n", G.__query(1, 1, 1, 1));
        }
    }
}
