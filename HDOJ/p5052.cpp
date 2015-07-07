////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-27 23:27:48
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5052
////Problem Title: 
////Run result: Accept
////Run time:3140MS
////Run memory:5184KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 50010;
const int MAXE = MAXV << 1;
const int INF = 0x3f3f3f3f;
const int NINF = -INF;

struct LCT {
    struct Node {
        Node *ch[2], *fa;
        int add, val;
        int lans, rans, maxt, mint;
        bool rt, rev;
        Node() {}
        Node(int v) {
            lans = rans = 0;
            val = maxt = mint = v;
        }
    } statePool[MAXV], *nil;
    int ncnt;

    int head[MAXV], val[MAXV], ecnt;
    int to[MAXE], next[MAXE];
    int n, m, T;
    Node *ptr[MAXV];

    LCT() {
        ptr[0] = nil = statePool;
        nil->maxt = -INF;
        nil->mint = INF;
        nil->lans = nil->rans = 0;
    }

    void init() {
        memset(head + 1, -1, n * sizeof(int));
        ncnt = 1;
        ecnt = 0;
    }

    void add_edge(int u, int v) {
        to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    Node* new_node(int val, Node *f) {
        Node* x = &statePool[ncnt++];
        x->ch[0] = x->ch[1] = nil; x->fa = f;
        x->maxt = x->mint = x->val = val;
        x->lans = x->rans = 0;
        x->rt = true; x->rev = false;
        return x;
    }

    void dfs(int u, int f) {
        ptr[u] = new_node(val[u], ptr[f]);
        for(int p = head[u]; ~p; p = next[p]) {
            int v = to[p];
            if(v == f) continue;
            dfs(v, u);
        }
    }

    void add(Node *a, Node x, Node y) {
        a->lans = max(max(x.lans, y.lans), y.maxt - x.mint);
        a->rans = max(max(x.rans, y.rans), x.maxt - y.mint);
        a->maxt = max(x.maxt, y.maxt);
        a->mint = min(x.mint, y.mint);
    }

    void update(Node *x) {
        add(x, *x->ch[0], Node(x->val));
        add(x, *x, *x->ch[1]);
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

    void update_add(Node *x, int val) {
        if(x == nil) return ;
        x->add += val;
        x->val += val;
        x->maxt += val;
        x->mint += val;
    }

    void update_rev(Node *x) {
        if(x == nil) return ;
        x->rev = !x->rev;
        swap(x->ch[0], x->ch[1]);
        swap(x->lans, x->rans);
    }

    void pushdown(Node *x) {
        if(x->add != 0) {
            FOR(k, 2) update_add(x->ch[k], x->add);
            x->add = 0;
        }
        if(x->rev) {
            FOR(k, 2) update_rev(x->ch[k]);
            x->rev = false;
        }
    }

    void push(Node *x) {
        if(!x->rt) push(x->fa);
        pushdown(x);
    }

    void splay(Node *x) {
        push(x);
        while(!x->rt) {
            Node *f = x->fa, *ff = f->fa;
            if(!f->rt) rotate(((ff->ch[1] == f) && (f->ch[1] == x)) ? f : x);
            rotate(x);
        }
        update(x);
    }

    Node* access(Node *x) {
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
        update_rev(x);
    }

    int query(Node *x, Node *y, int z) {
        be_root(x);
        Node *r = access(y);
        update_add(r, z);
        return r->lans;
    }

    void work() {
        scanf("%d", &T);
        for(int t = 1; t <= T; ++t) {
            scanf("%d", &n);
            init();
            for(int i = 1; i <= n; ++i) scanf("%d", &val[i]);
            for(int i = 1, u, v; i < n; ++i) {
                scanf("%d%d", &u, &v);
                add_edge(u, v);
            }
            dfs(1, 0);

            scanf("%d", &m);
            for(int i = 0, x, y, z; i < m; ++i) {
                scanf("%d%d%d", &x, &y, &z);
                printf("%d\n", query(ptr[x], ptr[y], z));
            }
        }
    }
} S;

int main() {
    S.work();
}