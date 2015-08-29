#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXE = 200010;

int head[MAXV], ecnt;
int from[MAXE], to[MAXE], nxt[MAXE], cost[MAXE], id[MAXE];
int head2[MAXV], ecnt2;
int to2[MAXE], nxt2[MAXE], cost2[MAXE];
int head3[MAXV], ecnt3;
int to3[MAXE], nxt3[MAXE];
int n, m, s, t;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
    memset(head2 + 1, -1, n * sizeof(int));
    ecnt2 = 0;
    memset(head3 + 1, -1, n * sizeof(int));
    ecnt3 = 0;
}

void add_edge(int u, int v, int c) {
    from[ecnt] = u;
    to[ecnt] = v; nxt[ecnt] = head[u]; cost[ecnt] = c; head[u] = ecnt++;
    to2[ecnt2] = u; nxt2[ecnt2] = head2[v]; cost2[ecnt2] = c; head2[v] = ecnt2++;
}

void add_edge3(int u, int v) {
    to3[ecnt3] = v; nxt3[ecnt3] = head3[u]; head3[u] = ecnt3++;
    to3[ecnt3] = u; nxt3[ecnt3] = head3[v]; head3[v] = ecnt3++;
}

bool shortest[MAXE];
LL diss[MAXV], dist[MAXV], inf;

void dijkstra(LL dis[], int head[], int to[], int nxt[], int cost[], int st) {
    memset(dis + 1, 0x3f, n * sizeof(LL));
    inf = dis[0];
    priority_queue<pair<LL, int> > que;
    que.push(make_pair(dis[st] = 0, st));
    while(!que.empty()) {
        int u = que.top().second;
        LL d = -que.top().first; que.pop();
        if(d != dis[u]) continue;
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[u] + cost[p] < dis[v]) {
                dis[v] = dis[u] + cost[p];
                que.push(make_pair(-dis[v], v));
            }
        }
    }
}

int pre[MAXV], lowlink[MAXV];
bool iscut[MAXE], vis[MAXE];
int stk[MAXV], top;
int dfs_clock;

void dfs(int u, int f) {
    pre[u] = lowlink[u] = ++dfs_clock;
    for(int p = head3[u]; ~p; p = nxt3[p]) if(!vis[p]) {
        vis[p] = vis[p ^ 1] = true;
        int v = to3[p];
        if(!pre[v]) {
            dfs(v, p);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if(p != f && (p ^ 1) != f) {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if(f >= 0 && lowlink[u] == pre[u]) iscut[f] = iscut[f ^ 1] = true;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    init();
    for(int i = 0, u, v, c; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u, v, c);
    }
    dijkstra(diss, head, to, nxt, cost, s);
    dijkstra(dist, head2, to2, nxt2, cost2, t);
    for(int i = 0; i < m; ++i) {
        shortest[i] = (diss[t] == diss[from[i]] + dist[to[i]] + cost[i]);
        if(shortest[i]) {
            id[i] = ecnt3;
            add_edge3(from[i], to[i]);
        }
    }
    dfs(s, -1);
    for(int i = 0; i < m; ++i) {
        if(shortest[i] && iscut[id[i]]) {
            puts("YES");
        } else {
            LL d = diss[from[i]] + dist[to[i]];
            if(d + 1 < diss[t]) printf("CAN %I64d\n", cost[i] - (diss[t] - d - 1));
            else puts("NO");
        }
    }
}
