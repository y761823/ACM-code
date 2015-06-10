#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 1010;
const int MAXE = 4010;

int head[MAXN];
int to[MAXE], next[MAXE], cost[MAXE];
int ecnt, n, m;

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

int SPFA(int st, int ed) {
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
    return dis[ed];
}

int main() {
    scanf("%d%d", &m, &n);
    init();
    while(m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u, v, c);
    }
    printf("%d\n", SPFA(1, n));
}
