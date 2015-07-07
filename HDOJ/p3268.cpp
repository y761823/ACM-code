////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-16 16:10:24
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3268
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:304KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 25;
const int MAXE = 2 * MAXN * MAXN;
const int INF = 0x3fff3fff;

struct Node {
    int id, val;
    void read() {
        scanf("%d%d", &id, &val);
    }
    bool operator < (const Node &rhs) const {
        return id < rhs.id;
    }
};

Node a[MAXN];
int dis[MAXN], head[MAXN], vis[MAXN];
int next[MAXE], to[MAXE], cost[MAXE];
int ecnt, n, m;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 1;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
}

void Dijkstra(int st, int n) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[st] = 0;
    for(int x = 1; x < n; ++x) {
        int u, minDis = INF;
        for(int i = 0; i < n; ++i)
            if(!vis[i] && dis[i] < minDis) u = i, minDis = dis[i];
        vis[u] = true;
        for(int p = head[u]; p; p = next[p]) {
            int v = to[p];
            if(!vis[v] && dis[v] > dis[u] + cost[p]) dis[v] = dis[u] + cost[p];
        }
    }
}

void solve() {
    init();
    scanf("%d", &m);
    while(m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u, v, c);
    }
    int st = 0;
    for(int i = 1; i <= n; ++i) add_edge(st, i, a[i].val - 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(i == j || a[i].val != a[j].val) continue;
            add_edge(i, j, 0);
            add_edge(j, i, 0);
        }
    }
    Dijkstra(st, n + 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) a[i].read();
        sort(a + 1, a + n + 1);
        solve();
        for(int i = 1; i <= n; ++i) printf("%d %d\n", i, dis[i]);
        int ans = 0;
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(i == j) continue;
                for(int k = 1; k <= n; ++k) {
                    if(k == i || k == j) continue;
                    if(vis[k] || dis[i] + dis[j] != dis[k]) continue;
                    vis[k] = true;
                    ++ans;
                }
            }
        }
        printf("%d\n", ans);
    }
}
