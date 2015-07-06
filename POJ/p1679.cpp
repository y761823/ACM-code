#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXE = 251000;
const int MAXN = 105;

struct Edge {
    int from, to, val;
    bool operator < (const Edge &rhs) const {
        return val < rhs.val;
    }
} edge[MAXE];

int fa[MAXN], deg[MAXN];
int n, ecnt;

void init() {
    ecnt = 0;
    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
        deg[i] = 0;
    }
}

void add_edge(int u, int v, int c) {
    edge[ecnt].from = u;
    edge[ecnt].to = v;
    edge[ecnt++].val = c;
}

int getfather(int x) {
    return fa[x] == x ? x : getfather(fa[x]);
}

void union_set(int x, int y) {
    int a = getfather(x);
    int b = getfather(y);
    if(a == b) return ;
    if(deg[a] <= deg[b]) swap(a, b);
    ++deg[a]; fa[b] = a;
}

int kruskal() {
    int sum = 0;
    int xa, ya;
    sort(edge, edge + ecnt);
    for(int i = 0; i < ecnt; ++i) {
        xa = getfather(edge[i].from);
        ya = getfather(edge[i].to);
        if(xa == ya) continue;
        for(int j = i + 1; j < ecnt; ++j) {
            if(edge[j].val != edge[i].val) break;
            if(xa == getfather(edge[j].from) && ya == getfather(edge[j].to)) {
                return -1;
                break;
            }
        }
        union_set(edge[i].from, edge[i].to);
        sum += edge[i].val;
    }
    return sum;
}

int main() {
    int T, m, a, b, c;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            if(a > b) add_edge(b, a, c);
            else add_edge(a, b, c);
        }
        int ans = kruskal();
        if(ans < 0) printf("Not Unique!\n");
        else printf("%d\n", ans);
    }
}
