#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;

struct Node {
    int x, id;
    bool operator < (const Node &rhs) const {
        return x < rhs.x;
    }
};

int tree[MAXN * 4];
Node a[MAXN * 2];
int l[MAXN], r[MAXN];
int n, cnt, m;

void pushdown(int x) {
    if(!tree[x]) return ;
    int ll = x << 1, rr = ll ^ 1;
    tree[ll] = tree[rr] = tree[x];
    tree[x] = 0;
}

void update(int x, int left, int right, int L, int R, int key) {
    if(L <= left && right <= R) {
        tree[x] = key;
    }
    else {
        pushdown(x);
        int ll = x << 1, rr = ll ^ 1;
        int mid = (left + right) >> 1;
        if(L < mid) update(ll, left, mid, L, R, key);
        if(mid < R) update(rr, mid, right, L, R, key);
    }
}

bool vis[MAXN];

int query(int x, int left, int right) {
    int ret = 0;
    if(tree[x]) {
        if(!vis[tree[x]]) {
            vis[tree[x]] = true;
            ret = 1;
        }
    }
    else {
        if(right - left == 1) return 0;
        int ll = x << 1, rr = ll ^ 1;
        int mid = (left + right) >> 1;
        ret += query(ll, left, mid);
        ret += query(rr, mid, right);
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        cnt = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &l[i], &r[i]);
            a[cnt].x = l[i]; a[cnt++].id = i;
            a[cnt].x = r[i] + 1; a[cnt++].id = i + MAXN;
        }
        sort(a, a + cnt);
        m = 1;
        for(int i = 0; i < cnt; ++i) {
            if(i > 0 && a[i - 1].x != a[i].x) ++m;
            if(a[i].id < MAXN) l[a[i].id] = m;
            else r[a[i].id - MAXN] = m;
        }
        memset(tree, 0, sizeof(tree));
        for(int i = 0; i < n; ++i)
            update(1, 1, m, l[i], r[i], i + 1);
        memset(vis, 0, sizeof(vis));
        int ans = query(1, 1, m);
        printf("%d\n", ans);
    }
}
