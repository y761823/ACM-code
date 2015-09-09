#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 100010;
const int INF = 0x3f3f3f3f;

struct Node {
    Node *ch[2], *fa;
    int u, minu;
    bool rev, rt;
    void update() {
        minu = u;
        REP(k, 2) minu = min(minu, ch[k]->minu);
    }
    void set_child(int k, Node *p) {
        ch[k] = p; p->fa = this;
    }
    void modify_rev() {
        rev = !rev;
        swap(ch[0], ch[1]);
    }
    void pushdown() {
        if(rev) REP(k, 2) ch[k]->modify_rev();
        rev = false;
    }
    void push() {
        if(!rt) fa->push();
        pushdown();
    }
} statePool[MAXV], *nil;
int ncnt;

int res[MAXV];
int n = 100000;

Node *new_node(int u, Node *f) {
    Node *x = statePool + ncnt++;
    x->ch[0] = x->ch[1] = nil;
    x->fa = f;
    x->minu = x->u = u;
    x->rev = false; x->rt = true;
    return x;
}

void rotate(Node *x) {
    Node *y = x->fa;
    int t = (y->ch[1] == x);
    
    if(y->rt) y->rt = false, x->rt = true;
    else y->fa->ch[y->fa->ch[1] == y] = x;
    x->fa = y->fa;
    
    y->set_child(t, x->ch[t ^ 1]);
    x->set_child(t ^ 1, y);
    y->update();
}

void splay(Node *x) {
    x->push();
    while(!x->rt) {
        Node *f = x->fa, *ff = f->fa;
        if(!f->rt) rotate((ff->ch[1] == f) == (f->ch[1] == x) ? f : x);
        rotate(x);
    }
    x->update();
}

Node *access(Node *x) {
    Node *y = nil;
    while(x != nil) {
        splay(x);
        x->ch[1]->rt = true;
        (x->ch[1] = y)->rt = false;
        x->update();
        y = x; x = x->fa;
    }
    return y;
}

void be_root(Node *x) {
    access(x);
    splay(x);
    x->modify_rev();
}

void link(Node *x, Node *y) {
    be_root(x);
    x->fa = y;
}

void cut(Node *x, Node *y) {
    be_root(x);
    splay(y);
    y->ch[0]->fa = y->fa;
    y->ch[0]->rt = true;
    y->fa = y->ch[0] = nil;
    y->update();
}

int query(Node *x, Node *y) {
    be_root(x);
    return access(y)->minu;
}

vector<int> fac[MAXV];

void init_factor() {
    for(int i = 2; i <= n; ++i)
        for(int j = i + i; j <= n; j += i) fac[j].push_back(i);
}

void init_tree() {
    nil = statePool;
    nil->u = nil->minu = INF;
    ncnt = 1;
    new_node(1, nil);
    for(int i = 2; i <= n; ++i)
        new_node(i, statePool + 1);
}

void solve() {
    res[1] = 0;
    for(int i = 2; i <= n; ++i) {
        res[i] = res[i - 1] + 1;
        for(int v : fac[i]) {
            int mn = query(statePool + i, statePool + v);
            if(mn >= v) continue;
            cut(statePool + i, statePool + mn); res[i] -= mn;
            link(statePool + i, statePool + v); res[i] += v;
        }
    }
}

int main() {
    init_factor();
    init_tree();
    solve();
    while(scanf("%d", &n) != EOF)
        printf("%d\n", res[n]);
}
