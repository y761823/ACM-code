#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 5010;
const int MAXE = 200010;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int n, m;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

priority_queue<pair<int, int> > que;
int dis[MAXV], dis2[MAXV];

int dijkstra() {
    memset(dis + 1, 0x3f, n * sizeof(int));
    memset(dis2 + 1, 0x3f, n * sizeof(int));
    que.push(make_pair(dis[1] = 0, 1));
    while(!que.empty()) {
        int d = -que.top().first, u = que.top().second; que.pop();
        if(d > dis2[u]) continue;
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p], c = d + cost[p];
            if(c < dis[v]) {
                swap(c, dis[v]);
                que.push(make_pair(-dis[v], v));
            }
            if(dis[v] < c && c < dis2[v]) {
                dis2[v] = c;
                que.push(make_pair(-dis2[v], v));
            }
        }
    }
    return dis2[n];
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    for(int i = 0, u, v, c; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u, v, c);
    }
    printf("%d\n", dijkstra());
}
