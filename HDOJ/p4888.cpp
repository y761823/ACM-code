////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-05 20:00:14
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4888
////Problem Title: 
////Run result: Accept
////Run time:218MS
////Run memory:4764KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 410;
const int MAXV = MAXN << 1;
const int MAXE = 2 * MAXN * MAXN;
const int INF = 0x3f3f3f3f;

struct ISAP {
    int head[MAXV], cur[MAXV], gap[MAXV], dis[MAXV], pre[MAXV];
    int to[MAXE], next[MAXE], flow[MAXE];
    int n, ecnt, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    void bfs() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        queue<int> que; que.push(ed);
        dis[ed] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            gap[dis[u]]++;
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                if(flow[p ^ 1] && dis[u] + 1 < dis[v]) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    int max_flow(int ss, int tt) {
        st = ss, ed = tt;
        int ans = 0, minFlow = INF;
        for(int i = 0; i <= n; ++i) {
            cur[i] = head[i];
            gap[i] = 0;
        }
        bfs();
        int u = pre[st] = st;
        while(dis[st] < n) {
            bool flag = false;
            for(int &p = cur[u]; ~p; p = next[p]) {
                int v = to[p];
                if(flow[p] && dis[u] == dis[v] + 1) {
                    flag = true;
                    minFlow = min(minFlow, flow[p]);
                    pre[v] = u;
                    u = v;
                    if(u == ed) {
                        ans += minFlow;
                        while(u != st) {
                            u = pre[u];
                            flow[cur[u]] -= minFlow;
                            flow[cur[u] ^ 1] += minFlow;
                        }
                        minFlow = INF;
                    }
                    break;
                }
            }
            if(flag) continue;
            int minDis = n - 1;
            for(int p = head[u]; ~p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && dis[v] < minDis) {
                    minDis = dis[v];
                    cur[u] = p;
                }
            }
            if(--gap[dis[u]] == 0) break;
            ++gap[dis[u] = minDis + 1];
            u = pre[u];
        }
        return ans;
    }

    int stk[MAXV], top;
    bool sccno[MAXV], vis[MAXV];

    bool dfs(int u, int f, bool flag) {
        vis[u] = true;
        stk[top++] = u;
        for(int p = head[u]; ~p; p = next[p]) if(flow[p]) {
            int v = to[p];
            if(v == f) continue;
            if(!vis[v]) {
                if(dfs(v, u, flow[p ^ 1])) return true;
            } else if(!sccno[v]) return true;
        }
        if(!flag) {
            while(true) {
                int x = stk[--top];
                sccno[x] = true;
                if(x == u) break;
            }
        }
        return false;
    }

    bool acycle() {
        memset(sccno + 1, 0, n * sizeof(bool));
        memset(vis + 1, 0, n * sizeof(bool));
        top = 0;
        return dfs(ed, 0, 0);
    }
} G;

int row[MAXN], col[MAXN];
int mat[MAXN][MAXN];
int n, m, k, ss, tt;

void solve() {
    int sumr = accumulate(row + 1, row + n + 1, 0);
    int sumc = accumulate(col + 1, col + m + 1, 0);
    if(sumr != sumc) {
        puts("Impossible");
        return ;
    }
    int res = G.max_flow(ss, tt);
    if(res != sumc) {
        puts("Impossible");
        return ;
    }
    if(G.acycle()) {
        puts("Not Unique");
    } else {
        puts("Unique");
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j < m; ++j) printf("%d ", G.flow[mat[i][j]]);
            printf("%d\n", G.flow[mat[i][m]]);
        }
    }
}

int main() {
    while(scanf("%d%d%d", &n, &m, &k) != EOF) {
        for(int i = 1; i <= n; ++i) scanf("%d", &row[i]);
        for(int i = 1; i <= m; ++i) scanf("%d", &col[i]);
        ss = n + m + 1, tt = n + m + 2;
        G.init(tt);
        for(int i = 1; i <= n; ++i) G.add_edge(ss, i, row[i]);
        for(int i = 1; i <= m; ++i) G.add_edge(n + i, tt, col[i]);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                mat[i][j] = G.ecnt ^ 1;
                G.add_edge(i, n + j, k);
            }
        }
        solve();
    }
}
