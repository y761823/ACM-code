#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 110;
const int MAXE = MAXV * MAXV;
const int INF = 0x7fffffff;

struct ZEK_FLOW {
    int head[MAXV], dis[MAXV];
    int next[MAXE], to[MAXE], cap[MAXE], cost[MAXE];
    int n, ecnt, st, ed;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c, int w) {
        to[ecnt] = v; cap[ecnt] = c; cost[ecnt] = w; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cap[ecnt] = 0; cost[ecnt] = -w; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    void SPFA() {
        for(int i = 1; i <= n; ++i) dis[i] = INF;
        priority_queue<pair<int, int> > que;
        dis[st] = 0; que.push(make_pair(0, st));
        while(!que.empty()) {
            int u = que.top().second, d = -que.top().first; que.pop();
            if(d != dis[u]) continue;
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(cap[p] && dis[v] > d + cost[p]) {
                    dis[v] = d + cost[p];
                    que.push(make_pair(-dis[v], v));
                }
            }
        }
        int t = dis[ed];
        for(int i = 1; i <= n; ++i) dis[i] = t - dis[i];
    }

    int minCost, maxFlow;
    bool vis[MAXV];

    int add_flow(int u, int aug) {
        if(u == ed) {
            maxFlow += aug;
            minCost += dis[st] * aug;
            return aug;
        }
        vis[u] = true;
        int now = aug;
        for(int p = head[u]; p; p = next[p]) {
            int &v = to[p];
            if(cap[p] && !vis[v] && dis[u] == dis[v] + cost[p]) {
                int t = add_flow(v, min(now, cap[p]));
                cap[p] -= t;
                cap[p ^ 1] += t;
                now -= t;
                if(!now) break;
            }
        }
        return aug - now;
    }

    bool modify_label() {
        int d = INF;
        for(int u = 1; u <= n; ++u) if(vis[u]) {
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(cap[p] && !vis[v]) d = min(d, dis[v] + cost[p] - dis[u]);
            }
        }
        if(d == INF) return false;
        for(int i = 1; i <= n; ++i) if(vis[i]) dis[i] += d;
        return true;
    }

    int min_cost_flow(int ss, int tt, int nn) {
        st = ss, ed = tt, n = nn;
        minCost = maxFlow = 0;
        SPFA();
        while(true) {
            while(true) {
                for(int i = 1; i <= n; ++i) vis[i] = 0;
                if(!add_flow(st, INF)) break;
            }
            if(!modify_label()) break;
        }
        return minCost;
    }
} G;

int n, m, k;
int need[MAXV][MAXV], have[MAXV][MAXV], sum[MAXV];
int mat[MAXV][MAXV];

int main() {
    while(scanf("%d%d%d", &n, &m, &k) != EOF) {
        if(n == 0 && m == 0 && k == 0) break;
        memset(sum, 0, sizeof(sum));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= k; ++j) scanf("%d", &need[i][j]), sum[j] += need[i][j];
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= k; ++j) scanf("%d", &have[i][j]);
        int ans = 0; bool flag = true;
        for(int x = 1; x <= k; ++x) {
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j) scanf("%d", &mat[i][j]);
            if(!flag) continue;
            G.init();
            int ss = n + m + 1, tt = ss + 1;
            for(int i = 1; i <= m; ++i) G.add_edge(ss, i, have[i][x], 0);
            for(int i = 1; i <= n; ++i) G.add_edge(i + m, tt, need[i][x], 0);
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j) G.add_edge(j, i + m, INF, mat[i][j]);
            ans += G.min_cost_flow(ss, tt, tt);
            flag = (G.maxFlow == sum[x]);
        }
        if(flag) printf("%d\n", ans);
        else puts("-1");
    }
}
