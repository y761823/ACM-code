#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 100010;

struct SplayTree {//左右各有一个空结点
    struct Node {
        int size, c;
        Node *fa, *ch[2];
    };
    Node statePool[MAXN], *nil, *root;
    int ncnt;

    Node* new_node(int v, Node* f) {
        Node* t = statePool + ncnt++;
        t->size = 1;
        t->c = v;
        t->ch[0] = t->ch[1] = nil;
        t->fa = f;
        return t;
    }

    void init() {
        nil = statePool;
        ncnt = 1;
        root = new_node(0, nil);
        root->ch[1] = new_node(0, root);
        update(root);
    }

    void update(Node *x) {
        x->size = x->ch[0]->size + x->ch[1]->size + 1;
    }

    void rotate(Node* x) {
        Node* y = x->fa;
        int t = (y->ch[1] == x);
        y->fa->ch[y->fa->ch[1] == y] = x; x->fa = y->fa;
        y->ch[t] = x->ch[t ^ 1]; x->ch[t ^ 1]->fa = y;
        x->ch[t ^ 1] = y; y->fa = x;
        update(y);
    }

    void splay(Node* x, Node* f) {
        while(x->fa != f) {
            if(x->fa->fa == f) rotate(x);
            else {
                Node *y = x->fa, *z = y->fa;
                if((z->ch[1] == y) == (y->ch[1] == x)) rotate(y);
                else rotate(x);
                rotate(x);
            }
        }
        update(x);
        if(x->fa == nil) root = x;
    }

    Node* kth(int k) {
        Node* x = root;
        while(true) {
            int t = x->ch[0]->size + 1;
            if(t == k) break;
            if(t > k) x = x->ch[0];
            else x = x->ch[1], k -= t;
        }
        return x;
    }

    void insert(int pos, int c) {
        splay(kth(pos), nil);
        splay(kth(pos + 1), root);
        root->ch[1]->ch[0] = new_node(c, root->ch[1]);
        update(root->ch[1]); update(root);
    }

    void print(Node *x) {
        if(x != nil) {
            print(x->ch[0]);
            printf(" %d", x->c);
            print(x->ch[1]);
        }
    }
    void print(int l, int r) {
        splay(kth(l - 1), nil);
        splay(kth(r + 1), root);
        print(root->ch[1]->ch[0]);
    }
} splay;

struct People {
    int h, k;
    void read() {
        scanf("%d%d", &h, &k);
    }
    bool operator < (const People &rhs) const {
        return h > rhs.h;
    }
} p[MAXN];

int T, n;

bool solve() {
    splay.init();
    for(int i = 0; i < n; ++i) {
        if(p[i].k > i) return false;
        p[i].k = min(p[i].k, i - p[i].k);
        splay.insert(p[i].k + 1, p[i].h);
    }
    splay.print(2, n + 1);
    return true;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            p[i].read();
        sort(p, p + n);
        printf("Case #%d:", t);
        printf("%s\n", solve() ? "" : " impossible");
    }
}
