#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 410;
const int MAXE = 30010;
const int INF = 0x3fff3fff;

struct SAP {
    int head[MAXN], dis[MAXN], cur[MAXN], pre[MAXN], gap[MAXN];
    int to[MAXE], flow[MAXE], next[MAXE];
    int ecnt, n, st, ed;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
        //printf("%d->%d, flow = %d\n", u, v, c);
    }

    void bfs() {
        memset(dis, 0x3f, sizeof(dis));
        queue<int> que; que.push(ed);
        dis[ed] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            ++gap[dis[u]];
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p ^ 1] && dis[v] > n) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    int Max_flow(int ss, int tt, int nn) {
        st = ss; ed = tt; n = nn;
        int ans = 0, minFlow = INF, u;
        for(int i = 0; i <= n; ++i) {
            cur[i] = head[i];
            gap[i] = 0;
        }
        u = pre[st] = st;
        bfs();
        while(dis[st] < n) {
            bool flag = false;
            for(int &p = cur[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && dis[u] == dis[v] + 1) {
                    flag = true;
                    minFlow = min(minFlow, flow[p]);
                    pre[v] = u;
                    u = v;
                    if(u == ed) {
                        ans += minFlow;
                        while(u != st) {
                            u = pre[u];
                            flow[cur[u]] -= minFlow;
                            flow[cur[u] ^ 1] += minFlow;
                        }
                        minFlow = INF;
                    }
                    break;
                }
            }
            if(flag) continue;
            int minDis = n - 1;
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && dis[v] < minDis) {
                    minDis = dis[v];
                    cur[u] = p;
                }
            }
            if(--gap[dis[u]] == 0) break;
            ++gap[dis[u] = minDis + 1];
            u = pre[u];
        }
        return ans;
    }

    bool vis[MAXN];

    bool link(int x, int y) {
        memset(vis, 0, sizeof(vis));
        queue<int> que; que.push(x);
        vis[x] = true;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && !vis[v]) {
                    if(v == y) return true;
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
        return false;
    }

    void add_flow(int x, int y) {
        memset(vis, 0, sizeof(vis));
        queue<int> que; que.push(x);
        vis[x] = true;
        bool flag = false;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && !vis[v]) {
                    pre[v] = p;
                    if(v == y) {
                        flag = true;
                        break;
                    }
                    vis[v] = true;
                    que.push(v);
                }
            }
            if(flag) break;
        }
        int u = y;
        while(u != x) {
            flow[pre[u]] -= 1;
            flow[pre[u] ^ 1] += 1;
            u = to[pre[u] ^ 1];
        }
    }
} G;

int mat[MAXN][MAXN];
int edge_id[MAXN];
int n, ss, tt;

int main() {
    scanf("%d%d%d", &n, &ss, &tt);
    G.init();
    for(int i = 1; i <= n; ++i) {
        edge_id[i] = G.ecnt;
        if(i == ss || i == tt) G.add_edge(i, i + n, INF);
        else G.add_edge(i, i + n, 1);
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &mat[i][j]);
            if(i != j && mat[i][j]) G.add_edge(i + n, j, INF);
        }
    }
    if(mat[ss][tt]) {
        puts("NO ANSWER!");
        return 0;
    }
    int ans = G.Max_flow(ss, tt + n, n + n);
    printf("%d\n", ans);
    if(ans == 0) return 0;
    bool flag = false;
    for(int i = 1; i <= n; ++i) {
        if(G.flow[edge_id[i]] == 0 && !G.link(i, i + n)) {
            if(flag) printf(" ");
            flag = true;
            printf("%d", i);
            G.flow[edge_id[i]] = G.flow[edge_id[i] ^ 1] = 0;
            G.add_flow(i, ss);
            G.add_flow(tt, i + n);
        }
    }
    printf("\n");
}
