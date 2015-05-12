#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXE = MAXV * 2;

int head[MAXV], val[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
int n, D, T, res;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    res = ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

int size[MAXV], maxBranch[MAXV];
bool del[MAXV];
vector<int> nodes;

void dfs_size(int u, int f) {
    size[u] = 1;
    maxBranch[u] = 0;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(del[v] || v == f) continue;
        dfs_size(v, u);
        size[u] += size[v];
        maxBranch[u] = max(maxBranch[u], size[v]);
    }
    nodes.push_back(u);
}
int get_root(int u) {
    nodes.clear();
    dfs_size(u, -1);
    int rt = u;
    for(int v : nodes) {
        maxBranch[v] = max(maxBranch[v], size[u] - size[v]);
        if(maxBranch[v] < maxBranch[rt]) rt = v;
    }
    return rt;
}

map<int, int> up;

void insert(int val, int len) {
    auto x = up.lower_bound(val);
    if(x != up.end() && x->second >= len) return ;

    auto ed = up.upper_bound(val);
    //printf("#debug %d %d\n", ed->first, ed->second);
    auto it = map<int, int>::reverse_iterator(ed);
    while(it != up.rend() && it->second <= len) ++it;
    up.erase(it.base(), ed);
    up[val] = len;
}

void dfs_up(int u, int f, int dep) {
    insert(val[u], dep);
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(!del[v] && v != f && val[v] <= val[u])
            dfs_up(v, u, dep + 1);
    }
}

void dfs_down(int u, int f, int dep) {
    auto it = up.lower_bound(val[u] - D);
    if(it != up.end()) res = max(res, it->second + dep + 1);
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(!del[v] && v != f && val[v] >= val[u])
            dfs_down(v, u, dep + 1);
    }
}

void _work(int u, vector<int> &son) {
    up.clear();
    up[val[u]] = 0;
    for(int v : son) {
        if(val[v] >= val[u]) dfs_down(v, u, 1);
        if(val[v] <= val[u]) dfs_up(v, u, 1);
    }
}
void work(int rt) {
    vector<int> son;
    for(int p = head[rt]; ~p; p = nxt[p])
        if(!del[to[p]]) son.push_back(to[p]);

    _work(rt, son);
    reverse(son.begin(), son.end());
    _work(rt, son);
}

void solve(int st) {
    int u = get_root(st);
    work(u);

    del[u] = true;
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(!del[v]) solve(v);
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &D);
        init();
        for(int i = 1; i <= n; ++i) scanf("%d", &val[i]);
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }

        memset(del + 1, 0, n * sizeof(bool));
        solve(1);
        printf("Case #%d: %d\n", t, res);
    }
}
