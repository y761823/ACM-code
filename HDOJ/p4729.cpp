////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-27 14:02:16
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4729
////Problem Title: 
////Run result: Accept
////Run time:703MS
////Run memory:32704KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXC = 10000;
const int MAXN = 100010;
const int MAXV = 2 * 100010;
const int MAXE = 2 * 200010;

int head[MAXV], fa[MAXV];
bool vis[MAXV];
int to[MAXE], next[MAXE], weight[MAXE];
int T, n, m, ecnt;

void init() {
    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; ++i) fa[i] = i;
    ecnt = 2;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; weight[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; weight[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

struct QUERY {
    int s, t, k, a, b, lca;
    void read(int i) {
        scanf("%d%d%d%d%d", &s, &t, &k, &a, &b);
        add_edge(s + n, t + n, i);
    }
} Query[MAXV];

int get_set(int x) {
    return fa[x] == x ? x : fa[x] = get_set(fa[x]);
}

void dfs_lca(int u, int f) {
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs_lca(v, u);
        fa[v] = u;
    }
    vis[u] = true;
    for(int p = head[u + n]; p; p = next[p]) {
        int v = to[p] - n;
        if(vis[v]) Query[weight[p]].lca = get_set(v);
    }
}

struct Node {
    int L, R, sum, cnt;
} tree[20 * MAXN];
int root[MAXV], Tcnt;

void init_Tree() {
    root[1] = 0;
    Tcnt = 1;
}

void insert(int &x, int left, int right, int &val) {
    tree[Tcnt] = tree[x]; x = Tcnt++;
    ++tree[x].cnt; tree[x].sum += val;
    if(left == right) return ;
    int mid = (left + right) >> 1;
    if(val <= mid) insert(tree[x].L, left, mid, val);
    else insert(tree[x].R, mid + 1, right, val);
}

void dfs_build_tree(int u, int f, int w) {
    root[u] = root[f];
    if(f) insert(root[u], 0, MAXC, w);
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        dfs_build_tree(v, u, weight[p]);
    }
}

int query(int x, int y, int lca, int left, int right, int k) {
    if(left == right) return left;
    int t = tree[tree[x].L].cnt + tree[tree[y].L].cnt - 2 * tree[tree[lca].L].cnt;
    int mid = (left + right) >> 1;
    if(k <= t) return query(tree[x].L, tree[y].L, tree[lca].L, left, mid, k);
    else return query(tree[x].R, tree[y].R, tree[lca].R, mid + 1, right, k - t);
}

int query(int x, int y, int lca, int cap) {
    int l = 0, r = MAXC, cnt = 0, sum = 0;
    while(l < r) {
        int mid = (l + r) >> 1;
        int tmp_cnt = tree[tree[x].L].cnt + tree[tree[y].L].cnt - 2 * tree[tree[lca].L].cnt;
        int tmp_sum = tree[tree[x].L].sum + tree[tree[y].L].sum - 2 * tree[tree[lca].L].sum;
        if((cnt + tmp_cnt) * mid - (sum + tmp_sum) > cap)
            x = tree[x].L, y = tree[y].L, lca = tree[lca].L, r = mid;
        else x = tree[x].R, y = tree[y].R, lca = tree[lca].R, l = mid + 1, cnt += tmp_cnt, sum += tmp_sum;
    }
    return l - 1;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1; i < n; ++i) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        for(int i = 1; i <= m; ++i) Query[i].read(i);
        printf("Case #%d:\n", t);
        dfs_lca(1, 0);
        //for(int i = 1; i <= m; ++i) printf("%d\n", Query[i].lca);
        init_Tree();
        dfs_build_tree(1, 0, 0);
        //for(int i = 1; i <= m; ++i) printf("%d\n", query(root[Query[i].s], root[Query[i].t], root[Query[i].lca], 0, MAXC, 1));
        for(int i = 1; i <= m; ++i) {
            int ans = query(root[Query[i].s], root[Query[i].t], root[Query[i].lca], 0, MAXC, 1);
            if(Query[i].a < Query[i].b) ans += Query[i].k / Query[i].a;
            else {
                if(Query[i].k >= Query[i].a) ans += (Query[i].k - Query[i].a) / Query[i].b + 1;
                ans = max(ans, query(root[Query[i].s], root[Query[i].t], root[Query[i].lca], Query[i].k / Query[i].b));
            }
            printf("%d\n", ans);
        }
    }
}