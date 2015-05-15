/*
ID: y7618231
PROG: ditch
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXV = 210;
const int MAXE = MAXV << 1;
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
#ifndef OYK_JUDGE
    freopen("ditch.in", "r", stdin); freopen("ditch.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &m, &n);
    G.init(n);
    for(int i = 0, x, y, z; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        G.add_edge(x, y, z);
    }
    printf("%d\n", G.maxflow(1, n));
}
