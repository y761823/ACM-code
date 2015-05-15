#include <bits/stdc++.h>
using namespace std;

const int MAXV = 10010;
const int MAXE = 200010;

int head[MAXV], ecnt;
int from[MAXE], to[MAXE], nxt[MAXE];
int n, m;

int deg[MAXV], deg2[MAXV], fa[MAXV];
bool vis[MAXE];

int find_set(int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void __add_edge(int u, int v) {
    from[ecnt] = u; to[ecnt] = v;
    deg2[find_set(u)]++;
    nxt[ecnt] = head[find_set(u)]; head[find_set(u)] = ecnt++;
}

void add_edge(int u, int v) {
    __add_edge(u, v);
    __add_edge(v, u);
}

vector<int> path;

void dfs_path(int u) {
    for(int p = head[u]; ~p; p = nxt[p]) if(!vis[p >> 1]) {
        vis[p >> 1] = true;
        dfs_path(find_set(to[p]));
        path.push_back(to[p]);
        path.push_back(from[p]);
    }
}

int a[MAXE], b[MAXE];

bool solve() {
    for(int i = 1; i <= n; ++i)
        if(deg2[find_set(i)] & 1) return false;

    int st = 1;
    while(find_set(st) != st) ++st;
    dfs_path(st);
    path.erase(unique(path.begin(), path.end()), path.end());
    if(path.front() == path.back()) path.pop_back();

    for(size_t i = 0; i < path.size(); ++i)
        printf("%d ", path[i]);
    puts("");
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) fa[i] = i;
    for(int i = 0; i < m; ++i) {
        scanf("%d%d", &a[i], &b[i]);
        deg[a[i]]++, deg[b[i]]++;
    }

    for(int i = 0; i < m; ++i) {
        if(deg[a[i]] > 2 && deg[b[i]] > 2 && find_set(a[i]) != find_set(b[i]))
            fa[find_set(a[i])] = find_set(b[i]);
    }

    init();
    for(int i = 0; i < m; ++i) {
        if(find_set(a[i]) != find_set(b[i]))
            add_edge(a[i], b[i]);
    }

    if(!solve()) puts("-1");
}
