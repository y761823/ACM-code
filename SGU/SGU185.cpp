#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 410;
const int INF = 0x3f3f3f3f;

struct Dinic {
    int head[MAXV], ecnt;
    vector<int> next;
    vector<short> to, flow;
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f) {
        to.push_back(v); flow.push_back(f); next.push_back(head[u]); head[u] = ecnt++;
        to.push_back(u); flow.push_back(0); next.push_back(head[v]); head[v] = ecnt++;
    }

    int dis[MAXV], cur[MAXV];

    bool bfs() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        dis[st] = 0;
        queue<int> que; que.push(st);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = next[p]) if(flow[p]) {
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
        for(int &p = cur[u]; ~p; p = next[p]) {
            int v = to[p];
            if(dis[u] + 1 == dis[v] && (f = dfs(v, min(a, (int)flow[p]))) > 0) {
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

    void getPath() {
        printf("%d", st);
        int u = st;
        while(u != ed) {
            for(int p = head[u]; ~p; p = next[p]) if(p % 2 == 0 && flow[p] == 0) {
                flow[p] = 1;
                printf(" %d", u = to[p]);
                break;
            }
        }
        puts("");
    }
} G;

int mat[MAXV][MAXV];
int dis[MAXV];
bool vis[MAXV];
int n, m;

void dijkstra(int st, int ed) {
    memset(dis + 1, 0x3f, n * sizeof(int));
    dis[st] = 0;
    while(true) {
        int u = -1, mindis = INF;
        for(int i = 1; i <= n; ++i) if(!vis[i])
            if(dis[i] < mindis) u = i, mindis = dis[i];
        if(u == -1) break;
        vis[u] = true;
        for(int i = 1; i <= n; ++i) if(!vis[i])
            dis[i] = min(dis[i], dis[u] + mat[u][i]);
    }
}

void build() {
    G.init(n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) if(i != j)
            if(dis[i] + mat[i][j] == dis[j]) G.add_edge(i, j, 1);
}

int main() {
    memset(mat, 0x3f, sizeof(mat));
    scanf("%d%d", &n, &m);
    for(int i = 0, u, v, c; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        mat[u][v] = mat[v][u] = c;
    }
    dijkstra(1, n);
    build();

    if(G.maxflow(1, n) >= 2) {
        FOR(_, 2) G.getPath();
    } else {
        puts("No solution");
    }
}
