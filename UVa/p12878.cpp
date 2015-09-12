#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 10010;
const int MAXE = 500010;
const int INF = 0x3f3f3f3f;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int n, m;

void init() {
    memset(head, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

int dis1[MAXV], dis2[MAXV];

void make_dis(int dis[], int st) {
    memset(dis, 0x3f, n * sizeof(int));
    priority_queue<pair<int, int> > que;
    que.push(make_pair(dis[st] = 0, st));
    while(!que.empty()) {
        int u = que.top().second, d = -que.top().first; que.pop();
        if(dis[u] != d) continue;
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[u] + cost[p] < dis[v]) {
                dis[v] = dis[u] + cost[p];
                que.push(make_pair(-dis[v], v));
            }
        }
    }
}

int solve() {
    make_dis(dis1, 0);
    make_dis(dis2, n - 1);
    int res = 0, d = dis1[n - 1];
    for(int u = 0; u < n; ++u) {
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis1[u] + cost[p] + dis2[v] == d)
                res += cost[p];
        }
    }
    return res << 1;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0, u, v, c; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        printf("%d\n", solve());
    }
}
