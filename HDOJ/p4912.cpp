////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-02 23:08:54
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4912
////Problem Title: 
////Run result: Accept
////Run time:453MS
////Run memory:11040KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int MAXV = 100010;
const int MAXE = MAXV << 1;

bool vis[MAXV];
int head[MAXV], fa[MAXV], dep[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m;

struct Path {
    int u, v, lca, dep;
    void read() {
        scanf("%d%d", &u, &v);
    }
    bool operator < (const Path &rhs) const {
        return dep > rhs.dep;
    }
} path[MAXV];
vector<PII> link[MAXV];

void init() {
    for(int i = 1; i <= n; ++i) fa[i] = i;
    for(int i = 1; i <= n; ++i) link[i].clear();
    memset(vis + 1, -1, n * sizeof(bool));
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int get_set(int x) {
    return fa[x] == x ? x : fa[x] = get_set(fa[x]);
}

void tarjan(int u, int f, int depth) {
    dep[u] = depth;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        tarjan(v, u, depth + 1);
        fa[v] = u;
    }
    vis[u] = true;
    for(size_t i = 0; i < link[u].size(); ++i) {
        int v = link[u][i].first;
        if(vis[v]) path[link[u][i].second].lca = get_set(v);
    }
}

void set_vis(int u) {
    if(vis[u]) return;
    vis[u] = true;
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(dep[v] > dep[u]) set_vis(v);
    }
}

int solve() {
    tarjan(1, 0, 0);
    for(int i = 0; i < m; ++i) path[i].dep = dep[path[i].lca];
    sort(path, path + m);
    memset(vis + 1, 0, n * sizeof(bool));
    int res = 0;
    for(int i = 0; i < m; ++i) {
        if(vis[path[i].u] || vis[path[i].v]) continue;
        res++;
        set_vis(path[i].lca);
    }
    return res;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        for(int i = 0; i < m; ++i) {
            path[i].read();
            link[path[i].u].push_back(make_pair(path[i].v, i));
            link[path[i].v].push_back(make_pair(path[i].u, i));
        }
        printf("%d\n", solve());
    }
}
