#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 110;
const int MAXE = 3010;
const double INF = 1e100;
const double EPS = 1e-8;

inline int sgn(double x) {
    if(fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

struct SAP {
    int head[MAXN], dis[MAXN], cur[MAXN], pre[MAXN], gap[MAXN];
    int to[MAXE], next[MAXE];
    double flow[MAXE];
    int ecnt, n, st, ed;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, double c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
        //printf("%d->%d %lf\n", u, v, c);
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
                if(sgn(flow[p ^ 1]) && dis[v] > n) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    double Max_flow(int ss, int tt, int nn) {
        st = ss; ed = tt; n = nn;
        double ans = 0, minFlow = INF;
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
                if(sgn(flow[p]) && dis[u] == dis[v] + 1) {
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
                if(sgn(flow[p]) && dis[v] < minDis) {
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

int main() {
    int T, n, m, l, a, b;
    double x;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &l);
        G.init();
        int ss = n + m + 1, tt = n + m + 2;
        for(int i = 1; i <= n; ++i) {
            scanf("%lf", &x);
            G.add_edge(ss, i, log(x));
        }
        for(int i = 1; i <= m; ++i) {
            scanf("%lf", &x);
            G.add_edge(i + n, tt, log(x));
        }
        for(int i = 1; i <= l; ++i) {
            scanf("%d%d", &a, &b);
            G.add_edge(a, b + n, INF);
            //G.add_edge(b + n, a, INF);
        }
        printf("%.4f\n", exp(G.Max_flow(ss, tt, tt)));
    }
}
