#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 100010;

#define X first
#define Y second

typedef pair<int, int> PII;

int head[MAXN], rhead[MAXN];
int next[MAXM], rnext[MAXM], to[MAXM], rto[MAXM], cost[MAXM];
int ecnt;

void init() {
    ecnt = 1;
    memset(head, 0, sizeof(head));
    memset(rhead, 0, sizeof(rhead));
}

void add_edge(int u, int v, int c) {
    cost[ecnt] = c;
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt;
    rto[ecnt] = u; rnext[ecnt] = rhead[v]; rhead[v] = ecnt++;
}

int dis[MAXN];
bool vis[MAXN];

void dijkstra(int st, int n) {
    for(int i = 1; i <= n; ++i) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    priority_queue<PII> Q;
    dis[st] = 0; Q.push(make_pair(0, st));
    while(!Q.empty()) {
        int u = Q.top().Y; Q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(int p = rhead[u]; p; p = rnext[p]) {
            int v = rto[p];
            if(dis[v] > dis[u] + cost[p]) {
                dis[v] = dis[u] + cost[p];
                Q.push(make_pair(-dis[v], v));
            }
        }
    }
}

int a_star(int st, int ed, int n, int k) {
    priority_queue<PII> Q;
    Q.push(make_pair(-dis[st], st));
    while(!Q.empty()) {
        int u = Q.top().Y, c = -Q.top().X; Q.pop();
        if(u == ed && --k == 0) return c;
        for(int p = head[u]; p; p = next[p])
            Q.push(make_pair(-(c - dis[u] + cost[p] + dis[to[p]]), to[p]));
    }
    return -1;
}

int main() {
    int n, m, st, ed, k;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; ++i) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        scanf("%d%d%d", &st, &ed, &k);
        dijkstra(ed, n);
        if(dis[st] == INF) {
            printf("-1\n");
            continue;
        }
        if(st == ed) ++k;
        printf("%d\n", a_star(st, ed, n, k));
    }
}
