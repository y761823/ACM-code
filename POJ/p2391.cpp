#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 210;
const int MAXV = MAXN * 2;
const int MAXE = MAXV * MAXV;
const int INF = 0x7fffffff;

struct SAP {
    int head[MAXV], gap[MAXV], pre[MAXV], cur[MAXV], dis[MAXV];
    int to[MAXE], flow[MAXE], next[MAXE];
    int n, st, ed, ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
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
        st = ss, ed = tt, n = nn;
        int ans = 0, minFLow = INF, u;
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
                    minFLow = min(minFLow, flow[p]);
                    pre[v] = u;
                    u = v;
                    if(u == ed) {
                        ans += minFLow;
                        while(u != st) {
                            u = pre[u];
                            flow[cur[u]] -= minFLow;
                            flow[cur[u] ^ 1] += minFLow;
                        }
                        minFLow = INF;
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

LL mat[MAXN][MAXN], t;
int a[MAXN], b[MAXN];
int n, m, sum;

void floyd() {
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}

bool build(LL up) {
    G.init();
    int ss = 2 * n + 1, tt = 2 * n + 2;
    for(int i = 1; i <= n; ++i) {
        G.add_edge(ss, i, a[i]);
        G.add_edge(i + n, tt, b[i]);
        for(int j = 1; j <= n; ++j) {
            if(mat[i][j] > up) continue;
            G.add_edge(i, j + n, INF);
        }
    }
    int t = G.Max_flow(ss, tt, tt);
    return  t == sum;
}

LL solve() {
    LL l = 0, r = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
            if(mat[i][j] != 0x3f3f3f3f3f3f3f3fLL) r = max(r, mat[i][j]);
    if(!build(r)) return -1;
    while(l < r) {
        LL mid = (l + r) >> 1;
        if(build(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d%d", &a[i], &b[i]), sum += a[i];
    int u, v, d;
    memset(mat, 0x3f, sizeof(mat));
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &d);
        mat[u][v] = mat[v][u] = min(mat[u][v], (LL)d);
    }
    for(int i = 1; i <= n; ++i) mat[i][i] = 0;
    floyd();
    cout<<solve()<<endl;
}