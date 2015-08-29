#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXV = 10010;
const int MAXE = 100010;

int head[MAXV], cur[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
int stk[MAXE], top;
int n, m;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

void dfs(int u) {
    int &p = cur[u];
    while(p != -1) {
        int v = to[p];
        p = nxt[p];
        dfs(v);
    }
    printf("%d\n", u);
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    for(int i = 0, u, v; i < m; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    memcpy(cur + 1, head + 1, n * sizeof(int));
    dfs(1);
}
