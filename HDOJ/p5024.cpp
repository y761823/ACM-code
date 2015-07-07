////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-20 20:52:01
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5024
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:680KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110;

int fx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int fy[] = {1, 1, 0, -1, -1, -1, 0, 1};

char mat[MAXN][MAXN];
int dp[MAXN][MAXN][8];
int n;

int solve() {
    memset(dp, 0, sizeof(dp));
    for(int i = n; i >= 1; --i) {
        for(int j = n; j >= 1; --j) {
            if(mat[i][j] == '#') continue;
            for(int k = 0; k < 4; ++k) {
                int pi = i + fx[k], pj = j + fy[k];
                dp[i][j][k] = dp[pi][pj][k] + 1;
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(mat[i][j] == '#') continue;
            for(int k = 4; k < 8; ++k) {
                int pi = i + fx[k], pj = j + fy[k];
                dp[i][j][k] = dp[pi][pj][k] + 1;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(mat[i][j] == '#') continue;
            for(int k = 0; k < 8; ++k) {
                ans = max(ans, dp[i][j][k] + dp[i][j][(k + 2) % 8] - 1);
            }
        }
    }
    return ans;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
        printf("%d\n", solve());
    }
}