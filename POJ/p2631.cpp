#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXV = 10010;
const int MAXE = 20010;

int head[MAXV];
int to[MAXE], next[MAXE], cost[MAXE];
int n, ecnt;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; next[ecnt] = head[v]; head[v] = ecnt++;
}

int dfs(int u, int f, int &ans) {
    int maxdep = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f) continue;
        int tmp = dfs(v, u, ans) + cost[p];
        ans = max(ans, maxdep + tmp);
        maxdep = max(tmp, maxdep);
    }
    return maxdep;
}

int main() {
    init();
    n = 1;
    int u, v, c;
    while(scanf("%d%d%d", &u, &v, &c) != EOF) {
        add_edge(u, v, c);
        ++n;
    }
    int ans = 0;
    dfs(1, 0, ans);
    printf("%d\n", ans);
}
