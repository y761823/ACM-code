////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-22 23:48:05
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5039
////Problem Title: 
////Run result: Accept
////Run time:2171MS
////Run memory:5116KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int, int> PII;

const int MAXV = 30010;
const int MAXE = MAXV << 1;
const int MAXT = MAXV << 2;

int flip[MAXT], sum[MAXT];
int n, m, T;

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
void update(int x) {
    sum[x] = sum[ll] + sum[rr];
}

void update_flip(int x, int l, int r) {
    sum[x] = (r - l + 1) - sum[x];
    flip[x] ^= 1;
}

void pushdown(int x, int l, int r) {
    if(flip[x]) {
        update_flip(ll, l, mid);
        update_flip(rr, mid + 1, r);
        flip[x] = 0;
    }
}

void modify(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        update_flip(x, l, r);
    } else {
        pushdown(x, l, r);
        if(a <= mid) modify(ll, l, mid, a, b);
        if(mid < b) modify(rr, mid + 1, r, a, b);
        update(x);
    }
}

int query() {
    return 2 * sum[1] * (n - sum[1]);
}

int head[MAXV], ecnt, dfs_clock;
int to[MAXE], next[MAXE], val[MAXE];
int bid[MAXV], eid[MAXV], son[MAXV];

void add_edge(int u, int v, int c) {
    to[ecnt] = v; val[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; val[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u, int f) {
    bid[u] = ++dfs_clock;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        son[p >> 1] = v;
        dfs(v, u);
    }
    eid[u] = dfs_clock;
}

map<string, int> mymap;

void init() {
    memset(flip + 1, 0, (n << 2) * sizeof(int));
    memset(sum + 1, 0, (n << 2) * sizeof(int));

    memset(head + 1, -1, n * sizeof(int));
    ecnt = dfs_clock = 0;

    mymap.clear();
}

void solve() {
    dfs(1, 0);
    for(int i = 1; i < n; ++i) if(val[(i - 1) << 1]) {
        int t = son[i - 1];
        modify(1, 1, n, bid[t], eid[t]);
    }
    int q, v; char c;
    scanf("%d", &q);
    while(q--) {
        scanf(" %c", &c);
        if(c == 'M') {
            scanf("%d", &v);
            v = son[v - 1];
            modify(1, 1, n, bid[v], eid[v]);
        } else {
            printf("%d\n", query());
        }
    }
}

char s1[15], s2[15];

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        init();
        for(int i = 1; i <= n; ++i) {
            scanf("%s", s1);
            mymap[s1] = i;
        }
        for(int i = 1, c; i < n; ++i) {
            scanf("%s%s%d", s1, s2, &c);
            add_edge(mymap[s1], mymap[s2], c);
        }
        printf("Case #%d:\n", t);
        solve();
    }
}
