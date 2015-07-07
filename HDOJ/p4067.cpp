////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-31 17:20:24
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4067
////Problem Title: 
////Run result: Accept
////Run time:328MS
////Run memory:404KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXV = 110;
const int MAXE = 2110 * 2;
const int INF = 0x3f3f3f3f;

struct SPFA_COST_FLOW {
    int head[MAXV], ecnt;
    int to[MAXE], next[MAXE], cost[MAXE], flow[MAXE];
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f, int c) {
        to[ecnt] = v; flow[ecnt] = f; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; cost[ecnt] = -c; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXV], pre[MAXV];
    bool vis[MAXV];
    queue<int> que;

    bool spfa() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        memset(vis + 1, 0, n * sizeof(bool));
        dis[st] = 0;
        que.push(st);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(flow[p] && dis[u] + cost[p] < dis[v]) {
                    pre[v] = p;
                    dis[v] = dis[u] + cost[p];
                    if(!vis[v]) {
                        que.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dis[ed] < INF;
    }

    int mincost, maxflow;

    int min_cost(int ss, int tt) {
        st = ss, ed = tt;
        maxflow = mincost = 0;
        while(spfa()) {
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
            maxflow += tmp;
            mincost += tmp * dis[ed];
        }
        return mincost;
    }
} G;

struct Edge {
    int u, v, a, b;
    void read() {
        scanf("%d%d%d%d", &u, &v, &a, &b);
    }
};

Edge edge[MAXE];
int indeg[MAXV];
int n, m, T, st, ed;

int solve() {
    memset(indeg + 1, 0, n * sizeof(int));
    indeg[st] = 1; indeg[ed] = -1;
    int ans = 0, sum = 0, ss = n + 1, tt = n + 2;
    G.init(tt);
    for(int i = 0; i < m; ++i) {
        if(edge[i].a > edge[i].b) {
            ans += edge[i].b;
            G.add_edge(edge[i].u, edge[i].v, 1, edge[i].a - edge[i].b);
        } else {
            ans += edge[i].a;
            indeg[edge[i].u]--;
            indeg[edge[i].v]++;
            G.add_edge(edge[i].v, edge[i].u, 1, edge[i].b - edge[i].a);
        }
    }
    for(int i = 1; i <= n; ++i) {
        if(indeg[i] > 0) G.add_edge(ss, i, indeg[i], 0), sum += indeg[i];
        if(indeg[i] < 0) G.add_edge(i, tt, -indeg[i], 0);
    }
    ans += G.min_cost(ss, tt);
    if(G.maxflow != sum) return -1;
    return ans;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d", &n, &m, &st, &ed);
        for(int i = 0; i < m; ++i) edge[i].read();
        int res = solve();
        if(res == -1) printf("Case %d: impossible\n", t);
        else printf("Case %d: %d\n", t, res);
    }
}
