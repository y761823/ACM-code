#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 110;
const int MAXE = MAXN * MAXN * 2;
const int INF = 0x3fff3fff;

struct SAP {
    int head[MAXN], gap[MAXN], dis[MAXN], pre[MAXN], cur[MAXN];
    int to[MAXE], next[MAXE], flow[MAXE], cap[MAXE];
    int n, ecnt, st, ed;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; cap[ecnt] = c; flow[ecnt] = 0; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cap[ecnt] = 0; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
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
                if(cap[p ^ 1] > flow[p ^ 1] && dis[v] > n) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    int Max_flow(int ss, int tt, int nn) {
        st = ss, ed = tt, n = nn;
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
                if(cap[p] > flow[p] && dis[u] == dis[v] + 1) {
                    flag = true;
                    minFlow = min(minFlow, cap[p] - flow[p]);
                    pre[v] = u;
                    u = v;
                    if(u == ed) {
                        ans += minFlow;
                        while(u != st) {
                            u = pre[u];
                            flow[cur[u]] += minFlow;
                            flow[cur[u] ^ 1] -= minFlow;
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
                if(cap[p] > flow[p] && dis[v] < minDis) {
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
} G;

int n, m, a, b, c, d, x;
int f[MAXN], down[MAXE], id[MAXE];

int main() {
    scanf("%d%d", &n, &m);
    G.init();
    int sum = 0;
    int ss = n + 1, tt = n + 2;
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if(d == 1) {
            f[a] -= c;
            f[b] += c;
            down[i] = c;
        }
        else {
            id[i] = G.ecnt;
            G.add_edge(a, b, c);
        }
    }
    for(int i = 1; i <= n; ++i) {
        if(f[i] > 0) sum += f[i], G.add_edge(ss, i, f[i]);
        else G.add_edge(i, tt, -f[i]);
    }
    sum -= G.Max_flow(ss, tt, tt);
    int ans_id = G.ecnt;
    G.add_edge(n, 1, INF);
    if(sum == G.Max_flow(ss, tt, tt)) {
        printf("%d\n", G.flow[ans_id]);
        for(int i = 1; i < m; ++i) {
            if(down[i]) printf("%d ", down[i]);
            else printf("%d ", G.flow[id[i]]);
        }
        if(down[m]) printf("%d\n", down[m]);
        else printf("%d\n", G.flow[id[m]]);
    }
    else printf("Impossible\n");
    return 0;
}
