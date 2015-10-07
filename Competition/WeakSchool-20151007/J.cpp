#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <complex>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXV = 100010;
const int MAXE = 200010;
const int MAX_LOG = 20;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int newa, newb, newc;
int n, q, T;

void init_graph() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

int dep[MAXV], dis[MAXV];
int fa[MAXV][MAX_LOG];

void dfs(int u, int f, int depth, int leng) {
    fa[u][0] = f;
    dep[u] = depth;
    dis[u] = leng;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(v != f) dfs(v, u, depth + 1, leng + cost[p]);
    }
}

void init_tree() {
    dfs(1, -1, 0, 0);
    for(int k = 0; k < MAX_LOG - 1; ++k) {
        for(int u = 1; u <= n; ++u)
            if(fa[u][k] == -1) fa[u][k + 1] = -1;
            else fa[u][k + 1] = fa[fa[u][k]][k];
    }
}

int lca(int a, int b) {
    if(dep[a] > dep[b]) swap(a, b);
    for(int k = 0; k < MAX_LOG; ++k) {
        if(((dep[b] - dep[a]) >> k) & 1) b = fa[b][k];
    }
    if(a == b) return a;
    for(int k = MAX_LOG - 1; k >= 0; --k) {
        if(fa[a][k] != fa[b][k]) a = fa[a][k], b = fa[b][k];
    }
    return fa[a][0];
}

int get_dis(int a, int b) {
    int l = lca(a, b);
    return dis[a] + dis[b] - 2 * dis[l];
}

int solve(int a, int b) {
    int x = min(get_dis(a, newa) + get_dis(newb, b), get_dis(a, newb) + get_dis(newa, b)) + newc;
    return max(0, get_dis(a, b) - x);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &q);
        init_graph();
        for(int i = 1, u, v, c; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        scanf("%d%d%d", &newa, &newb, &newc);
        init_tree();

        printf("Case #%d:\n", t);
        for(int i = 0, u, v; i < q; ++i) {
            scanf("%d%d", &u, &v);
            printf("%d\n", solve(u, v));
        }
    }
}
