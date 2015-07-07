////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-04-04 20:19:26
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3686
////Problem Title: 
////Run result: Accept
////Run time:171MS
////Run memory:5304KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

typedef pair<int, int> PII;

const int MAXV = 10010;
const int MAXE = 200010;

int ans[MAXV];
vector<PII> query[MAXV << 1];

struct SccGraph {
    int head[MAXV << 1], fa[MAXV << 1], ecnt;
    bool vis[MAXV << 1];
    int to[MAXE << 1], next[MAXE << 1];
    int dep[MAXV << 1];

    void init(int n) {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(vis, 0, sizeof(bool) * (n + 1));
        for(int i = 1; i <= n; ++i) fa[i] = i;
        ecnt = 0;
    }

    int find_set(int x) {
        return fa[x] == x ? x : fa[x] = find_set(fa[x]);
    }

    void add_edge(int u, int v) {
        to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    void lca(int u, int f, int deep) {
        dep[u] = deep;
        for(int p = head[u]; ~p; p = next[p]) {
            int &v = to[p];
            if(v == f || vis[v]) continue;
            lca(v, u, deep + 1);
            fa[v] = u;
        }
        vis[u] = true;
        for(vector<PII>::iterator it = query[u].begin(); it != query[u].end(); ++it) {
            if(vis[it->first]) {
                ans[it->second] = (dep[u] + dep[it->first] - 2 * dep[find_set(it->first)]) / 2;
            }
        }
    }
} G;

int head[MAXV], lowlink[MAXV], pre[MAXV], ecnt, dfs_clock;
int sccno[MAXV], scc_cnt;
int to[MAXE], next[MAXE], scc_edge[MAXE];
bool vis[MAXE], iscut[MAXV];
int stk[MAXE], top;
int n, m, q;

void init() {
    memset(head, -1, sizeof(int) * (n + 1));
    memset(pre, 0, sizeof(int) * (n + 1));
    memset(iscut, 0, sizeof(bool) * (n + 1));
    memset(vis, 0, sizeof(bool) * (2 * m));
    ecnt = scc_cnt = dfs_clock = 0;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

void tarjan(int u, int f) {
    pre[u] = lowlink[u] = ++dfs_clock;
    int child = 0;
    for(int p = head[u]; ~p; p = next[p]) {
        if(vis[p]) continue;
        vis[p] = vis[p ^ 1] = true;
        stk[++top] = p;
        int &v = to[p];
        if(!pre[v]) {
            ++child;
            tarjan(v, u);
            lowlink[u] = min(lowlink[u], lowlink[v]);\
            if(pre[u] <= lowlink[v]) {
                iscut[u] = true;
                ++scc_cnt;
                while(true) {
                    int t = stk[top--];
                    scc_edge[t] = scc_edge[t ^ 1] = scc_cnt;
                    if(t == p) break;
                }
            }
        } else lowlink[u] = min(lowlink[u], pre[v]);
    }
    if(f < 1 && child == 1) iscut[u] = false;
}

void build() {
    G.init(scc_cnt);
    for(int p = 0; p != ecnt; ++p) {
        int &v = to[p];
        if(iscut[v]) G.add_edge(sccno[v], scc_edge[p]);
    }
}

void solve() {
    for(int i = 1; i <= n; ++i)
        if(!pre[i]) tarjan(i, 0);
    for(int u = 1; u <= n; ++u)
        if(iscut[u]) sccno[u] = ++scc_cnt;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        init();
        for(int i = 1; i <= m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        solve();
        build();
        for(int i = 0; i <= scc_cnt; ++i) query[i].clear();
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            x = scc_edge[x * 2 - 2]; y = scc_edge[y * 2 - 2];
            query[x].push_back(make_pair(y, i));
            query[y].push_back(make_pair(x, i));
        }
        for(int i = 1; i <= scc_cnt; ++i) if(!G.vis[i]) G.lca(i, 0, 0);
        for(int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    }
}
