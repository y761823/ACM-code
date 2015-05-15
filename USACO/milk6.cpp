/*
ID: y7618231
PROG: milk6
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
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXV = 35;
const int MAXE = 2010;
const int INF = 0x3f3f3f3f;
const LL LINF = LL(INF) << 32;

struct DINIC {
    int head[MAXV], ecnt;
    int to[MAXE], next[MAXE];
    LL flow[MAXE];
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, LL c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXV], cur[MAXV];

    bool bfs() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        dis[st] = 0;
        queue<int> que; que.push(st);
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

    LL dfs(int u, LL a) {
        if(u == ed || a == 0) return a;
        LL outflow = 0, f;
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

    LL maxflow(int ss, int tt) {
        st = ss, ed = tt;
        LL res = 0;
        while(bfs()) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            res += dfs(st, LINF);
        }
        return res;
    }

    bool vis[MAXV];

    bool link(int x, int y) {
        queue<int> que; que.push(x);
        memset(vis + 1, 0, n * sizeof(bool));
        vis[x] = true;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(!vis[v] && flow[p]) {
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
        return vis[y];
    }

    void add_flow(int x, int y, LL f) {
        st = x, ed = y;
        while(bfs() && f) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            f -= dfs(x, f);
        }
    }

    void clear(int x, int y, int p) {
        LL tmp = flow[p ^ 1];
        flow[p ^ 1] = 0;
        add_flow(x, 1, tmp);
        add_flow(n, y, tmp);
    }
} G;

pair<int, int> edge[MAXE];
int n, m;

void solve() {
    LL res = G.maxflow(1, n);
    printf(longformat " " longformat "\n", res / 2000, res % 2000);
    for(int i = 0; i < m; ++i) {
        int u = edge[i].first, v = edge[i].second;
        if(G.flow[i << 1] == 0 && !G.link(u, v)) {
            printf("%d\n", i + 1);
            G.clear(u, v, i << 1);
        }
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("milk6.in", "r", stdin); freopen("milk6.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d", &n, &m);
    G.init(n);
    for(int i = 0, u, v, c; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        G.add_edge(u, v, (LL)c * 2000 + 1);
        edge[i] = make_pair(u, v);
    }
    solve();
}
