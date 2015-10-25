#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXV = 20010;
const int MAXE = 100010;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int n, m, r, T;

void init(int n) {
    memset(head, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

priority_queue<pair<int, int> > que;
bool vis[MAXV];
int dis[MAXV];

int prim() {
    for(int i = 0; i < n + m; ++i) {
        dis[i] = 10000;
        vis[i] = false;
        que.push(make_pair(-dis[i], i));
    }
    while(!que.empty()) {
        int u = que.top().second; que.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(!vis[v] && cost[p] < dis[v]) {
                dis[v] = cost[p];
                que.push(make_pair(-dis[v], v));
            }
        }
    }
    return accumulate(dis, dis + n + m, 0);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &r);
        init(n + m);
        for(int i = 0, x, y, d; i < r; ++i) {
            scanf("%d%d%d", &x, &y, &d);
            add_edge(x, n + y, 10000 - d);
        }
        printf("%d\n", prim());
    }
}
