#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n + 2; ++i)

const int MAXV = 100010;
const int MAXE = 200010;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
bool iscut[MAXE];
int n, m, T;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; iscut[ecnt] = false; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; iscut[ecnt] = false; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

int pre[MAXV], lowlink[MAXV], maxs[MAXV];
int dfs_clock;

void dfs(int u, int f) {
    pre[u] = lowlink[u] = ++dfs_clock;
    maxs[u] = u;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(!pre[v]) {
            dfs(v, p);
            lowlink[u] = min(lowlink[u], lowlink[v]);
            maxs[u] = max(maxs[u], maxs[v]);
        } else if((p ^ 1) != f) {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if(f >= 0 && lowlink[u] == pre[u]) iscut[f] = true;
}

void solve() {
    memset(pre + 1, 0, n * sizeof(int));
    dfs_clock = 0;
    dfs(n, -1);
    for(int i = 0; i < m; ++i) {
        if(iscut[i << 1] || iscut[(i << 1) | 1]) {
            int u = to[(i << 1) | !iscut[i << 1]];
            printf("%d %d\n", maxs[u], maxs[u] + 1);
        } else {
            puts("0 0");
        }
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        solve();
    }
}
