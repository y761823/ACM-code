#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MAXE = MAXN * MAXN;

int head[MAXN];
int to[MAXE], next[MAXE], cost[MAXE];
int ecnt, n, st, ed;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
}

int dis[MAXN];
bool inque[MAXN];

int SPFA() {
    memset(dis, 0x3f, sizeof(dis));
    memset(inque, false, sizeof(inque));
    dis[st] = 0; inque[st] = true;
    queue<int> que; que.push(st);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        inque[u] = false;
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(dis[u] + cost[p] < dis[v]) {
                dis[v] = dis[u] + cost[p];
                if(!inque[v]) {
                    que.push(v);
                    inque[v] = true;
                }
            }
        }
    }
    if(dis[ed] > n) return -1;
    return dis[ed];
}

int main() {
    scanf("%d%d%d", &n, &st, &ed);
    init();
    for(int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        for(int j = 0; j < k; ++j) {
            int x;
            scanf("%d", &x);
            add_edge(i + 1, x, j != 0);
        }
    }
    printf("%d\n", SPFA());
}
