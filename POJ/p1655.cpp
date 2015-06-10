#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 20010;
const int MAXE = 40010;
const int INF = 0x7fff7fff;

int head[MAXN], size[MAXN], maxSize[MAXN], f[MAXN];
int to[MAXE], next[MAXE];
int n, ecnt;

void init() {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u) {
    maxSize[u] = 0;
    size[u] = 1;
    for(int p = head[u]; ~p; p = next[p]) {
        int &v = to[p];
        if(v == f[u]) continue;
        f[v] = u;
        dfs(v);
        size[u] += size[v];
        maxSize[u] = max(maxSize[u], size[v]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        init();
        scanf("%d", &n);
        int u, v;
        for(int i = 1; i < n; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        dfs(1);
        int pos, maxd = INF;
        for(int i = 1; i <= n; ++i) {
            if(max(maxSize[i], n - size[i]) < maxd) {
                pos = i;
                maxd = max(maxSize[i], n - size[i]);
            }
        }
        printf("%d %d\n", pos, maxd);
    }
}
