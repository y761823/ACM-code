#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXW = 31;
const int INF = 0x3f3f3f3f;

int head[MAXV], val[MAXV], ecnt;
int to[MAXV], nxt[MAXV];
int n, m, T;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
}

int bid[MAXV], eid[MAXV];
int dfs_clock;

void dfs(int u) {
    bid[u] = ++dfs_clock;
    for(int p = head[u]; ~p; p = nxt[p])
        dfs(to[p]);
    eid[u] = dfs_clock;
}

void dfs() {
    dfs_clock = 0;
    dfs(1);
}

struct Node {
    Node *go[2];
    int cnt;
} statePool[MAXV * 65], *rt;
int ncnt;

Node *new_node() {
    return statePool + ncnt++;
}

void init_trie() {
    memset(statePool, 0, ncnt * sizeof(Node));
    ncnt = 0;
    rt = new_node();
}

void insert(int val, int offset) {
    Node *p = rt;
    for(int i = 30; i >= 0; --i) {
        int idx = (val >> i) & 1;
        if(!p->go[idx]) p->go[idx] = new_node();
        p = p->go[idx];
        p->cnt += offset;
    }
}

int getmax(int val) {
    Node *p = rt;
    int res = 0;
    for(int i = 30; i >= 0; --i) {
        int idx = ((val >> i) & 1) ^ 1;
        if(p->go[idx] && p->go[idx]->cnt) {
            res |= (1 << i);
            p = p->go[idx];
        } else {
            p = p->go[idx ^ 1];
        }
    }
    return res;
}

struct Query {
    int type, u, v, prev;
    void read(int i) {
        scanf("%d%d", &type, &u);
        if(type == 0) {
            scanf("%d", &v);
            prev = val[u]; val[u] = v;
        } else {
            v = i;
            prev = val[u];
        }
    }
} query[MAXV];
int ans[MAXV];

vector<Query> opera[MAXV << 1];

int root(int l, int r) { return (l + r) | (l != r); }
#define x root(l, r)
#define mid ((l + r) >> 1)
#define ll root(l, mid)
#define rr root(mid + 1, r)
void build(int l, int r) {
    opera[x].clear();
    if(l != r && l <= mid) build(l, mid);
    if(l != r && mid < r) build(mid + 1, r);
}

void insert(int l, int r, int a, int b, const Query& op) {
    if(op.type == 1) opera[x].push_back(op);
    if(a <= l && r <= b) {
        if(op.type == 0) opera[x].push_back(op);
    } else {
        if(a <= mid) insert(l, mid, a, b, op);
        if(mid < b) insert(mid + 1, r, a, b, op);
    }
}

void solve(int l, int r) {
    init_trie();
    for(Query op : opera[x]) {
        if(op.type == 0) {
            if(~op.prev) insert(op.prev, -1);
            insert(op.v, 1);
        } else {
            if(ncnt > 1) ans[op.v] = max(ans[op.v], getmax(op.prev));
        }
    }
    if(l != r && l <= mid) solve(l, mid);
    if(l != r && mid < r) solve(mid + 1, r);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int u = 2, f; u <= n; ++u) {
            scanf("%d", &f);
            add_edge(f, u);
        }
        build(1, n);
        dfs();
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &val[i]);
            insert(1, n, bid[i], eid[i], {0, i, val[i], -1});
        }
        memset(ans, -1, m * sizeof(int));
        for(int i = 0; i < m; ++i) {
            query[i].read(i);
            if(query[i].type == 0) insert(1, n, bid[query[i].u], eid[query[i].u], query[i]);
            else insert(1, n, bid[query[i].u], bid[query[i].u], query[i]);
        }
        solve(1, n);
        for(int i = 0; i < m; ++i)
            if(~ans[i]) printf("%d\n", ans[i]);
    }
}
