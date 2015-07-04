#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 210;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

struct SPFA_COST_FLOW {
    int head[MAXV], ecnt;
    int to[MAXE], next[MAXE], flow[MAXE], cost[MAXE];
    int n;

    void init(int n) {
        this->n = n;
        memset(head, -1, n * sizeof(int));
    }

    void add_edge(int u, int v, int f, int c) {
        to[ecnt] = v; flow[ecnt] = f; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; cost[ecnt] = -c; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXV], pre[MAXV];
    bool vis[MAXV];

    bool spfa(int st, int ed) {
        memset(dis, 0x3f, n * sizeof(int)); dis[st] = 0;
        memset(vis, 0, n * sizeof(bool));
        queue<int> que; que.push(st);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; ~p; p = next[p]) if(flow[p]) {
                int v = to[p];
                if(dis[u] + cost[p] < dis[v]) {
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

    int min_cost(int st, int ed) {
        int mincost = 0;
        while(spfa(st, ed)) {
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
            mincost += dis[ed] * tmp;
        }
        return mincost;
    }
} G;

char mat[MAXV][MAXV];
pair<int, int> a[MAXV], b[MAXV];
int acnt, bcnt;
int n, m;

int getdis(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int solve() {
    acnt = bcnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(mat[i][j] == 'm') a[acnt++] = make_pair(i, j);
            if(mat[i][j] == 'H') b[bcnt++] = make_pair(i, j);
        }
    }
    G.init(acnt + bcnt + 2);
    int ss = acnt + bcnt, tt = ss + 1;
    for(int i = 0; i < acnt; ++i) {
        G.add_edge(ss, i, 1, 0);
        G.add_edge(acnt + i, tt, 1, 0);
        for(int j = 0; j < bcnt; ++j) {
            G.add_edge(i, acnt + j, 1, getdis(a[i], b[j]));
        }
    }
    return G.min_cost(ss, tt);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 0; i < n; ++i)
            scanf("%s", mat[i]);
        printf("%d\n", solve());
    }
}
