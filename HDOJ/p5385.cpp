#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXE = 100010;
const int INF = 0x3f3f3f3f;

int head[MAXV], ecnt;
int from[MAXE], to[MAXE], nxt[MAXE], cost[MAXE];
int n, m, T;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
   from[ecnt] = u; to[ecnt] = v; nxt[ecnt] = head[u]; cost[ecnt] = INF; head[u] = ecnt++;
}

int dis[MAXV], pre[MAXV];

void solve() {
    memset(dis + 1, 0x3f, n * sizeof(int));
    dis[1] = INF - 1; pre[1] = -1;
    int l = 1, r = n, nowdis = 0;
    while(l <= r) {
        int u = dis[l] < INF ? l++ : r--;
        dis[u] = nowdis++;
        if(~pre[u]) cost[pre[u]] = dis[u] - dis[from[pre[u]]];
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[v] == INF) {
                dis[v] = INF - 1;
                pre[v] = p;
            }
        }
    }
}

void print() {
    for(int i = 0; i < ecnt; ++i)
        printf("%d\n", cost[i] < INF ? cost[i] : n);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        solve();
        print();
    }
}
