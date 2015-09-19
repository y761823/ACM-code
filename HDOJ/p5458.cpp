#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
using namespace std;
typedef long long LL;

const int MAXV = 30010;
const int MAXQ = 100010;
const int MAX_LOG = 16;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

struct Node {
    int to, del;
    Node(int to): to(to), del(0) {}
    bool operator < (const Node &rhs) const {
        if(to != rhs.to) return to < rhs.to;
        return del > rhs.del;
    }
};
vector<Node> adjs[MAXV];
int n, m, q, T;

void init() {
    for(int i = 1; i <= n; ++i) {
        adjs[i].clear();
    }
}

void add_edge(int u, int v) {
    adjs[u].push_back(Node(v));
    adjs[v].push_back(Node(u));
}

struct Query {
    int op, a, b, apos, bpos;
    void read() {
        scanf("%d%d%d", &op, &a, &b);
        if(op == 1) {
            lower_bound(adjs[a].begin(), adjs[a].end(), Node(b))->del = true;
            lower_bound(adjs[b].begin(), adjs[b].end(), Node(a))->del = true;
        }
    }
} query[MAXQ];
int ans[MAXQ], acnt;

struct BIT {
    int tree[MAXV];
    void init() {
        memset(tree + 1, 0, n * sizeof(int));
    }
    int lowbit(int x) {
        return x & -x;
    }
    void modify(int x, int val) {
        while(x <= n) {
            tree[x] += val;
            x += lowbit(x);
        }
    }
    void modify(int a, int b, int val) {
        modify(a, val);
        modify(b + 1, -val);
    }
    int get_val(int x) {
        int res = 0;
        while(x) {
            res += tree[x];
            x -= lowbit(x);
        }
        return res;
    }
} bitree;

int bid[MAXV], eid[MAXV], dep[MAXV];
int fa[MAX_LOG][MAXV];
int dfs_clock;

void dfs_id(int u, int f, int depth) {
    if(f > 0) adjs[u].erase(lower_bound(adjs[u].begin(), adjs[u].end(), Node(f)));
    fa[0][u] = f;
    dep[u] = depth;
    bid[u] = ++dfs_clock;
    for(Node& p : adjs[u]) if(!p.del && !bid[p.to]) {
        p.del = 1;
        dfs_id(p.to, u, depth + 1);
    }
    eid[u] = dfs_clock;
    bitree.modify(bid[u], eid[u], 1);
}
void bit_init() {
    memset(bid + 1, 0, n * sizeof(int));
    bitree.init();
    dfs_clock = 0;
    dfs_id(1, 0, 0);
}

struct LCA {
    void init_lca() {
        for(int k = 0; k + 1 < MAX_LOG; ++k) {
            for(int u = 1; u <= n; ++u) {
                if(fa[k][u] == -1) fa[k + 1][u] = -1;
                else fa[k + 1][u] = fa[k][fa[k][u]];
            }
        }
    }

    int ask(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);
        for(int k = 0; k < MAX_LOG; ++k) {
            if((dep[u] - dep[v]) & (1 << k)) u = fa[k][u];
        }
        if(u == v) return u;
        for(int k = MAX_LOG - 1; k >= 0; --k) {
            if(fa[k][u] != fa[k][v])
                u = fa[k][u], v = fa[k][v];
        }
        return fa[0][u];
    }
} lca;

int dsu[MAXV];

int find_set(int x) {
    return dsu[x] == x ? x : dsu[x] = find_set(dsu[x]);
}

void mergeFa(int u, int gold) {
    u = find_set(u);
    while(u != gold) {
        int t = find_set(fa[0][u]);
        dsu[u] = t;
        bitree.modify(bid[u], eid[u], -1);
        u = t;
    }
}

void merge(int u, int v) {
    int l = find_set(lca.ask(u, v));
    mergeFa(u, l);
    mergeFa(v, l);
}

void init_tree() {
    for(int i = 1; i <= n; ++i)
        dsu[i] = i;
    for(int u = 1; u <= n; ++u)
        for(Node p : adjs[u]) if(!p.del) {
            merge(u, p.to);
        }
}

void solve() {
    bit_init();
    lca.init_lca();
    init_tree();
    for(int i = q - 1; i >= 0; --i) {
        if(query[i].op == 1) {
            merge(query[i].a, query[i].b);
        } else {
            int l = lca.ask(query[i].a, query[i].b);
            ans[acnt++] = bitree.get_val(bid[query[i].a]) + bitree.get_val(bid[query[i].b]) - 2 * bitree.get_val(bid[l]);
        }
    }
    for(int i = acnt - 1; i >= 0; --i)
        printf("%d\n", ans[i]);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &q);
        init();
        for(int i = 0, u, v; i < m; ++i) {
            u = readint(), v = readint();
            add_edge(u, v);
        }
        for(int i = 1; i <= n; ++i)
            sort(adjs[i].begin(), adjs[i].end());

        acnt = 0;
        for(int i = 0; i < q; ++i)
            query[i].read();

        printf("Case #%d:\n", t);
        solve();
    }
}
