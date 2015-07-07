////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-22 12:11:46
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4571
////Problem Title: 
////Run result: Accept
////Run time:843MS
////Run memory:576KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MAXE = MAXN * MAXN;

int n, m, st, ed, T;
int val[MAXN], vis_c[MAXN];
int mat[MAXN][MAXN];

inline void update_min(int &a, const int &b) {
    if(a > b) a = b;
}

inline void update_max(int &a, const int &b) {
    if(a < b) a = b;
}

struct Solve {
    int head[MAXN], indeg[MAXN];
    int to[MAXE], next[MAXE], cost[MAXE];
    int ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        memset(indeg, 0, sizeof(indeg));
        ecnt = 1;
    }

    void add_edge(int u, int v, int c) {
        ++indeg[v];
        to[ecnt] = v; cost[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
    }

    int dp[MAXN][MAXN * 3];

    int solve() {
        memset(dp, -1, sizeof(dp));
        dp[n][0] = 0;
        queue<int> que; que.push(n);
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int i = 1; i <= T; ++i) update_max(dp[u][i], dp[u][i - 1]);
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                for(int i = 0; i <= T - cost[p]; ++i) {
                    if(dp[u][i] == -1) continue;
                    update_max(dp[v][i + cost[p]], dp[u][i] + val[v]);
                }
                if(--indeg[v] == 0) que.push(v);
            }
        }
        int ans = 0;
        mat[n][ed] = mat[st][ed];
        for(int i = 0; i <= n; ++i) if(T - mat[i][ed] >= 0)
            update_max(ans, dp[i][T - mat[i][ed]]);
        //printdp();
        return ans;
    }

    void printdp() {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j <= T; ++j) printf("%d ", dp[i][j]);
            printf("\n");
        }
    }

} G;

struct Original {
    void read() {
        memset(mat, 0x3f, sizeof(mat));
        for(int i = 0; i < n; ++i) mat[i][i] = 0;
        int u, v, c;
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &c);
            update_min(mat[u][v], c);
            update_min(mat[v][u], c);
        }
    }

    void floyd() {
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j) update_min(mat[i][j], mat[i][k] + mat[k][j]);
    }

    bool make_G() {
        floyd();
        if(mat[st][ed] > T) return false;
        G.init();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if(val[i] < val[j]) G.add_edge(i, j, mat[i][j] + vis_c[j]);
        for(int i = 0; i < n; ++i)
            G.add_edge(n, i, mat[st][i] + vis_c[i]);
        return true;
    }
} O;

int main() {
    int W;
    scanf("%d", &W);
    for(int w = 1; w <= W; ++w) {
        scanf("%d%d%d%d%d", &n, &m, &T, &st, &ed);
        for(int i = 0; i < n; ++i) scanf("%d", &vis_c[i]);
        for(int i = 0; i < n; ++i) scanf("%d", &val[i]);
        O.read();
        O.make_G();
        printf("Case #%d:\n%d\n", w, G.solve());
    }
}
