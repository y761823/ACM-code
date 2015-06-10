#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

namespace Bilibili {
    const int MAXV = 10010;
    const int MAXE = MAXV * 4;

    struct Edge {
        int u, v, cost;
        Edge(int u = 0, int v = 0, int cost = 0):
            u(u), v(v), cost(cost) {}
        bool operator < (const Edge &rhs) const {
            return cost < rhs.cost;
        }
    };

    struct Point {
        int x, y, id;
        void read(int i) {
            id = i;
            scanf("%d%d", &x, &y);
        }
        bool operator < (const Point &rhs) const {
            if(x != rhs.x) return x < rhs.x;
            return y < rhs.y;
        }
    };

    Point p[MAXV];
    Edge edge[MAXE];
    int x_plus_y[MAXV], y_sub_x[MAXV];
    int n, k, ecnt;

    int hash[MAXV], hcnt;

    void get_y_sub_x() {
        for(int i = 0; i < n; ++i) hash[i] = y_sub_x[i] = p[i].y - p[i].x;
        sort(hash, hash + n);
        hcnt = unique(hash, hash + n) - hash;
        for(int i = 0; i < n; ++i) y_sub_x[i] = lower_bound(hash, hash + hcnt, y_sub_x[i]) - hash + 1;
    }

    void get_x_plus_y() {
        for(int i = 0; i < n; ++i) x_plus_y[i] = p[i].x + p[i].y;
    }

    int tree[MAXV];
    int lowbit(int x) {
        return x & -x;
    }

    void update_min(int &a, int b) {
        if(b == -1) return ;
        if(a == -1 || x_plus_y[a] > x_plus_y[b])
            a = b;
    }

    void initBit() {
        memset(tree + 1, -1, hcnt * sizeof(int));
    }

    void modify(int x, int val) {
        while(x) {
            update_min(tree[x], val);
            x -= lowbit(x);
        }
    }

    int query(int x) {
        int res = -1;
        while(x <= hcnt) {
            update_min(res, tree[x]);
            x += lowbit(x);
        }
        return res;
    }

    void build_edge() {
        sort(p, p + n);
        get_x_plus_y();
        get_y_sub_x();
        initBit();
        for(int i = n - 1; i >= 0; --i) {
            int tmp = query(y_sub_x[i]);
            if(tmp != -1) edge[ecnt++] = Edge(p[i].id, p[tmp].id, x_plus_y[tmp] - x_plus_y[i]);
            modify(y_sub_x[i], i);
        }
    }

    int fa[MAXV], ans[MAXV];

    int find_set(int x) {
        return fa[x] == x ? x : fa[x] = find_set(fa[x]);
    }

    int kruskal() {
        for(int i = 0; i < n; ++i) fa[i] = i;
        sort(edge, edge + ecnt);
        int acnt = 0;
        for(int i = 0; i < ecnt; ++i) {
            int fu = find_set(edge[i].u), fv = find_set(edge[i].v);
            if(fu != fv) {
                ans[acnt++] = edge[i].cost;
                fa[fu] = fv;
            }
        }
        reverse(ans, ans + acnt);
        return ans[k - 1];
    }

    void mymain() {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i) p[i].read(i);

        build_edge();
        for(int i = 0; i < n; ++i) swap(p[i].x, p[i].y);
        build_edge();
        for(int i = 0; i < n; ++i) p[i].x = -p[i].x;
        build_edge();
        for(int i = 0; i < n; ++i) swap(p[i].x, p[i].y);
        build_edge();

        printf("%d\n", kruskal());
    }
}

int main() {
    Bilibili::mymain();
}
