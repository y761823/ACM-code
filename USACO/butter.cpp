/*
ID: y7618231
LANG: C++
TASK: butter
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 810;
const int MAXE = 1455 * 2;
const int INF = 0x3f3f3f3f;

int head[MAXV], ecnt;
int to[MAXE], next[MAXE], cost[MAXE];
int pos[MAXV];
int n, p, c;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

int dis[MAXV], sum[MAXV];

void spfa(int st) {
    priority_queue<pair<int, int> > que;
    memset(dis + 1, 0x3f, n * sizeof(int));
    que.push(make_pair(dis[st] = 0, st));
    while(!que.empty()) {
        pair<int, int> tmp = que.top(); que.pop();
        int u = tmp.second;
        if(-tmp.first != dis[u]) continue;
        for(int p = head[u]; ~p; p = next[p]) {
            int v = to[p];
            if(dis[u] + cost[p] < dis[v]) {
                dis[v] = dis[u] + cost[p];
                que.push(make_pair(-dis[v], v));
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        sum[i] += dis[i];
}

int main() {
#ifndef OYK_JUDGE
    freopen("butter.in", "r", stdin); freopen("butter.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d", &p, &n, &c);
    for(int i = 0; i < p; ++i) scanf("%d", &pos[i]);
    init();
    for(int _ = 0, x, y, z; _ < c; ++_) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
    }
    for(int i = 0; i < p; ++i)
        spfa(pos[i]);
    printf("%d\n", *min_element(sum + 1, sum + n + 1));
}
