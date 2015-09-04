#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long LL;

const int MAXV = 100010;
const int MAXE = 200010;

int head[MAXV], ecnt;
int to[MAXE], nxt[MAXE], cost[MAXE];
int query[10];
LL cnt[10];
int T, n, Q;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int c) {
    to[ecnt] = v; cost[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cost[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

LL hashset[131072];
int offset;

void dfs(int u, int f) {
    hashset[offset]++;
    for(int i = 0; i < Q; ++i)
        cnt[i] += hashset[query[i] ^ offset];
    for(int p = head[u]; ~p; p = nxt[p]) {
        int v = to[p];
        if(v != f) {
            offset ^= cost[p];
            dfs(v, u);
            offset ^= cost[p];
        }
    }
}

void solve() {
    memset(hashset, 0, sizeof(hashset));
    offset = 0;
    dfs(1, 0);
    for(int i = 0; i < Q; ++i)
        printf("%I64d\n", cnt[i]);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        init();
        for(int i = 1, u, v, c; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &c);
            add_edge(u, v, c);
        }
        scanf("%d", &Q);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < Q; ++i)
            scanf("%d", &query[i]);
        solve();
    }
}
