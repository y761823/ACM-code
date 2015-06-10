#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long LL;

const int MAXN = 5010;
const int MAXE = 200010;
const LL INF = 0x3fff3fff3fff3fffLL;

struct SAP {
    int head[MAXN], dis[MAXN], gap[MAXN], cur[MAXN], pre[MAXN];
    int to[MAXE], next[MAXE];
    LL flow[MAXE];
    int ecnt, n, st, ed;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, LL c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
        //printf("%d->%d %I64d\n", u, v, c);
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

    LL Max_flow(int ss, int tt, int nn) {
        st = ss; ed = tt; n = nn;
        LL ans = 0, minFlow = INF;
        for(int i = 0; i <= n; ++i) {
            cur[i] = head[i];
            gap[i] = 0;
        }
        int u = pre[st] = st;
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

    int cnt_S() {
        memset(dis, 0, sizeof(dis));
        int * vis = dis, ret = 0;
        queue<int> que; que.push(st);
        vis[st] = 1;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && !vis[v]) {
                    vis[v] = 1;
                    ++ret;
                    que.push(v);
                }
            }
        }
        return ret;
    }
} G;

int main() {
    int n, m, a, b;
    LL x, sum = 0;
    scanf("%d%d", &n, &m);
    int ss = 0, tt = n + 1;
    G.init();
    for(int i = 1; i <= n; ++i) {
        scanf("%I64d", &x);
        if(x > 0) sum += x, G.add_edge(ss, i, x);
        if(x < 0) G.add_edge(i, tt, -x);
    }
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", &a, &b);
        G.add_edge(a, b, INF);
    }
    LL ans1 = sum - G.Max_flow(ss, tt, tt);
    int ans2 = G.cnt_S();
    printf("%d %I64d\n", ans2, ans1);
}
