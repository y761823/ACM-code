#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

struct Node {
    int a, b, id, pre;
    void read(int i) {
        id = i;
        pre = -1;
        scanf("%d%d", &a, &b);
    }
    bool operator < (const Node &rhs) const {
        if(a != rhs.a) return a < rhs.a;
        return b > rhs.b;
    }
    bool operator == (const Node &rhs) const {
        return a == rhs.a && b == rhs.b;
    }
};

Node p[MAXN];
int n, g[MAXN], pos[MAXN];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) p[i].read(i + 1);
    sort(p, p + n);
    n = unique(p, p + n) - p;

    memset(g, 0x3f, n * sizeof(0));
    for(int i = 0; i < n; ++i) {
        int idx = lower_bound(g, g + n, p[i].b) - g;
        g[idx] = p[i].b;
        pos[idx] = i;
        if(idx) p[i].pre = pos[idx - 1];
    }

    int ans = lower_bound(g, g + n, INF) - g;
    printf("%d\n", ans);
    for(int i = pos[ans - 1]; ~i; i = p[i].pre)
        printf("%d ", p[i].id);
}
