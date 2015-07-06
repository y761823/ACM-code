#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 510;
const int MAXE = 10010;

int head[MAXN];
int to[MAXE], next[MAXE];
int n, k, ecnt;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 1;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
}

bool vis[MAXN];
int link[MAXN];

bool dfs(int u) {
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(vis[v]) continue;
        vis[v] = true;
        if(!link[v] || dfs(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;
}

int solve() {
    int ret = 0;
    for(int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        ret += dfs(i);
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &k);
    init();
    for(int i = 1; i <= k; ++i) {
        int r, c;
        scanf("%d%d", &r, &c);
        add_edge(r, c);
    }
    printf("%d\n", solve());
}
