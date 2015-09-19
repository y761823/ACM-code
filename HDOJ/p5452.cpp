#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
using namespace std;
typedef long long LL;

const int MAXN = 20010;
const int MAX_LOG = 16;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

vector<int> adjt[MAXN], adjg[MAXN];
int cnt[MAXN], dep[MAXN];
int fa[MAX_LOG][MAXN];
int n, m, res, T;

int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

void init() {
    for(int i = 1; i <= n; ++i) {
        adjt[i].clear();
        adjg[i].clear();
    }
}

void add_edge(vector<int> adj[], int u, int v) {
    adj[v].push_back(u);
    adj[u].push_back(v);
}

void dfs_dep(int u, int f, int d) {
    dep[u] = d;
    fa[0][u] = f;
    for(int v : adjt[u]) if(v != f)
        dfs_dep(v, u, d + 1);
}

void init_lca() {
    dfs_dep(1, -1, 0);
    for(int k = 0; k + 1 < MAX_LOG; ++k) {
        for(int u = 1; u <= n; ++u) {
            if(fa[k][u] == -1) fa[k + 1][u] = -1;
            else fa[k + 1][u] = fa[k][fa[k][u]];
        }
    }
}

bool isfa(int f, int u) {
    if(dep[f] >= dep[u]) return false;
    for(int k = 0, t = dep[u] - dep[f]; k < MAX_LOG; ++k)
        if((t >> k) & 1) u = fa[k][u];
    return f == u;
}

void dfs_res(int u, int f) {
    cnt[u] = 0;
    for(int v : adjt[u]) if(v != f) {
        dfs_res(v, u);
        cnt[u] += cnt[v];
    }
    for(int v : adjg[u]) {
        if(isfa(u, v)) cnt[u]--;
        else cnt[u]++;
    }
    if(f > 0) res = min(res, cnt[u]);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1, u, v; i <= m; ++i) {
            u = readint(), v = readint();
            if(i < n) add_edge(adjt, u, v);
            else add_edge(adjg, u, v);
        }
        init_lca();
        res = INF;
        dfs_res(1, 0);
        printf("Case #%d: %d\n", t, res + 1);
    }
}
