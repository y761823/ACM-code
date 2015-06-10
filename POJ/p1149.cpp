#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 110;
const int MAXE = MAXN * MAXN;
const int INF = 0x7fffffff;

struct SAP {
    int head[MAXN], gap[MAXN], pre[MAXN], dis[MAXN], cur[MAXN];
    int next[MAXE], to[MAXE], flow[MAXE];
    int ecnt, n, st, ed;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    void bfs() {
        queue<int> que; que.push(ed);
        memset(dis, 0x3f, sizeof(dis));
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
        st = ss, ed = tt, n = nn;
        int ans = 0, minFlow = INF, u;
        for(int i = 0; i <= n; ++i) {
            cur[i] = head[i];
            gap[i] = 0;
        }
        bfs();
        u = pre[st] = st;
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
} G;

int n, m;
int last[1010];
int a[1010], b[110];

int main() {
    scanf("%d%d", &m, &n);
    G.init();
    int ss = n + 1, tt = n + 2;
    for(int i = 1; i <= m; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) {
        int x, b;
        scanf("%d", &b);
        for(int j = 1; j <= b; ++j) {
            scanf("%d", &x);
            if(last[x] == 0) G.add_edge(ss, i, a[x]);
            else G.add_edge(last[x], i, INF);
            last[x] = i;
        }
        scanf("%d", &x); G.add_edge(i, tt, x);
    }
    printf("%d\n", G.Max_flow(ss, tt, tt));
}
