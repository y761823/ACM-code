////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-22 00:07:59
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5029
////Problem Title: 
////Run result: Accept
////Run time:3046MS
////Run memory:58640KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> PII;

const int MAXV = 100010;
const int MAXE = MAXV << 1;
const int MAXT = MAXV << 2;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m, maxz;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

#define mid ((l + r) >> 1)
struct Node {
    Node *lson, *rson;
    int val, cnt, size;
    Node() {
        val = cnt = size = 0;
    }
    void update() {
        Node *s = lson->cnt >= rson->cnt ? lson : rson;
        val = s->val;
        cnt = s->cnt;
        size = lson->size + rson->size;
    }
} *nil;
Node statePool[MAXT * 3];
Node *stk[MAXT * 3];
int top, scnt;

Node* new_node() {
    Node *p;
    if(top) p = stk[--top];
    else p = &statePool[scnt++];
    p->lson = p->rson = nil;
    p->val = p->cnt = p->size = 0;
    return p;
}

void del_node(Node *p) {
    stk[top++] = p;
}

void remove(Node *y) {
    if(y->lson != nil) remove(y->lson);
    if(y->rson != nil) remove(y->rson);
    del_node(y);
}

void modify(Node *&x, int l, int r, int pos, int val) {
    if(x == nil) x = new_node();
    if(l == r) {
        x->val = l;
        x->cnt += val;
        x->size = (x->cnt > 0);
    } else {
        if(pos <= mid) modify(x->lson, l, mid, pos, val);
        if(mid < pos) modify(x->rson, mid + 1, r, pos, val);
        x->update();
    }
}

void merge(Node *x, Node *y, int l, int r) {
    if(y->size != 0) {
        if(l == r) {
            modify(x, 1, maxz, l, y->cnt);
        } else {
            merge(x, y->lson, l, mid);
            merge(x, y->rson, mid + 1, r);
        }
    }
}

Node* merge(Node *x, Node *y) {
    if(x->size < y->size) swap(x, y);
    merge(x, y, 1, maxz);
    remove(y);
    return x;
}

vector<PII> query[MAXV];
struct Modify {
    int u, v, c, lca;
    void read(int i) {
        scanf("%d%d%d", &u, &v, &c);
        maxz = max(maxz, c);
        query[u].push_back(make_pair(v, i));
        query[v].push_back(make_pair(u, i));
    }
} ask[MAXV];
int fa[MAXV];
bool vis[MAXV];

int find_set(int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void lca(int u, int f) {
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f || vis[v]) continue;
        lca(v, u);
        fa[v] = u;
    }
    vis[u] = true;
    for(vector<PII>::iterator it = query[u].begin(); it != query[u].end(); ++it) {
        if(vis[it->first]) {
            ask[it->second].lca = find_set(it->first);
        }
    }
}

vector<PII> pre[MAXV], nxt[MAXV];
int ans[MAXV];

Node* dfs(int u, int f) {
    Node *x = new_node();
    for(int p = head[u]; ~p; p = next[p]) {
        int v = to[p];
        if(v == f) continue;
        x = merge(x, dfs(v, u));
    }
    for(vector<PII>::iterator it = pre[u].begin(); it != pre[u].end(); ++it)
        modify(x, 1, maxz, it->first, it->second);
    ans[u] = x->val;
    for(vector<PII>::iterator it = nxt[u].begin(); it != nxt[u].end(); ++it)
        modify(x, 1, maxz, it->first, it->second);
    return x;
}

void solve() {
    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
        vis[i] = false;
        pre[i].clear(); nxt[i].clear();
    }
    lca(1, 0);
    for(int i = 0; i < m; ++i) {
        const Modify &t = ask[i];
        pre[t.u].push_back(make_pair(t.c, 1));
        pre[t.v].push_back(make_pair(t.c, 1));
        pre[t.lca].push_back(make_pair(t.c, -1));
        nxt[t.lca].push_back(make_pair(t.c, -1));
    }
    top = scnt = 0;
    Node *p = dfs(1, 0);
    if(p != nil) remove(p);

    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
}

int main() {
    nil = new Node();
    nil->lson = nil->rson = nil;

    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        init();
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        for(int i = 1; i <= n; ++i) query[i].clear();
        maxz = 0;
        for(int i = 0; i < m; ++i) ask[i].read(i);
        solve();
    }
}
