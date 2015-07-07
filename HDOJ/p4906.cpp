////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-01 16:41:29
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4906
////Problem Title: 
////Run result: Accept
////Run time:1156MS
////Run memory:86564KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 22;
const int MAXM = (1 << 20) + 5;
const int MOD = 1e9 + 7;

#define mod(x) ((x) % MOD)

int dp[MAXN][MAXM];
int n, k, L, T;

inline void update_add(int &a, int b) {
    a += b;
    a -= MOD & ~((a >= MOD) - 1);
}

int solve() {
    for(int i = 1; i <= n; ++i)
        memset(dp[i], 0, (1 << k) * sizeof(int));
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int v = 0, ed = 1 << k; v < ed; ++v) if(dp[i - 1][v]) {
            LL t = 1 + max(0, L - k);
            update_add(dp[i][v], mod(dp[i - 1][v] * t));
            for(int j = 1; j <= k; ++j) {
                int nv = (v | (v << j) | (1 << (j - 1))) & ((1 << k) - 1);
                update_add(dp[i][nv], dp[i - 1][v]);
            }
        }
    }
    int res = 0;
    for(int v = 1 << (k - 1), ed = 1 << k; v < ed; ++v)
        update_add(res, dp[n][v]);
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &k, &L);
        printf("%d\n", solve());
    }
}
