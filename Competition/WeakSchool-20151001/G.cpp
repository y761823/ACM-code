#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXV = 2010;
const int MAXE = 50010;
const int INF = 0x3f3f3f3f;

struct DINIC {
    int head[MAXV], ecnt;
    int to[MAXE], nxt[MAXE], flow[MAXE];
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f) {
        to[ecnt] = v; flow[ecnt] = f; nxt[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; nxt[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXV], cur[MAXV];

    bool bfs() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        queue<int> que; que.push(st);
        dis[st] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = nxt[p]) if(flow[p]) {
                int v = to[p];
                if(dis[u] + 1 < dis[v]) {
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
        for(int &p = cur[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[u] + 1 == dis[v] && (f = dfs(v, min(flow[p], a))) > 0) {
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
} G;

vector<int> adjs[MAXV];
int color[MAXV];
int w[MAXV], p[MAXV], type[MAXV];
int n, m;

void dfs(int u, int col) {
    color[u] = col;
    foreach(v, adjs[u]) if(color[*v] == -1)
        dfs(*v, col ^ 1);
}

int solve() {
    memset(color + 1, -1, n * sizeof(int));
    for(int i = 1; i <= n; ++i)
        if(color[i] == -1) dfs(1, 0);
    int ss = 2 * n + 1, tt = ss + 1;
    G.init(tt);
    for(int i = 1; i <= n; ++i) {
        G.add_edge(i, i + n, w[i]);
        type[i] = ((p[i] >> color[i]) & 1) | (1 << ((p[i] >> (color[i] ^ 1)) & 1));
        if(!(type[i] & 1))
            G.add_edge(ss, i, INF);
        if(!(type[i] & 2))
            G.add_edge(n + i, tt, INF);
    }
    for(int u = 1; u <= n; ++u)
        foreach(v, adjs[u]) G.add_edge(n + u, *v, INF);
    return G.maxflow(ss, tt);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
        for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
        for(int i = 1; i <= n; ++i) adjs[i].clear();
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            adjs[u].push_back(v);
            adjs[v].push_back(u);
        }
        printf("%d\n", solve());
    }
}
