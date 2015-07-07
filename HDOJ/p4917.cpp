////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-02 22:28:40
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4917
////Problem Title: 
////Run result: Accept
////Run time:140MS
////Run memory:8520KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 44;
const int MAXD = 1 << 21;
const int MOD = 1e9 + 7;

#define mod(x) ((x) % MOD)

LL c[MAXN][MAXN];
bool mat[MAXN][MAXN];
bool vis[MAXN];
int id[MAXN], pre[MAXN];
int n, m, k;

inline void update_add(int &a, int b) {
    a += b;
    if(a >= MOD) a -= MOD;
}

int dp[MAXD];

int calc() {
    memset(dp, 0, (1 << k) * sizeof(int));
    memset(pre, 0, sizeof(pre));
    for(int i = 0; i < k; ++i)
        for(int j = 0; j < k; ++j) if(mat[id[i]][id[j]]) pre[j] |= (1 << i);
    dp[0] = 1;
    for(int state = 0, ed = (1 << k); state < ed; ++state) if(dp[state]) {
        for(int i = 0; i < k; ++i) if(!((state >> i) & 1) && (state & pre[i]) == pre[i])
            update_add(dp[state | (1 << i)], dp[state]);
    }
    return dp[(1 << k) - 1];
}

void dfs(int u) {
    vis[id[k++] = u] = true;
    for(int v = 1; v <= n; ++v) if(!vis[v]) {
        if(mat[u][v] || mat[v][u]) dfs(v);
    }
}

int solve() {
    memset(vis, 0, sizeof(vis));
    int cnt = 0, ans = 1;
    for(int i = 1; i <= n; ++i) if(!vis[i]) {
        k = 0;
        dfs(i);
        cnt += k;
        ans = mod(c[cnt][k] * mod((LL)ans * calc()));
    }
    return ans;
}

int main() {
    c[0][0] = 1;
    for(int i = 1; i <= 40; ++i) {
        c[i][0] = 1;
        for(int j = 1; j <= i; ++j) c[i][j] = mod(c[i - 1][j - 1] + c[i - 1][j]);
    }

    while(scanf("%d%d", &n, &m) != EOF) {
        memset(mat, 0, sizeof(mat));
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            mat[u][v] = true;
        }
        printf("%d\n", solve());
    }
}
