#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXV = 310;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

struct SPFA_COST_FLOW {
    int head[MAXV], ecnt;
    int to[MAXE], nxt[MAXE], flow[MAXE], cost[MAXE];
    int n;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f, int c) {
        to[ecnt] = v; flow[ecnt] = f; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; cost[ecnt] = -c; nxt[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXV], pre[MAXV];
    bool vis[MAXV];

    bool spfa(int st, int ed) {
        memset(vis + 1, 0, n * sizeof(bool));
        memset(dis + 1, 0x3f, n * sizeof(int));
        queue<int> que; que.push(st);
        dis[st] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            vis[u] = false;
            for(int p = head[u]; ~p; p = nxt[p]) {
                int v = to[p];
                if(flow[p] && dis[u] + cost[p] < dis[v]) {
                    dis[v] = dis[u] + cost[p];
                    pre[v] = p;
                    if(!vis[v]) {
                        que.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dis[ed] < INF;
    }

    int min_cost_flow(int st, int ed) {
        int mincost = 0;
        while(spfa(st, ed)) {
            if(dis[ed] >= 0) break;
            int u = ed;
            while(u != st) {
                flow[pre[u]] -= 1;
                flow[pre[u] ^ 1] += 1;
                u = to[pre[u] ^ 1];
            }
            mincost += dis[ed];
        }
        return mincost;
    }
} G;

int atuner[MAXV], alv[MAXV], aatk[MAXV];
int blv[MAXV], batk[MAXV], br[MAXV][3];
int mat[MAXV][MAXV];
int T, n, m;

void add_edge(int a, int b, int i) {
    if(atuner[a] == 1) swap(a, b);
    if(alv[a] + alv[b] == blv[i])
        mat[a][b] = max(mat[a][b], batk[i] - aatk[a] - aatk[b]);
}

int solve() {
    int ss = n + 1, tt = ss + 1;
    G.init(tt);
    for(int i = 1; i <= n; ++i) {
        if(atuner[i] == 0) G.add_edge(ss, i, 1, 0);
        else G.add_edge(i, tt, 1, 0);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) mat[i][j] = 0;
    for(int i = 1; i <= m; ++i) {
        if(br[i][0] == 0) {
            for(int a = 1; a <= n; ++a) if(atuner[a] == 0)
                for(int b = 1; b <= n; ++b) if(atuner[b] == 1)
                    add_edge(a, b, i);
        } else if(br[i][0] == 1) {
            int a = br[i][1];
            for(int b = 1; b <= n; ++b) if(atuner[a] != atuner[b])
                add_edge(a, b, i);
        } else {
            add_edge(br[i][1], br[i][2], i);
        }
    }
    for(int i = 1; i <= n; ++i) if(atuner[i] == 0)
        for(int j = 1; j <= n; ++j) if(atuner[j] == 1)
            if(mat[i][j] > 0) G.add_edge(i, j, 1, -mat[i][j]);
    return accumulate(aatk + 1, aatk + n + 1, 0) - G.min_cost_flow(ss, tt);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d%d%d", &atuner[i], &alv[i], &aatk[i]);
        for(int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &blv[i], &batk[i], &br[i][0]);
            for(int j = 1; j <= br[i][0]; ++j) scanf("%d", &br[i][j]);
        }
        printf("%d\n", solve());
    }
}
