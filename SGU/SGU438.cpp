#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 53 * 105 * 2;
const int MAXE = MAXN * 100;
const int INF = 0x7fff7fff;

struct SAP {
    int head[MAXN];
    int gap[MAXN], dis[MAXN], pre[MAXN], cur[MAXN];
    int to[MAXE], flow[MAXE], next[MAXE];
    int ecnt, st, ed, n;

    void init(int ss, int tt, int nn) {
        memset(head, 0, sizeof(head));
        ecnt = 2;
        st = ss; ed = tt; n = nn;
    }

    void addEdge(int u,int v,int f) {
        to[ecnt] = v; flow[ecnt] = f; next[ecnt] = head[u]; head[u] = ecnt++;
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
                int v = to[p];
                if (dis[v] > n && flow[p ^ 1] > 0) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    int Max_flow() {
        int ans = 0, minFlow = INF,  u;
        for (int i = 0; i <= n; ++i){
            cur[i] = head[i];
            gap[i] = dis[i] = 0;
        }
        u = pre[st] = st;
        //gap[0] = n;
        bfs();
        while (dis[st] < n){
            bool flag = false;
            for (int &p = cur[u]; p; p = next[p]){
                int v = to[p];
                if (flow[p] > 0 && dis[u] == dis[v] + 1){
                    flag = true;
                    minFlow = min(minFlow, flow[p]);
                    pre[v] = u;
                    u = v;
                    if(u == ed){
                        ans += minFlow;
                        while (u != st){
                            u = pre[u];
                            flow[cur[u]] -= minFlow;
                            flow[cur[u] ^ 1] += minFlow;
                        }
                        minFlow = INF;
                    }
                    break;
                }
            }
            if (flag) continue;
            int minDis = n-1;
            for (int p = head[u]; p; p = next[p]){
                int v = to[p];
                if (flow[p] && dis[v] < minDis){
                    minDis = dis[v];
                    cur[u] = p;
                }
            }
            if (--gap[dis[u]] == 0) break;
            gap[dis[u] = minDis+1]++;
            u = pre[u];
        }
        return ans;
    }
} G;

const int MAX = 55;

struct Point {
    int x, y, c;
};

int dis2(const Point &a, const Point &b) {
    int xx = a.x - b.x, yy = a.y - b.y;
    return xx * xx + yy * yy;
}

int n, m, d, w;
Point rub[MAX];

#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define get_num(i, t) ((i - 1) * 2 * (mid - 1) + 2 * (t - 1) + 1)

void solve() {
    int left = 1, right = n + m + 1;
    while(left < right) {
        int mid = (left + right) >> 1;
        int ss = n * (mid - 1) * 2 + 1, st = ss + 1, tt = ss + 2;
        G.init(st, tt, tt);
        G.addEdge(st, ss, m);
        FOR(i, 1, n) {
            if(rub[i].y <= d) {
                FOR(t, 1, mid - 1) G.addEdge(ss, get_num(i, t), INF);
            }
            if(rub[i].y + d >= w) {
                FOR(t, 1, mid - 1) G.addEdge(get_num(i, t) + 1, tt, INF);
            }
        }
        FOR(i, 1, n) FOR(t, 1, mid - 1) {
            int num = get_num(i, t);
            G.addEdge(num, num + 1, rub[i].c);
            if(t < mid - 1) G.addEdge(num + 1, num + 2, INF);
        }
        FOR(i, 1, n) FOR(j, 1, n) {
            if(i == j || dis2(rub[i], rub[j]) > d * d) continue;
            FOR(t, 1, mid - 2) G.addEdge(get_num(i, t) + 1, get_num(j, t + 1), INF);
        }
        int ans = G.Max_flow();
        if(ans < m) left = mid + 1;
        else right = mid;
    }
    if(right == n + m + 1) puts("IMPOSSIBLE");
    else printf("%d\n", right);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &d, &w);
    FOR(i, 1, n) scanf("%d%d%d", &rub[i].x, &rub[i].y, &rub[i].c);
    FOR(i, 1, n) if(rub[i].c > m) rub[i].c = m;
    if(w <= d) printf("1\n");
    else solve();
}
