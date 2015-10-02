#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXV = 200010;
const int INF = 0x3f3f3f3f;

struct LCT {
    struct Status {
        int lmax, rmax, sum, cover, res, size, val;
        void init(int v) {
            lmax = rmax = sum = res = val = v;
            cover = INF;
            size = 1;
        }
        void modify_cover(int v) {
            val = cover = v;
            sum = v * size;
            lmax = rmax = res = max(cover, sum);
        }
        Status operator + (const Status &rhs) const {
            Status ret;
            ret.lmax = max(lmax, sum + rhs.lmax);
            ret.rmax = max(rhs.rmax, rhs.sum + rmax);
            ret.sum = sum + rhs.sum;
            ret.cover = INF;
            ret.res = max(max(res, rhs.res), rmax + rhs.lmax);
            ret.size = size + rhs.size;
            return ret;
        }
    };
    struct Node {
        Status s;
        Node *fa, *ch[2];
        bool rev, rt;
    } statePool[MAXV], *nil;
    int ncnt;

    Node* new_node(int val, Node* f) {
        Node* x = statePool + ncnt++;
        x->s.init(val);
        x->fa = f;
        REP(k, 2) x->ch[k] = nil;
        x->rev = false;
        x->rt = true;
        return x;
    }

    void init() {
        nil = statePool;
        ncnt = 0;
        nil = new_node(-INF, nil);
        nil->s.size = 0;
    }

    void modify_rev(Node *x) {
        if(x == nil) return ;
        swap(x->s.lmax, x->s.rmax);
        swap(x->ch[0], x->ch[1]);
        x->rev = !x->rev;
    }

    void update(Node *x) {
        if(x == nil) return ;
        int t = x->s.val;
        x->s.init(t);
        if(x->ch[0] != nil) x->s = x->ch[0]->s + x->s;
        if(x->ch[1] != nil) x->s = x->s + x->ch[1]->s;
        x->s.val = t;
    }

    void pushdown(Node *x) {
        if(x->rev) {
            REP(k, 2) modify_rev(x->ch[k]);
            x->rev = false;
        }
        if(x->s.cover != INF) {
            REP(k, 2) x->ch[k]->s.modify_cover(x->s.cover);
            x->s.cover = INF;
        }
    }

    void rotate(Node *x) {
        Node *y = x->fa;
        int t = (y->ch[1] == x);

        if(y->rt) y->rt = false, x->rt = true;
        else y->fa->ch[y->fa->ch[1] == y] = x;
        x->fa = y->fa;

        (y->ch[t] = x->ch[t ^ 1])->fa = y;
        (x->ch[t ^ 1] = y)->fa = x;
        update(y);
    }

    void push(Node *x) {
        if(!x->rt) push(x->fa);
        pushdown(x);
    }

    void splay(Node *x) {
        push(x);
        while(!x->rt) {
            Node *f = x->fa, *ff = f->fa;
            if(!f->rt) rotate((ff->ch[1] == f) == (f->ch[1] == x) ? f : x);
            rotate(x);
        }
        update(x);
    }

    Node *access(Node *x) {
        Node *y = nil;
        while(x != nil) {
            splay(x);
            x->ch[1]->rt = true;
            (x->ch[1] = y)->rt = false;
            update(x);
            y = x; x = x->fa;
        }
        return y;
    }

    void be_root(Node *x) {
        access(x);
        splay(x);
        modify_rev(x);
    }

    int query(Node *x, Node *y) {
        be_root(x);
        return access(y)->s.res;
    }

    void modify(Node *x, Node *y, int val) {
        be_root(x);
        access(y)->s.modify_cover(val);
    }
} lct;

vector<int> adjs[MAXV];
LCT::Node* root[MAXV];
int w[MAXV];
int n, q;

void bfs_build() {
    root[1] = lct.new_node(w[1], lct.nil);
    queue<int> que; que.push(1);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        foreach(v, adjs[u]) if(!root[*v]) {
            root[*v] = lct.new_node(w[*v], root[u]);
            que.push(*v);
        }
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        adjs[u].push_back(v);
        adjs[v].push_back(u);
    }
    lct.init();
    bfs_build();
    for(int i = 0, op, a, b, c; i < q; ++i) {
        scanf("%d%d%d%d", &op, &a, &b, &c);
        if(op == 1) lct.modify(root[a], root[b], c);
        if(op == 2) printf("%d\n", lct.query(root[a], root[b]));
    }
}
