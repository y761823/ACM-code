////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-24 15:13:00
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4757
////Problem Title: 
////Run result: Accept
////Run time:1265MS
////Run memory:30152KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100010;
const int MAXN = 2 * MAX;
const int MAXE = 2 * MAXN;

int head[MAXN], weight[MAXN], fa[MAX];
bool vis[MAX];
int to[MAXE], next[MAXE], id[MAXE];
int n, m, ecnt;

inline void init() {
    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; ++i) fa[i] = i;
    ecnt = 2;
}

inline void add_edge(int u, int v, int i) {
    to[ecnt] = v; id[ecnt] = i; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; id[ecnt] = i; next[ecnt] = head[v]; head[v] = ecnt++;
}

struct QUERY {
    int x, y, lca, z;
    void read(int i) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x + n, y + n, i);
    }
} Query[MAX];

int get_set(int x) {
    return fa[x] == x ? x : fa[x] = get_set(fa[x]);
}

void dfs_LCA(int u, int f) {
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs_LCA(v, u);
        fa[v] = u;
    }
    vis[u] = true;
    for(int p = head[u + n]; p; p = next[p]) {
        int v = to[p] - n;
        if(vis[v]) Query[id[p]].lca = get_set(v);
    }
}

struct Node {
    int go[2], cnt;
} tree[20 * MAX];
int root[MAX], Tcnt;

void init_tree() {
    Tcnt = 1; root[0] = 0;
}

int insert(int x, int val) {
    tree[Tcnt] = tree[x];
    int ret = x = Tcnt++;
    for(int i = 15; i >= 0; --i) {
        int idx = (val >> i) & 1, t = Tcnt++;
        tree[t] = tree[tree[x].go[idx]];
        ++tree[t].cnt;
        tree[x].go[idx] = t;
        x = t;
    }
    return ret;
}

void dfs_build(int u, int f) {
    root[u] = insert(root[f], weight[u]);
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs_build(v, u);
    }
}

int query(int x, int y, int lca, int val) {
    int ret = 0, ret_lca = weight[lca] ^ val;
    x = root[x], y = root[y], lca = root[lca];
    for(int i = 15; i >= 0; --i) {
        int idx = !((val >> i) & 1);
        int cnt = tree[tree[x].go[idx]].cnt + tree[tree[y].go[idx]].cnt - 2 * tree[tree[lca].go[idx]].cnt;
        if(cnt > 0) ret |= (1 << i);
        else idx = !idx;
        x = tree[x].go[idx], y = tree[y].go[idx], lca = tree[lca].go[idx];
    }
    return max(ret, ret_lca);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i) scanf("%d", &weight[i]);
        init();
        for(int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v, 0);
        }
        for(int i = 1; i <= m; ++i) Query[i].read(i);
        dfs_LCA(1, 0);
        init_tree();
        dfs_build(1, 0);
        for(int i = 1; i <= m; ++i)
            printf("%d\n", query(Query[i].x, Query[i].y, Query[i].lca, Query[i].z));
    }
}
