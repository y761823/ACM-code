#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const int MAXE = 50010;

int outdeg[MAXN], pre[MAXN], lowlink[MAXN], sum[MAXN];
int head[MAXN], sccno[MAXN], ecnt, scc_cnt;
int to[MAXE], next[MAXE];
int n, m, dfs_clock;
int stk[MAXN], top;

void init() {
    memset(sum, 0, sizeof(sum));
    memset(head, 0, sizeof(head));
    memset(outdeg, 0, sizeof(outdeg));
    ecnt = 1;
    scc_cnt = 0;
    dfs_clock = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
}

void dfs(int u) {//tarjan
    pre[u] = lowlink[u] = ++dfs_clock;
    stk[++top] = u;
    for(int p = head[u]; p; p = next[p]) {
        int &v = to[p];
        if(!pre[v]) {
            dfs(v);
            if(lowlink[u] > lowlink[v]) lowlink[u] = lowlink[v];
        } else if(!sccno[v]) {
            if(lowlink[u] > pre[v]) lowlink[u] = pre[v];
        }
    }
    if(lowlink[u] == pre[u]) {
        ++scc_cnt;
        while(true) {
            int x = stk[top--];
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}

int solve() {
    for(int i = 1; i <= n; ++i)
        if(!pre[i]) dfs(i);
    for(int u = 1; u <= n; ++u) {
        ++sum[sccno[u]];
        for(int p = head[u]; p; p = next[p]) {
            int &v = to[p];
            if(sccno[u] == sccno[v]) continue;
            ++outdeg[sccno[u]];
        }
    }
    int ans = 0;
    for(int i = 1; i <= scc_cnt; ++i)
        if(outdeg[i] == 0) {
            if(ans == 0) ans = sum[i];
            else return 0;
        }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    while(m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
    }
    printf("%d\n", solve());
}
