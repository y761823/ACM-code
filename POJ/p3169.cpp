#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXV = 1010;
const int MAXE = 20010 + MAXV;
const int INF = 0x3f3f3f3f;

int from[MAXE], to[MAXE], cost[MAXE];
int n, ml, md, ecnt;

void add_edge(int u, int v, int c) {
    from[ecnt] = u; to[ecnt] = v; cost[ecnt] = c;
    ecnt++;
}

int dis[MAXV];

bool check() {
    memset(dis + 1, 0, n * sizeof(int));
    for(int i = 0; i < n; ++i) {
        for(int e = 0; e < ecnt; ++e) {
            if(dis[from[e]] + cost[e] < dis[to[e]]) {
                dis[to[e]] = dis[from[e]] + cost[e];
                if(i == n - 1) return false;
            }
        }
    }
    return true;
}

int bellman_ford() {
    memset(dis + 1, 0x3f, n * sizeof(int));
    dis[1] = 0;
    for(int i = 0; i < n; ++i) {
        for(int e = 0; e < ecnt; ++e) if(dis[from[e]] < INF) {
            dis[to[e]] = min(dis[to[e]], dis[from[e]] + cost[e]);
        }
    }
    return dis[n] < INF ? dis[n] : -2;
}

int main() {
    scanf("%d%d%d", &n, &ml, &md);
    for(int i = 1; i < n; ++i) {
        add_edge(i + 1, i, 0);
    }
    for(int i = 0, a, b, d; i < ml; ++i) {
        scanf("%d%d%d", &a, &b, &d);
        add_edge(a, b, d);
    }
    for(int i = 0, a, b, d; i < md; ++i) {
        scanf("%d%d%d", &a, &b, &d);
        add_edge(b, a, -d);
    }
    if(!check()) puts("-1");
    else printf("%d\n", bellman_ford());
}
