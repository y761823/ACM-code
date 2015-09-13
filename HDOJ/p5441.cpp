#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 20010;
const int MAXE = 100010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int a, b, val;
    void read() {
        scanf("%d%d%d", &a, &b, &val);
    }
    bool operator < (const Edge &rhs) const {
        return val < rhs.val;
    }
} edge[MAXE];

struct Query {
    int val, id;
    void read(int i) {
        id = i;
        scanf("%d", &val);
    }
    bool operator < (const Query &rhs) const {
        return val < rhs.val;
    }
} query[MAXV];

int fa[MAXV], cnt[MAXV], ans[MAXV];
int n, m, res, q, T;

int find_set(int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void merge(int x, int y) {
    x = find_set(x), y = find_set(y);
    if(x != y) {
        res -= cnt[x] * (cnt[x] - 1);
        res -= cnt[y] * (cnt[y] - 1);
        fa[x] = y;
        cnt[y] += cnt[x];
        res += cnt[y] * (cnt[y] - 1);
    }
}

void solve() {
    res = 0;
    for(int i = 0, j = 0; i < q; ++i) {
        while(j < m && edge[j].val <= query[i].val)
            merge(edge[j].a, edge[j].b), j++;
        ans[query[i].id] = res;
    }
    for(int i = 0; i < q; ++i)
        printf("%d\n", ans[i]);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &q);
        for(int i = 0; i < m; ++i) edge[i].read();
        for(int i = 0; i < q; ++i) query[i].read(i);

        for(int i = 1; i <= n; ++i) fa[i] = i, cnt[i] = 1;
        sort(edge, edge + m);
        sort(query, query + q);
        solve();
    }
}
