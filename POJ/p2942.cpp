#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXV = 1010;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

int pre[MAXV], lowlink[MAXV], dfs_clock;
int sccno[MAXV], scc_cnt;
int stk[MAXV], top;
bool mat[MAXV][MAXV], flag[MAXV];
int n, m;

int color[MAXV];
bool dfs_col(int u) {
    for(int v = 0; v < n; ++v) if(mat[u][v] && sccno[u] == sccno[v]) {
        if(color[v] == -1) {
            color[v] = !color[u];
            if(!dfs_col(v)) return false;
        } else {
            if(color[v] == color[u]) return false;
        }
    }
    return true;
}

void check(int st, int scc) {
    memset(color, -1, sizeof(color));
    color[st] = 0;
    if(!dfs_col(st)) {
        for(int i = 0; i < n; ++i)
            flag[i] |= (sccno[i] == scc);
    }
}

void dfs(int u, int f) {
    pre[u] = lowlink[u] = ++dfs_clock;
    stk[top++] = u;
    for(int v = 0; v < n; ++v) if(mat[u][v] && v != f) {
        if(!pre[v]) {
            dfs(v, u);
            lowlink[u] = min(lowlink[u], lowlink[v]);
            if(pre[u] == lowlink[v]) {
                scc_cnt++;
                while(true) {
                    int x = stk[--top];
                    sccno[x] = scc_cnt;
                    if(x == v) break;
                }
                sccno[u] = scc_cnt;
                check(u, scc_cnt);
                sccno[u] = 0;
            }
        } else lowlink[u] = min(lowlink[u], pre[v]);
    }
    if(pre[u] == lowlink[u]) {
        scc_cnt++;
        while(true) {
            int x = stk[--top];
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
        check(u, scc_cnt);
    }
}

int solve() {
    memset(pre, 0, n * sizeof(int));
    memset(lowlink, 0, n * sizeof(int));
    memset(sccno, -1, n * sizeof(int));
    memset(flag, 0, n * sizeof(bool));
    top = scc_cnt = dfs_clock = 0;
    for(int i = 0; i < n; ++i) if(!pre[i])
        dfs(i, -1);
    return n - accumulate(flag, flag + n, 0);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) mat[i][j] = (i != j);
        for(int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            a--, b--;
            mat[a][b] = mat[b][a] = false;
        }
        printf("%d\n", solve());
    }
}
