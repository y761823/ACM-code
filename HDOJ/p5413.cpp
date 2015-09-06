#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <bitset>
#include <stack>
using namespace std;

const int MAXV = 20010;
const int MAXE = 100010;

int head[MAXV], indeg[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
bitset<MAXV> bit[MAXV];
stack<int> fa[MAXV];
int n, m, T;

void init() {
    for(int i = 1; i <= n; ++i) {
        bit[i].reset();
        head[i] = -1;
        indeg[i] = 0;
    }
    ecnt = 0;
}

void add_edge(int u, int v) {
    indeg[v]++;
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
}

int que[MAXV], cnt;

int solve() {
    cnt = 0;
    for(int i = 1; i <= n; ++i)
        if(indeg[i] == 0) que[cnt++] = i;
    
    for(int i = 0; i < n; ++i) {
        int u = que[i];
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            fa[v].push(u);
            if(--indeg[v] == 0)
                que[cnt++] = v;
        }
    }
    
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int v = que[i];
        while(!fa[v].empty()) {
            int u = fa[v].top(); fa[v].pop();
            res += bit[v][u - 1];
            bit[v] |= bit[u];
        }
        bit[v].set(v - 1);
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        printf("%d\n", solve());
    }
}
