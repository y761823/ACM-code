#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 110;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

struct DINIC {
    int head[MAXV], cur[MAXV], ecnt;
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

    int dis[MAXV];

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
                a -= f;
                outflow += f;
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

int lower[MAXV], upper[MAXV];
int s[MAXV], e[MAXV];
int res[MAXV];
bool vis[MAXV];
int n, m1, m2;

bool solve() {
    memset(vis + 1, 0, n * sizeof(bool));
    int ss = 2 * n + 1, tt = ss + 1;
    for(int i = 1; i <= n; ++i) {
        res[i] = -1;
        for(int j = lower[i]; j <= upper[i]; ++j) if(!vis[j]) {
            if(i < s[j] || e[j] < i) continue;
            vis[j] = true;
            G.init(tt);
            for(int k = i + 1; k <= n; ++k) {
                G.add_edge(ss, k, 1);
                for(int l = lower[k]; l <= upper[k]; ++l) if(!vis[l]) {
                    if(k < s[l] || e[l] < k) continue;
                    G.add_edge(k, n + l, 1);
                }
            }
            for(int l = 1; l <= n; ++l) if(!vis[l])
                G.add_edge(n + l, tt, 1);
            if(G.maxflow(ss, tt) == n - i) {
                res[i] = j;
                break;
            }
            vis[j] = false;
        }
        if(res[i] == -1) return false;
    }
    for(int i = 1; i <= n; ++i) {
        printf("%d", res[i]);
        putchar(i < n ? ' ' : '\n');
    }
    return true;
}

int main() {
    while(scanf("%d%d%d", &n, &m1, &m2) != EOF) {
        for(int i = 1; i <= n; ++i) {
            s[i] = lower[i] = 1;
            e[i] = upper[i] = n;
        }
        for(int i = 0, a, b, c; i < m1; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            s[c] = max(s[c], a);
            e[c] = min(e[c], b);
            for(int j = a; j <= b; ++j)
                lower[j] = max(lower[j], c);
        }
        for(int i = 0, a, b, c; i < m2; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            s[c] = max(s[c], a);
            e[c] = min(e[c], b);
            for(int j = a; j <= b; ++j)
                upper[j] = min(upper[j], c);
        }
        if(!solve()) puts("-1");
    }
}
