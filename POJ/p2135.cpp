#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 1010;
const int MAXE = 40010;
const int INF = 0x7f7f7f7f;

struct SPFA_COST_FLOW {
    bool vis[MAXV];
    int head[MAXV], dis[MAXV], pre[MAXV];
    int to[MAXE], next[MAXE], cost[MAXE], flow[MAXE];
    int n, st, ed, ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c, int w) {
        to[ecnt] = v; flow[ecnt] = c; cost[ecnt] = w; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; cost[ecnt] = -w; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    bool spfa() {
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x7f, sizeof(dis));
        queue<int> que; que.push(st);
        vis[st] = true; dis[st] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && dis[v] > dis[u] + cost[p]) {
                    dis[v] = dis[u] + cost[p];
                    pre[v] = p;
                    if(!vis[v]) {
                        vis[v] = true;
                        que.push(v);
                    }
                }
            }
        }
        return dis[ed] < INF;
    }

    int maxFlow, minCost;

    int min_cost_flow(int ss, int tt, int nn) {
        st = ss, ed = tt, n = nn;
        maxFlow = minCost = 0;
        while(spfa()) {
            minCost += dis[ed];
            int u = ed, tmp = INF;
            while(u != st) {
                tmp = min(tmp, flow[pre[u]]);
                u = to[pre[u] ^ 1];
            }
            u = ed;
            while(u != st) {
                flow[pre[u]] -= tmp;
                flow[pre[u] ^ 1] += tmp;
                u = to[pre[u] ^ 1];
            }
            maxFlow += tmp;
        }
        return minCost;
    }
} G;

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    G.init();
    int ss = n + 1, tt = n + 2;
    while(m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        G.add_edge(u, v, 1, c);
        G.add_edge(v, u, 1, c);
    }
    G.add_edge(ss, 1, 2, 0);
    G.add_edge(n, tt, 2, 0);
    printf("%d\n", G.min_cost_flow(ss, tt, tt));
}
