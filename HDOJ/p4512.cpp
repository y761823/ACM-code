////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-02 14:59:20
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4512
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:472KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 210;

int dp[MAXN][MAXN];
int p[MAXN];
int n, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n; ++j) dp[i][j] = 0;
        for(int i = 1; i <= n; ++i) {
            int t = 0;
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i - 1][j];
                if(p[i] > p[n - j + 1]) t = max(t, dp[i][j]);
                if(p[i] == p[n - j + 1]) dp[i][j] = t + 1;
            }
        }
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            ans = max(ans, 2 * dp[i][n - i + 1] - 1);
        for(int i = 1; i < n; ++i)
            ans = max(ans, 2 * dp[i][n - i]);
        printf("%d\n", ans);
    }
}
