#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 0x7fff7fff;
const int MAX = 25;
const int MAXN = MAX * MAX;
const int MAXE = 10 * MAXN;

struct Dinic {
    int head[MAXN], cur[MAXN], dis[MAXN];
    int to[MAXE], next[MAXE], cap[MAXE], flow[MAXE];
    int n, st, ed, ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; cap[ecnt] = c; flow[ecnt] = 0; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cap[ecnt] = 0; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    bool bfs() {
        memset(dis, 0, sizeof(dis));
        queue<int> que; que.push(st);
        dis[st] = 1;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; p; p = next[p]) {
                int v = to[p];
                if(!dis[v] && cap[p] > flow[p]) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                    if(v == ed) return true;
                }
            }
        }
        return dis[ed];
    }

    int dfs(int u, int a) {
        if(u == ed || a == 0) return a;
        int outflow = 0, f;
        for(int &p = cur[u]; p; p = next[p]) {
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

    int Maxflow(int ss, int tt, int nn) {
        st = ss; ed = tt; n = nn;
        int ans = 0;
        while(bfs()) {
            for(int i = 0; i <= n; ++i) cur[i] = head[i];
            ans += dfs(st, INF);
        }
        return ans;
    }
} G;

int r[MAX], w[MAX];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &r[i]);
    int max_score = w[1] + r[1], node_cnt = n, game_cnt = 0;
    for(int i = 2; i <= n; ++i)
        if(max_score < w[i]) {puts("NO"); return 0;}
    G.init();
    int ss = 1;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) {
        int x; scanf("%d", &x);
        if(i == 1 || i >= j || x == 0) continue;
        game_cnt += x;
        G.add_edge(ss, ++node_cnt, x);
        G.add_edge(node_cnt, i, INF);
        G.add_edge(node_cnt, j, INF);
    }
    int tt = ++node_cnt;
    for(int i = 2; i <= n; ++i) G.add_edge(i, tt, max_score - w[i]);
    if(G.Maxflow(ss, tt, node_cnt) == game_cnt) puts("YES");
    else puts("NO");
}
