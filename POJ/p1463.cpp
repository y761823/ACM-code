#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1510;
const int MAXE = MAXN << 1;

int head[MAXN];
int to[MAXE], next[MAXE];
int n, ecnt;

void init() {
    memset(head, 0, sizeof(head));
    ecnt = 2;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

int link[MAXN], dep[MAXN];
bool vis[MAXN];

bool dfs(int u) {
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(vis[v]) continue;
        vis[v] = true;
        if(!~link[v] || dfs(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        init();
        memset(dep, 0, sizeof(dep));
        for(int i = 0; i < n; ++i) {
            int a, b, c;
            scanf("%d:(%d)", &a, &b);
            while(b--) {
                scanf("%d", &c);
                dep[c] = dep[a] + 1;
                add_edge(a, c);
            }
        }
        int ans = 0;
        memset(link, 255, sizeof(link));
        for(int i = 0; i < n; ++i) {
            if(dep[i] & 1) continue;
            memset(vis, 0, sizeof(vis));
            if(dfs(i)) ++ans;
        }
        printf("%d\n", ans);
    }
}
