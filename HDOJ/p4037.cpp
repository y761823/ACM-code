////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-25 20:30:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4037
////Problem Title: 
////Run result: Accept
////Run time:1734MS
////Run memory:7304KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = MAXN << 2;
const int MOD = 20110911;

int T, n, q;
int c[MAXN], d[MAXN];

LL mod(LL x) {
    return x % MOD;
}

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
struct SegmentTree {
    int addc[MAXT], addd[MAXT];
    int sumc[MAXT], sumd[MAXT], treed[MAXT];
    int summ[MAXT];

    void update(int x, int l, int r) {
        LL sr = r - mid;
        sumc[x] = mod(sumc[ll] + sumc[rr]);
        sumd[x] = mod(sumd[ll] + sumd[rr]);
        treed[x] = mod(treed[ll] + sumd[ll] * sr + treed[rr]);
        LL initM = mod(treed[ll] - sumc[ll] + MOD);
        summ[x] = mod(summ[ll] + summ[rr] + mod(sr * initM) + mod(mod(sr * (sr + 1) / 2) * (LL)sumd[ll]));
    }

    void add_c(int x, int l, int r, int val) {
        LL s = r - l + 1;
        addc[x] = mod(addc[x] + val);
        sumc[x] = mod(sumc[x] + s * val);
        summ[x] = mod(summ[x] - mod(mod(s * (s + 1) / 2) * (LL)val) + MOD);
    }

    void add_d(int x, int l, int r, int val) {
        LL s = r - l + 1;
        addd[x] = mod(addd[x] + val);
        sumd[x] = mod(sumd[x] + val * s);
        treed[x] = mod(treed[x] + mod(s * (s - 1) / 2) * val);
        LL cnt = (LL(s) * (s + 1) * (2 * s + 1) - 3 * s * (s + 1)) / 12;
        summ[x] = mod(summ[x] + mod(cnt) * (LL)val);
    }

    void pushdown(int x, int l, int r) {
        if(addc[x]) {
            add_c(ll, l, mid, addc[x]);
            add_c(rr, mid + 1, r, addc[x]);
            addc[x] = 0;
        }
        if(addd[x]) {
            add_d(ll, l, mid, addd[x]);
            add_d(rr, mid + 1, r, addd[x]);
            addd[x] = 0;
        }
    }

    void build(int x, int l, int r) {
        addc[x] = addd[x] = 0;
        if(l == r) {
            sumd[x] = d[l];
            treed[x] = 0;
            sumc[x] = c[l];
            summ[x] = -c[l] + MOD;
        } else {
            build(ll, l, mid);
            build(rr, mid + 1, r);
            update(x, l, r);
        }
    }

    void update_c(int x, int l, int r, int a, int b, int val) {
        if(a <= l && r <= b) {
            add_c(x, l, r, val);
        } else {
            pushdown(x, l, r);
            if(a <= mid) update_c(ll, l, mid, a, b, val);
            if(mid < b) update_c(rr, mid + 1, r, a, b, val);
            update(x, l, r);
        }
    }

    void update_d(int x, int l, int r, int a, int b, int val) {
        if(a <= l && r <= b) {
            add_d(x, l, r, val);
        } else {
            pushdown(x, l, r);
            if(a <= mid) update_d(ll, l, mid, a, b, val);
            if(mid < b) update_d(rr, mid + 1, r, a, b, val);
            update(x, l, r);
        }
    }

    int query(int x, int l, int r, int a, int b, int &initd, int &initt, int &initc) {
        if(a <= l && r <= b) {
            initt = mod(initt + initd * LL(r - l + 1) + treed[x]);
            initd = mod(initd + sumd[x]);
            initc = mod(initc + sumc[x]);
            return summ[x];
        } else {
            pushdown(x, l, r);
            LL sr = min(b, r) - mid;
            int res = 0;
            if(a <= mid) res = mod(res + query(ll, l, mid, a, b, initd, initt, initc));
            if(mid < b) {
                int initM = mod(initt - initc + MOD);
                res = mod(res + initM * sr + mod(sr * (sr + 1) / 2) * (LL)initd);
                //res = mod(res + query(rr, mid + 1, r, a, b, initd, initt, initc));
                int dd = 0, tt = 0, cc = 0;
                res = mod(res + query(rr, mid + 1, r, a, b, dd, tt, cc));
                initt = mod(initt + initd * sr + tt);
                initd = mod(initd + dd);
                initc = mod(initc + cc);
            }
            return res;
        }
    }

    int query(int x, int l, int r, int a, int b) {
        int initd = 0, initt = 0, initc = 0;
        return query(x, l, r, a, b, initd, initt, initc);
    }
} G;

char s[10];

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d%d", &c[i], &d[i]);
        G.build(1, 1, n);
        printf("Case %d:\n", t);
        //cout<<G.query(1, 1, n, 1, 3)<<endl;
        scanf("%d", &q);
        for(int i = 0, x, y, z; i < q; ++i) {
            scanf("%s%d%d", s, &x, &y);
            if(strcmp(s, "Cost") == 0) {
                scanf("%d", &z);
                G.update_c(1, 1, n, x, y, z);
            } else if(strcmp(s, "Collect") == 0) {
                scanf("%d", &z);
                G.update_d(1, 1, n, x, y, z);
            } else if(strcmp(s, "Query") == 0) {
                printf("%d\n", G.query(1, 1, n, x, y));
            }
        }
    }
}
