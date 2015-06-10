#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 510;
const int MAXE = 2010;
const int INF = 0x7fff7fff;

int head[MAXN];
int to[MAXE], next[MAXE], cost[MAXE];
int ecnt, n, m, k, C;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
    //printf("%d--%d %d\n", u, v, c);
}

int dis[MAXN];
bool inque[MAXN];

void SPFA(int st) {
    memset(dis, 0x3f, sizeof(dis));
    memset(inque, false, sizeof(inque));
    queue<int> que; que.push(st);
    dis[st] = 0; inque[st] = true;
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
}

int pos[MAXN];

void solve() {
    SPFA(1);
    int cnt = 0;
    for(int i = 1; i <= C; ++i) cnt += (dis[pos[i]] <= k);
    printf("%d\n", cnt);
    for(int i = 1; i <= C; ++i)
        if(dis[pos[i]] <= k) printf("%d\n", i);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &C, &k);
    init();
    while(m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u, v, c);
    }
    for(int i = 1; i <= C; ++i) scanf("%d", &pos[i]);
    solve();
}
