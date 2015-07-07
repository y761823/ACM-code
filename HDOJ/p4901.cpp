////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-01 00:17:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4901
////Problem Title: 
////Run result: Accept
////Run time:2250MS
////Run memory:12760KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 1030;
const int MOD = 1e9 + 7;

int xordp[MAXN][MAXN], anddp[MAXN][MAXN];
int dp[MAXN][MAXN];
int a[MAXN], n, T;

inline int mod(LL x) {
    return x % MOD;
}

inline void update_add(int &a, int b) {
    a = mod(a + b);
}

int solve() {
    memset(dp, 0, sizeof(dp));
    memset(xordp, 0, sizeof(xordp));
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < 1024; ++j) {
            update_add(dp[i][j ^ a[i]], dp[i - 1][j]);
            update_add(dp[i][j], dp[i - 1][j]);
        }
        update_add(dp[i][a[i]], 1);

        for(int j = 0; j < 1024; ++j)
            update_add(xordp[i][j ^ a[i]], dp[i - 1][j]);
        update_add(xordp[i][a[i]], 1);
    }

    memset(anddp, 0, sizeof(anddp));
    for(int i = n; i >= 1; --i) {
        update_add(anddp[i][a[i]], 1);
        for(int j = 0; j < 1024; ++j) {
            update_add(anddp[i][j & a[i]], anddp[i + 1][j]);
            update_add(anddp[i][j], anddp[i + 1][j]);
        }
    }

    int res = 0;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < 1024; ++j) {
            update_add(res, mod((LL)xordp[i][j] * anddp[i + 1][j]));
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
}
