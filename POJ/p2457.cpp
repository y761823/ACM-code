#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 1010;
const int MAXE = 50010;

int head[MAXN];
int to[MAXE], next[MAXE], cost[MAXE];
int ecnt, n, k;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    //printf("%d--%d %d\n", u, v, c);
}

int dis[MAXN], pre[MAXN];
bool inque[MAXN];

int SPFA(int st) {
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
                    pre[v] = u;
                    inque[v] = true;
                }
            }
        }
    }
    if(dis[k] > k) return -1;
    return dis[k] + 1;
}

void print(int x) {
    if(x != 1) print(pre[x]);
    printf("%d\n", x);
}

int main() {
    init();
    scanf("%d%d", &n, &k);
    while(n--) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v, 1);
    }
    int ans = SPFA(1);
    printf("%d\n", ans);
    if(ans > 0) print(k);
}
