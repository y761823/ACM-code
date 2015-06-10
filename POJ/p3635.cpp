#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 1010;
const int MAXE = 20010;
const int MAXP = 110;

int head[MAXV], val[MAXV], ecnt;
int to[MAXE], next[MAXE], cost[MAXE];
int n, m, q;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

struct Node {
    int u, c, cost;
    Node(int u, int c, int cost): u(u), c(c), cost(cost) {}
    bool operator < (const Node &rhs) const {
        return cost > rhs.cost;
    }
};

int dis[MAXV][MAXP];

int SPFA(int st, int ed, int c) {
    priority_queue<Node> que;
    memset(dis, 0x7f, sizeof(dis));
    que.push(Node(st, 0, 0));
    dis[st][0] = 0;
    while(!que.empty()) {
        Node t = que.top(); que.pop();
        int u = t.u;
        if(t.cost != dis[u][t.c]) continue;
        if(u == ed) return t.cost;
        if(t.c < c && dis[u][t.c + 1] > t.cost + val[u]) {
            dis[u][t.c + 1] = t.cost + val[u];
            que.push(Node(u, t.c + 1, t.cost + val[t.u]));
        }
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(cost[p] > t.c || dis[v][t.c - cost[p]] <= t.cost) continue;
            dis[v][t.c - cost[p]] = t.cost;
            que.push(Node(v, t.c - cost[p], t.cost));
        }
    }
    return -1;
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    for(int i = 0; i < n; ++i) scanf("%d", &val[i]);
    while(m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u, v, c);
    }
    scanf("%d", &q);
    while(q--) {
        int st, ed, c;
        scanf("%d%d%d", &c, &st, &ed);
        int ans = SPFA(st, ed, c);
        if(ans == -1) puts("impossible");
        else printf("%d\n", ans);
    }
}
