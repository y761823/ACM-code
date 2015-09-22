#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define sqr(x) ((x) * (x))

const int MAXN = 100010;
const int MAXT = MAXN * 80;

struct Node {
    Node *ls, *rs;
    int maxv;
} statePool[MAXT], *nil;
int ncnt;

Node *new_node(int val = 0) {
    Node *x = statePool + ncnt++;
    x->ls = x->rs = nil;
    x->maxv = val;
    return x;
}

Node *new_node(Node *src) {
    Node *x = statePool + ncnt++;
    *x = *src;
    return x;
}

void init_tree() {
    nil = statePool;
    ncnt = 0;
    nil = new_node();
}

Node* insert(Node *src, int l, int r, int a, int b, int val) {
    Node *x = new_node(src);
    if(a <= l && r <= b) {
        x->maxv = max(x->maxv, val);
    } else {
        int mid = (l + r) >> 1;
        if(a <= mid) x->ls = insert(x->ls, l, mid, a, b, val);
        if(mid < b) x->rs = insert(x->rs, mid + 1, r, a, b, val);
    }
    return x;
}

int query(Node *x, int l, int r, int pos) {
    if(l == r) {
        return x->maxv;
    } else {
        int mid = (l + r) >> 1;
        if(pos <= mid) return max(x->maxv, query(x->ls, l, mid, pos));
        else return max(x->maxv, query(x->rs, mid + 1, r, pos));
    }
}

vector<int> ason[MAXN], bson[MAXN];
Node *root[MAXN];
int bid[MAXN], eid[MAXN], dfs_clock;
int depa[MAXN], depb[MAXN];
int n, m;

void init() {
    for(int i = 1; i <= n; ++i) {
        ason[i].clear();
        bson[i].clear();
    }
}

void dfsa(int u, int depth) {
    depa[u] = depth;
    bid[u] = ++dfs_clock;
    for(int v : ason[u])
        dfsa(v, depth + 1);
    eid[u] = dfs_clock;
}
void dfsa() {
    dfs_clock = 0;
    dfsa(1, 0);
}

void dfsb(int u, int f, int depth) {
    depb[u] = depth;
    root[u] = insert(root[f], 1, n, bid[u], eid[u], u);
    for(int v : bson[u])
        dfsb(v, u, depth + 1);
}
void dfsb() {
    init_tree();
    root[0] = nil;
    dfsb(1, 0, 0);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 2, x; i <= n; ++i) {
            scanf("%d", &x);
            ason[x].push_back(i);
        }
        for(int i = 2, x; i <= n; ++i) {
            scanf("%d", &x);
            bson[x].push_back(i);
        }
        dfsa();
        dfsb();
        for(int i = 0, k = 0, x, y; i < m; ++i) {
            scanf("%d%d", &x, &y);
            x = (x + k) % n + 1;
            y = (y + k) % n + 1;
            k = query(root[y], 1, n, bid[x]);
            printf("%d %d %d\n", k, depa[x] - depa[k] + 1, depb[y] - depb[k] + 1);
        }
    }
}
