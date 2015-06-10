#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int key[MAXN], weight[MAXN], child[MAXN][2], size[MAXN];
int stk[MAXN], top, cnt;

inline void init() {
    top = cnt = 0;
}

inline int new_node(int k) {
    int x = (top ? stk[top--] : ++cnt);
    key[x] = k;
    size[x] = 1;
    weight[x] = rand();
    child[x][0] = child[x][1] = 0;
    return x;
}

inline void update(int &x) {
    size[x] = size[child[x][0]] + size[child[x][1]] + 1;
}

void rotate(int &x, int t) {
    int y = child[x][t];
    child[x][t] = child[y][t ^ 1];
    child[y][t ^ 1] = x;
    update(x); update(y);
    x = y;
}

void insert(int &x, int k) {
    if(x == 0) x = new_node(k);
    else {
        int t = key[x] < k;
        insert(child[x][t], k);
        if(weight[child[x][t]] < weight[x]) rotate(x, t);
    }
    update(x);
}

void remove(int &x, int k) {
    if(key[x] == k) {
        if(child[x][0] && child[x][1]) {
            int t = weight[child[x][0]] < weight[child[x][1]];
            rotate(x, t); remove(child[x][t ^ 1], k);
        }
        else {
            stk[++top] = x;
            x = child[x][0] + child[x][1];
        }
    }
    else remove(child[x][key[x] < k], k);
    if(x > 0) update(x);
}

int kth(int &x, int k) {
    if(x == 0 || k <= 0 || k > size[x]) return 0;
    int s = 0;
    if(child[x][0]) s = size[child[x][0]];
    if(k == s + 1) return key[x];
    if(k <= s) return kth(child[x][0], k);
    return kth(child[x][1], k - s - 1);
}

struct Node {
    int l, r, k, id;
    void read(int i) {
        id = i;
        scanf("%d%d%d", &l, &r, &k);
    }
    bool operator < (const Node &rhs) const {
        if(r != rhs.r) return r < rhs.r;
        return l < rhs.l;
    }
};

Node query[MAXN];
int a[MAXN], ans[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < m; ++i) query[i].read(i);
    sort(query, query + m);
    int left = 1, right = 0, root = 0;
    for(int i = 0; i < m; ++i) {
        while(right < query[i].r)
            if(!root) root = new_node(a[++right]);
            else insert(root, a[++right]);
        while(left > query[i].l)
            if(!root) root = new_node(a[--left]);
            else insert(root, a[--left]);
        while(left < query[i].l) remove(root, a[left++]);
        ans[query[i].id] = kth(root, query[i].k);
    }
    for(int i = 0; i < m; ++i) printf("%d\n", ans[i]);
}
