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
int ecnt, n;

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
                    inque[v] = true;
                }
            }
        }
    }
    int ret = 0;
    for(int i = 1; i <= n; ++i) ret = max(ret, dis[i]);
    return ret;
}

int main() {
    init();
    scanf("%d", &n);
    char s[13];
    for(int i = 2; i <= n; ++i)
        for(int j = 1; j < i; ++j) {
            scanf("%s", s);
            if(*s != 'x') add_edge(i, j, atoi(s));
        }
    printf("%d\n", SPFA(1));
}
