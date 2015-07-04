//C++ 2469MS, G++ TLE
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 200010;
const int INF = 0x3f3f3f3f;

struct Node {
    Node *ch[2];
    int size, key, val;
    Node() {
        key = rand();
    }
    void update() {
        size = ch[0]->size + ch[1]->size + 1;
    }
} statePool[MAXN], *nil, *root;
int ncnt;

void init() {
    root = nil = statePool;
    nil->ch[0] = nil->ch[1] = nil;
    nil->size = 0;
    ncnt = 1;
}

Node* newnode(int val) {
    Node *x = statePool + ncnt++;
    //x->key = rand();
    x->size = 1;
    x->val = val;
    x->ch[0] = x->ch[1] = nil;
    return x;
}

void rotate(Node *&x, int t) {
    Node *y = x->ch[t];
    x->ch[t] = y->ch[t ^ 1];
    y->ch[t ^ 1] = x;
    x->update();
    x = y;
}

void insert(Node *&x, int k, int val) {
    if(x != nil) {
        int t = (x->ch[0]->size + 1 <= k);
        insert(x->ch[t], k - t * (x->ch[0]->size + 1), val);
        if(x->ch[t]->key > x->key) rotate(x, t);
        x->update();
    } else x = newnode(val);
}

bool first;
void print(Node *x) {
    if(x != nil) {
        print(x->ch[0]);
        if(!first) printf(" ");
        printf("%d", x->val);
        first = false;
        print(x->ch[1]);
    }
}

int main() {
    int n, p, v;
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &p, &v);
            insert(root, p, v);
        }
        first = true;
        print(root);
        puts("");
    }
}
