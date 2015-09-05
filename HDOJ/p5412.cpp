#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 100010;

int tree[MAXN];
int n, Q;

int lowbit(int x) {
    return x & -x;
}

void modify(int x, int val) {
    while(x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int get_sum(int x) {
    int res = 0;
    while(x) {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

struct Query {
    int op, l, r, k, id, type;
    void set(int _id, int _op, int _l, int _r, int _k) {
        id = _id; op = _op; l = _l; r = _r; k = _k;
    }
    bool operator < (const Query &rhs) const {
        if(type != rhs.type) return type < rhs.type;
        return id < rhs.id;
    }
} query[MAXN * 3];
int a[MAXN], q;
int ans[MAXN];

void work(int down, int up, int l, int r) {
    if(l > r) return ;
    if(down == up) {
        for(int i = l; i < r; ++i)
            if(~query[i].op) ans[query[i].op] = down;
        return ;
    }
    int mid = down + (up - down) / 2, cnt = 0;
    for(int i = l; i < r; ++i) {
        if(~query[i].op) {
            int t = get_sum(query[i].r) - get_sum(query[i].l - 1);
            if(t >= query[i].k) query[i].type = 0;
            else query[i].k -= t, query[i].type = 1;
        } else {
            if(query[i].r <= mid) {
                modify(query[i].l, query[i].k);
                query[i].type = 0;
            } else query[i].type = 1;
        }
        cnt += query[i].type ^ 1;
    }

    for(int i = l; i < r; ++i) {
        if(query[i].op == -1 && query[i].r <= mid)
            modify(query[i].l, -query[i].k);
    }

    sort(query + l, query + r);
    work(down, mid, l, l + cnt);
    work(mid + 1, up, l + cnt, r);
}

int main() {
    while(scanf("%d", &n) != EOF) {
        q = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            query[q].set(q, -1, i, a[i], 1); q++;
        }
        int right = *max_element(a + 1, a + n + 1);
        scanf("%d", &Q);
        for(int i = 0, op, l, r, k; i < Q; ++i) {
            scanf("%d%d%d", &op, &l, &r);
            if(op == 1) {
                query[q].set(q, -1, l, a[l], -1); q++;
                query[q].set(q, -1, l, a[l] = r, 1); q++;
                right = max(right, r);
            } else {
                scanf("%d", &k);
                query[q].set(q, i, l, r, k); q++;
            }
        }
        memset(ans, -1, Q * sizeof(int));
        work(1, right, 0, q);
        for(int i = 0; i < Q; ++i)
            if(ans[i] > 0) printf("%d\n", ans[i]);
    }
}
