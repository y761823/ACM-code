#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXV = 10010;
const int MAXE = 200010;
const int INF = 0x3f3f3f3f;

int head[MAXV], weight[MAXV], deg[MAXV], ecnt;
int to[MAXE], nxt[MAXE];
int n, m, T;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    memset(deg + 1, 0, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    deg[u]++, deg[v]++;
    to[ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

bool del[MAXV];
int stk[MAXV], top;

int fa[MAXV], cnt[MAXV];

int find_set(int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void merge(int x, int y) {
    x = find_set(x), y = find_set(y);
    if(x != y) {
        fa[x] = y;
        cnt[y] += cnt[x];
    }
}

LL solve() {
    memset(del + 1, 0, n * sizeof(bool));
    for(int i = 1; i <= n; ++i) {
        if(deg[i] <= 1) {
            stk[top++] = i;
            del[i] = true;
        }
    }
    while(top) {
        int u = stk[--top];
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(--deg[v] <= 1 && !del[v])
                del[stk[top++] = v] = true;
        }
    }

    for(int i = 1; i <= n; ++i) fa[i] = i, cnt[i] = 1;
    for(int u = 1; u <= n; ++u) if(!del[u]) {
        for(int p = head[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(!del[v]) merge(u, v);
        }
    }
    LL res = 0;
    for(int i = 1; i <= n; ++i)
        if(!del[i] && (cnt[find_set(i)] & 1)) res += weight[i];
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1; i <= n; ++i) scanf("%d", &weight[i]);
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        cout<<solve()<<endl;
    }
}
