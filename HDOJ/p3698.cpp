////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:51:53
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3698
////Problem Title: 
////Run result: Accept
////Run time:1484MS
////Run memory:4428KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 110;
const int MAXM = 5010;
const int INF = 0x3f3f3f3f;

int high[MAXN][MAXM], siz[MAXN][MAXM];
int n, m;

int tree[MAXM * 4], mint[MAXM * 4];

inline void update_min(int &a, const int &b) {
    if(a > b) a = b;
}

inline void pushdown(int x) {
    int ll = x << 1, rr = ll ^ 1;
    if(tree[x] == INF) return ;
    update_min(tree[ll], tree[x]);
    update_min(tree[rr], tree[x]);
    update_min(mint[ll], tree[ll]);
    update_min(mint[rr], tree[rr]);
    tree[x] = INF;
}

inline void update(int x) {
    int ll = x << 1, rr = ll ^ 1;
    mint[x] = min(mint[ll], mint[rr]);
}

void update(int x, int left, int right, int L, int R, int val) {
    if(L <= left && right <= R) {
        update_min(tree[x], val);
        update_min(mint[x], val);
    }
    else {
        pushdown(x);
        int ll = x << 1, rr = ll ^ 1;
        int mid = (left + right) >> 1;
        if(L <= mid) update(ll, left, mid, L, R, val);
        if(mid < R) update(rr, mid + 1, right, L, R, val);
        update(x);
    }
}

int query(int x, int left, int right, int L, int R) {
    if(L <= left && right <= R) return mint[x];
    else {
        pushdown(x);
        int ll = x << 1, rr = ll ^ 1;
        int mid = (left + right) >> 1, ret = INF;
        if(L <= mid) update_min(ret, query(ll, left, mid, L, R));
        if(mid < R) update_min(ret, query(rr, mid + 1, right, L, R));
        return ret;
    }
}

int solve() {
    for(int i = 2; i <= n; ++i) {
        memset(tree, 0x3f, sizeof(tree));
        memset(mint, 0x3f, sizeof(mint));
        for(int j = 1; j <= m; ++j)
            update(1, 1, m, max(1, j - siz[i - 1][j]), min(m, j + siz[i - 1][j]), high[i - 1][j]);
        for(int j = 1; j <= m; ++j)
            high[i][j] += query(1, 1, m, max(1, j - siz[i][j]), min(m, j + siz[i][j]));
    }
    int ret = INF;
    for(int i = 1; i <= m; ++i) update_min(ret, high[n][i]);
    return ret;
}

int main () {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%d", &high[i][j]);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%d", &siz[i][j]);
        printf("%d\n", solve());
    }
}