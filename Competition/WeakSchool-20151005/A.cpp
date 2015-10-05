#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXV = 210;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;
const double EPS = 1e-6;

int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct SPFA_COST_FLOW {
    int head[MAXV], ecnt;
    int to[MAXE], nxt[MAXE], flow[MAXE];
    double cost[MAXE];
    int n;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f, double c) {
        to[ecnt] = v; flow[ecnt] = f; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; cost[ecnt] = -c; nxt[ecnt] = head[v]; head[v] = ecnt++;
    }

    double dis[MAXV];
    int pre[MAXV];
    bool vis[MAXV];

    bool spfa(int st, int ed) {
        for(int i = 1; i <= n; ++i)
            dis[i] = 1e100, vis[i] = false;
        dis[st] = 0;
        queue<int> que; que.push(st);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; ~p; p = nxt[p]) if(flow[p]) {
                int v = to[p];
                if(sgn(dis[u] + cost[p] - dis[v]) < 0) {
                    dis[v] = dis[u] + cost[p];
                    pre[v] = p;
                    if(!vis[v]) {
                        vis[v] = true;
                        que.push(v);
                    }
                }
            }
        }
        return dis[ed] < 1e100;
    }

    double min_cost_flow(int st, int ed) {
        double mincost = 0;
        while(spfa(st, ed)) {
            int u = ed;
            while(u != st) {
                flow[pre[u]]--;
                flow[pre[u] ^ 1]++;
                u = to[pre[u] ^ 1];
            }
            mincost += dis[ed];
        }
        return mincost;
    }
} G;

int id[MAXV][MAXV];
int x[MAXV], y[MAXV];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < (n << 1); ++i) scanf("%d%d", &x[i], &y[i]);
    int ss = 2 * n + 1, tt = ss + 1;
    G.init(tt);
    for(int i = 0; i < n; ++i) {
        G.add_edge(ss, i + 1, 1, 0);
        G.add_edge(n + i + 1, tt, 1, 0);
        for(int j = 0; j < n; ++j) {
            id[i][j] = G.ecnt;
            G.add_edge(i + 1, n + j + 1, 1, hypot(x[i] - x[n + j], y[i] - y[n + j]));
        }
    }
    G.min_cost_flow(ss, tt);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(G.flow[id[i][j]] == 0) {
                printf("%d\n", j + 1);
                break;
            }
        }
    }
}
