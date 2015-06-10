#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXV = 50010;
const int MAXE = MAXV << 1;

int head[MAXV], val[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int fa[20][MAXV], dep[MAXV];

void dfs(int u, int depth) {
    dep[u] = depth + 1;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == fa[0][u]) continue;
        fa[0][v] = u;
        dfs(v, depth + 1);
    }
}

int maxp[20][MAXV], minp[20][MAXV];
int upans[20][MAXV], downans[20][MAXV];

void init2() {
    fa[0][1] = -1;
    dfs(1, 0);
    for(int i = 1; i <= n; ++i) {
        maxp[0][i] = val[fa[0][i]];
        minp[0][i] = val[fa[0][i]];
        upans[0][i] = 0;
        downans[0][i] = 0;
    }
    for(int k = 0; k < 19; ++k) {
        for(int u = 1; u <= n; ++u) {
            if(fa[k][u] < 0) fa[k + 1][u] = -1;
            else {
                int f = fa[k][u];
                fa[k + 1][u] = fa[k][f];
                maxp[k + 1][u] = max(maxp[k][u], maxp[k][f]);
                minp[k + 1][u] = min(minp[k][u], minp[k][f]);
                upans[k + 1][u] = max(max(upans[k][u], upans[k][f]), maxp[k][f] - minp[k][u]);
                downans[k + 1][u] = max(max(downans[k][u], downans[k][f]), maxp[k][u] - minp[k][f]);
            }
        }
    }
}

int mint, maxt, ans;

void updatet(int &t, int k) {
    ans = max(ans, max(downans[k][t], maxt - minp[k][t]));
    maxt = max(maxt, maxp[k][t]);
    t = fa[k][t];
}

void updates(int &s, int k) {
    ans = max(ans, max(upans[k][s], maxp[k][s] - mint));
    mint = min(mint, minp[k][s]);
    s = fa[k][s];
}

int solve(int s, int t) {
    mint = val[s], maxt = val[t], ans = 0;
    if(dep[s] < dep[t]) {
        for(int k = 0; k < 20; ++k) {
            if((dep[t] - dep[s]) >> k & 1) updatet(t, k);
        }
    }
    if(dep[s] > dep[t]) {
        for(int k = 0; k < 20; ++k) {
            if((dep[s] - dep[t]) >> k & 1) updates(s, k);
        }
    }
    if(s != t) {
        for(int k = 19; k >= 0; --k) {
            if(fa[k][s] != fa[k][t]) {
                updatet(t, k);
                updates(s, k);
            }
        }
        updatet(t, 0);
        updates(s, 0);
    }
    return max(ans, maxt - mint);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &val[i]);
    init();
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    init2();
    scanf("%d", &m);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", solve(u, v));
    }
}