#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 5010;
const int MAXE = 20010;

int head[MAXN], sccno[MAXN];
int to[MAXE], next[MAXE];
bool vis[MAXE];
int pre[MAXN], lowlink[MAXN];
int stk[MAXN], top;
int dfs_clock, scc_cnt, ecnt, n, m;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 2;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    stk[top++] = u;
    for(int p = head[u]; p; p = next[p]) {
        if(vis[p]) continue;
        vis[p] = vis[p ^ 1] = true;
        int &v = to[p];
        if(!pre[v]) {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else lowlink[u] = min(lowlink[u], pre[v]);
    }
    if(lowlink[u] == pre[u]) {
        ++scc_cnt;
        while(true) {
            int x = stk[--top];
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

int deg[MAXN];

int solve() {
    for(int i = 1; i <= n; ++i)
        if(!pre[i]) dfs(i);
    int ret = 0;
    for(int u = 1; u <= n; ++u) {
        for(int p = head[u]; p; p = next[p]) {
            int &v = to[p];
            if(sccno[u] == sccno[v]) continue;
            ++deg[sccno[v]];
        }
    }
    for(int i = 1; i <= scc_cnt; ++i)
        ret += (deg[i] == 1);
    return (ret + 1) >> 1;
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    while(m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
    }
    printf("%d\n", solve());
}
