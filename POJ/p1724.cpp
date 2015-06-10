#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 110;
const int MAXE = 10010;
const int INF = 0x3f3f3f3f;

int head[MAXV], dis[MAXE][MAXV];
int to[MAXE], next[MAXE], cost[MAXE], val[MAXE];
int n, m, k, ecnt;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c, int _v) {
    to[ecnt] = v; cost[ecnt] = c; val[ecnt] = _v;
    next[ecnt] = head[u]; head[u] = ecnt++;
}

struct Graph {
    int head[MAXV], dis[MAXV], vis[MAXV];
    int to[MAXE], next[MAXE], cost[MAXE];
    int ecnt;

    void init() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    }

    void dijkstra(int st) {
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[st] = 0;
        for(int x = 1; x < n; ++x) {
            int u = -1;
            for(int i = 1; i <= n; ++i) if(!vis[i])
                if(u == -1 || dis[i] < dis[u]) u = i;
            vis[u] = true;
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(dis[u] + cost[p] < dis[v]) dis[v] = dis[u] + cost[p];
            }
        }
    }
} G;

struct Node {
    int f, g, u, c;
    Node() {}
    Node(int f, int g, int u, int c): f(f), g(g), u(u), c(c) {}
    bool operator < (const Node &rhs) const{
        return f + g > rhs.f + rhs.g;
    }
};

int astar(int st, int ed) {
    G.dijkstra(ed);
    priority_queue<Node> que;
    que.push(Node(0, G.dis[st], st, 0));
    memset(dis, 0x3f, sizeof(dis));
    dis[0][st] = 0;
    while(!que.empty()) {
        Node t = que.top(); que.pop();
        if(t.u == ed) return t.f;
        for(int p = head[t.u]; ~p; p = next[p]) {
            int &v = to[p], x = t.c + cost[p];
            if(x <= k) {
                if(dis[x][v] <= t.f + val[p]) continue;
                dis[x][v] = t.f + val[p];
                que.push(Node(t.f + val[p], G.dis[v], v, x));
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d%d%d", &k, &n, &m);
    G.init();
    init();
    while(m--) {
        int u, v, c, _v;
        scanf("%d%d%d%d", &u, &v, &_v, &c);
        add_edge(u, v, c, _v);
        G.add_edge(v, u, _v);
    }
    printf("%d\n", astar(1, n));
}
