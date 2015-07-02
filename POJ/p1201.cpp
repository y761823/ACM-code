#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 50010;
const int MAXE = MAXV * 3;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int n, m;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
}

int dis[MAXV];
bool inque[MAXV];

int spfa() {
    queue<int> que; que.push(0);
    memset(dis + 1, 0x80, n * sizeof(int)); dis[0] = 0;
    memset(inque + 1, 0, n * sizeof(bool));
    while(!que.empty()) {
        int u = que.front(); que.pop();
        inque[u] = false;
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[v] < dis[u] + cost[p]) {
                dis[v] = dis[u] + cost[p];
                if(!inque[v]) {
                    inque[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dis[n];
}

int main() {
    init();
    scanf("%d", &m);
    for(int i = 0, a, b, c; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        add_edge(a, b + 1, c);
        n = max(n, b + 1);
    }
    for(int i = 1; i <= n; ++i) {
        add_edge(i - 1, i, 0);
        add_edge(i, i - 1, -1);
    }
    printf("%d\n", spfa());
}
