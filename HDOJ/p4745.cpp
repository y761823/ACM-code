////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-16 19:29:13
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4745
////Problem Title: 
////Run result: Accept
////Run time:125MS
////Run memory:4248KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int dp[MAXN][MAXN], a[MAXN];
int pre[MAXN], next[MAXN];
int n;

int dfs(int l, int r) {
    if(dp[l][r]) return dp[l][r];
    if(pre[l] == r) return dp[l][r] = 1 + (a[l] == a[r]);
    if(a[l] == a[r]) dp[l][r] = dfs(pre[l], next[r]) + 2;
    else dp[l][r] = max(dfs(pre[l], r), dfs(l, next[r]));
    return dp[l][r];
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        if(n < 3) printf("%d\n", n);
        else {
            memset(dp, 0, sizeof(dp));
            for(int i = 0; i < n; ++i)
                pre[i] = (i - 1 + n) % n, next[i] = (i + 1) % n, dp[i][i] = 1;
            int ans = 0;
            for(int i = 0; i < n; ++i)
                ans = max(ans, max(dfs(pre[i], i), dfs(pre[i], next[i]) + 1));
            printf("%d\n", ans);
        }
    }
}
