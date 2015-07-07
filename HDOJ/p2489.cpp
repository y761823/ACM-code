////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-14 20:29:20
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2489
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:328KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 18;
const int INF = 0x3fff3fff;

int mat[MAXN][MAXN];
int weight[MAXN];
int n, m;
bool use[MAXN], vis[MAXN];
int dis[MAXN];

int prim(int st) {
    memset(vis, 0, sizeof(vis));
    vis[st] = true;
    for(int i = 1; i <= n; ++i) dis[i] = mat[st][i];
    int ret = 0;
    for(int cnt = 1; cnt < m; ++cnt) {
        int u, min_dis = INF;
        for(int i = 1; i <= n; ++i)
            if(use[i] && !vis[i] && dis[i] < min_dis) u = i, min_dis = dis[i];
        ret += min_dis;
        vis[u] = true;
        for(int i = 1; i <= n; ++i)
            if(use[i] && !vis[i] && dis[i] > mat[u][i]) dis[i] = mat[u][i];
    }
    return ret;
}

bool ans[MAXN];
int ans_pw, ans_ew;

void dfs(int dep, int cnt, int sum_pw) {
    if(cnt == m) {
        int sum_ew = prim(dep - 1);
        if(ans_ew == INF || ans_ew * sum_pw > ans_pw * sum_ew) {//ans_ew/ans_pw > sum_ew/sum_pw
            for(int i = 1; i <= n; ++i) ans[i] = use[i];
            ans_ew = sum_ew; ans_pw = sum_pw;
        }
        return ;
    }
    if(dep == n + 1) return ;
    use[dep] = true;
    dfs(dep + 1, cnt + 1, sum_pw + weight[dep]);
    use[dep] = false;
    dfs(dep + 1, cnt, sum_pw);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; ++i) scanf("%d", &weight[i]);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) scanf("%d", &mat[i][j]);
        }
        ans_ew = INF; ans_pw = 1;
        dfs(1, 0, 0);
        bool flag = false;
        for(int i = 1; i <= n; ++i) {
            if(!ans[i]) continue;
            if(flag) printf(" ");
            else flag = true;
            printf("%d", i);
        }
        printf("\n");
    }
}
