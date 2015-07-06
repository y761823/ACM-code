#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 25;
const int MAXE = 3010;
const int INF = 0x3fff3fff;

struct SAP {
    int head[MAXN], dis[MAXN], pre[MAXN], cur[MAXN], gap[MAXN];
    int to[MAXE], next[MAXE], flow[MAXE];
    int n, st, ed, ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
        //printf("%d->%d flow = %d\n", u, v, c);
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
                        if(minFlow == INF) return INF;//no ans
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
                if(flow[p] && minDis > dis[v]) {
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

char s[5];
int n, ss, tt, T, c, x;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &tt);
        ss = n;
        G.init();
        for(int i = 0; i < n; ++i) {
            scanf("%s%d", s, &c);
            while(c--) {
                scanf("%d", &x);
                G.add_edge(i, x, INF);
                G.add_edge(x, i, 1);
            }
            if(s[0] == 'I') G.add_edge(ss, i, INF);
        }
        int ans = G.Max_flow(ss, tt, ss);
        if(ans == INF) puts("PANIC ROOM BREACH");
        else printf("%d\n", ans);
    }
}
