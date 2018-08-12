#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXV = 110;
const int MAXE = 110;

struct Edge {
    int a, b, w;
    char col;
    bool used;
    void read() {
        scanf("%d%d%d %c", &a, &b, &w, &col);
    }
    void change() {
        if (col != 'G')
            col ^= ('R' ^ 'B');
    }
} edge[MAXE];
int ans[MAXE], fa[MAXV];
int n, m, T;

int find_fa(int x) {
    return fa[x] == x ? x : fa[x] = find_fa(fa[x]);
}

void kruskal() {
    for (int i = 0; i < m; ++i)
        edge[i].used = false;
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    sort(edge, edge + m, [](const Edge& lhs, const Edge& rhs) {
        return lhs.w < rhs.w;
    });
    int sum = 0;
    for (int i = 0; i < m; ++i) if (edge[i].col != 'B') {
        int fx = find_fa(edge[i].a), fy = find_fa(edge[i].b);
        if (fx != fy) {
            edge[i].used = true;
            sum += edge[i].w;
            fa[fx] = fy;
        }
    }
    sort(edge, edge + m, [](const Edge& lhs, const Edge& rhs) {
         if (lhs.used != rhs.used)
            return lhs.used > rhs.used;
         return lhs.w < rhs.w;
    });

    if (n == 1) {
        for (int i = 0; i < m; ++i) {
            sum += edge[i].w;
            ans[i + 1] = min<unsigned>(ans[i + 1], sum);
        }
    } else if (!edge[n - 2].used) {
        // not connected
    } else {
        ans[n - 1] = min<unsigned>(ans[n - 1], sum);
        for (int i = n - 1; i < m; ++i) {
            sum += edge[i].w;
            ans[i + 1] = min<unsigned>(ans[i + 1], sum);
        }
    }
}

void solve() {
    memset(ans + 1, 0xff, sizeof(int) * m);
    kruskal();
    for (int i = 0; i < m; ++i)
        edge[i].change();
    kruskal();
}

int main () {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i)
            edge[i].read();
        solve();
        printf("Case #%d:\n", t);
        for (int i = 1; i <= m; ++i)
            printf("%d\n", ans[i]);
    }
}
