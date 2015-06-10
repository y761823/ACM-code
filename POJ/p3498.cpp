#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 222;
const int MAXE = MAXN * MAXN * 2;
const int INF = 0x3f3f3f3f;

struct SAP {
    int head[MAXN], dis[MAXN], gap[MAXN], pre[MAXN], cur[MAXN];
    int to[MAXE], next[MAXE], flow[MAXE], cap[MAXE];
    int st, ed, n, ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int f) {
        to[ecnt] = v; cap[ecnt] = f; flow[ecnt] = 0; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; cap[ecnt] = 0; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
        //printf("%d->%d cap=%d\n", u, v, f);
    }

    void bfs() {
        memset(dis, 0x3f, sizeof(dis));
        queue<int> que; que.push(ed);
        dis[ed] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            ++gap[dis[u]];
            for(int p = head[u]; p; p = next[p]) {
                int v = to[p];
                if(dis[v] > n && cap[p ^ 1]) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    int Maxflow(int ss, int tt, int nn) {
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
                int v = to[p];
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
                int v = to[p];
                if(cap[p] > flow[p] && dis[v] < minDis) {
                    minDis = dis[v];
                    cur[u] = p;
                }
            }
            if(--gap[dis[u]] == 0) break;
            gap[dis[u] = minDis + 1]++;
            u = pre[u];
        }
        return ans;
    }
} G;

struct Point {
    int x, y, n, m;
    void read() {
        scanf("%d%d%d%d", &x, &y, &n, &m);
    }
};

double dist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n, ss, tt;
int ans[110], cnt;
double d;
Point p[110];

void make_graph() {
    ss = 2 * n + 1, tt = ss + 1;
    G.init();
    for(int i = 1; i <= n; ++i)
        if(p[i].n) G.add_edge(ss, 2 * i - 1, p[i].n);
    for(int i = 1; i <= n; ++i) G.add_edge(2 * i - 1, 2 * i, p[i].m);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(i == j || dist(p[i], p[j]) > d) continue;
            G.add_edge(i * 2, j * 2 - 1, INF);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%lf", &n, &d);
        for(int i = 1; i <= n; ++i) p[i].read();
        int sum = 0;
        for(int i = 1; i <= n; ++i) sum += p[i].n;
        make_graph();
        cnt = 0;
        for(int i = 1; i <= n; ++i) {
            G.add_edge(i * 2 - 1, tt, INF);
            memset(G.flow, 0, sizeof(G.flow));
            if(sum == G.Maxflow(ss, tt, tt)) ans[++cnt] = i - 1;
            G.cap[G.ecnt - 2] = 0;
        }
        if(cnt == 0) puts("-1");
        else {
            for(int i = 1; i < cnt; ++i) printf("%d ", ans[i]);
            printf("%d\n", ans[cnt]);
        }
    }
}
