#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 20010;
const int MAXE = 100010;
const int INF = 0x3f3f3f3f;

struct DINIC {
    int head[MAXV], ecnt;
    int to[MAXE], next[MAXE], cap[MAXE], flow[MAXE];
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; cap[ecnt] = c; flow[ecnt] = 0; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cap[ecnt] = 0; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    bool vis[MAXV];
    int dis[MAXV], cur[MAXV];

    bool bfs() {
        memset(vis + 1, 0, n * sizeof(bool));
        queue<int> que; que.push(st);
        dis[st] = 0; vis[st] = true;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(!vis[v] && cap[p] > flow[p]) {
                    vis[v] = true;
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
        return vis[ed];
    }

    int dfs(int u, int a) {
        if(u == ed || a == 0) return a;
        int outflow = 0, f;
        for(int &p = cur[u]; ~p; p = next[p]) {
            int v = to[p];
            if(dis[u] + 1 == dis[v] && (f = dfs(v, min(a, cap[p] - flow[p]))) > 0) {
                flow[p] += f;
                flow[p ^ 1] -= f;
                outflow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return outflow;
    }

    int maxflow(int ss, int tt) {
        st = ss, ed = tt;
        int res = 0;
        while(bfs()) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            res += dfs(st, INF);
        }
        return res;
    }
} G;

int n, m;

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        int ss = 2 * n + 1, tt = ss + 1;
        G.init(tt);
        for(int i = 1; i <= n; ++i) {
            G.add_edge(ss, 2 * i, 1);
            G.add_edge(2 * i - 1, tt, 1);
        }
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            u++, v++;
            G.add_edge(u * 2, v * 2 - 1, 1);
        }
        puts(G.maxflow(ss, tt) == n ? "YES" : "NO");
    }
}
