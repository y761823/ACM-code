/*
ID: y7618231
PROG: telecow
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
#include <vector>
#include <numeric>
#include <set>
#include <deque>
#include <queue>
#include <unordered_map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 110;
const int MAXV = MAXN << 1;
const int MAXE = 3010;//bug?
const int INF = 0x3f3f3f3f;

struct DINIC {
    int head[MAXV], ecnt;
    int to[MAXE], next[MAXE], flow[MAXE];
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    int cur[MAXV], dis[MAXV];

    bool bfs() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        queue<int> que; que.push(st);
        dis[st] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(flow[p] && dis[v] == INF) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
        return dis[ed] < INF;
    }

    int dfs(int u, int a) {
        if(u == ed || a == 0) return a;
        int outflow = 0, f;
        for(int &p = cur[u]; ~p; p = next[p]) {
            int v = to[p];
            if(dis[v] == dis[u] + 1 && (f = dfs(v, min(flow[p], a))) > 0) {
                flow[p] -= f;
                flow[p ^ 1] += f;
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

    bool vis[MAXV];

    bool link(int x, int y) {
        memset(vis + 1, 0, n * sizeof(bool));
        queue<int> que; que.push(x);
        vis[x] = true;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(flow[p] && !vis[v]) {
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
        return vis[y];
    }

    void back_flow(int x, int y) {
        st = x, ed = y;
        bfs();
        memcpy(cur + 1, head + 1, n * sizeof(int));
        dfs(st, 1);
    }
} G;

int n, m, ss, tt;

int main() {
#ifndef OYK_JUDGE
    freopen("telecow.in", "r", stdin); freopen("telecow.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d%d", &n, &m, &ss, &tt);
    G.init(n << 1);
    for(int i = 1; i <= n; ++i) {
        int cap = (i == ss || i == tt) ? INF : 1;
        G.add_edge(i, i + n, cap);
    }
    for(int i = 0, u, v; i < m; ++i) {
        scanf("%d%d", &u, &v);
        G.add_edge(u + n, v, INF);
        G.add_edge(v + n, u, INF);
    }
    printf("%d\n", G.maxflow(ss, tt + n));
    bool flag = false;
    for(int i = 1; i <= n; ++i) {
        int p = (i - 1) << 1;
        if(G.flow[p] || G.link(i, i + n)) continue;
        G.flow[p ^ 1] = 0;
        G.back_flow(i, ss);
        G.back_flow(tt + n, i + n);

        if(flag) putchar(' ');
        else flag = true;
        printf("%d", i);
    }
    puts("");
}
