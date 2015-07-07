////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-03 21:20:18
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4433
////Problem Title: 
////Run result: Accept
////Run time:203MS
////Run memory:812KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 1010;

int a[MAXN], b[MAXN], n;
int dp[MAXN][11][11];
char s[MAXN];

inline int make(int x) {
    if(x < 0) x += 10;
    if(x > 9) x -= 10;
    return x;
}

inline void update_min(int &a, const int &b) {
    if(a > b) a = b;
}

inline int calc(int x, int y) {
    if(x > y) y += 10;
    return y - x;
}

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[1][a[1]][0] = 0;
    for(int i = 1; i <= 9; ++i) {
        update_min(dp[1][make(a[1] + i)][0], i);
        update_min(dp[1][make(a[1] - i)][0], i);
    }
    for(int i = 2; i <= n; ++i) {
        for(int x = 0; x <= 9; ++x) {
            for(int y = 0; y <= 9; ++y) {
                int k = calc(a[i], x);
                for(int p = 0; p <= k; ++p) {
                    for(int q = 0; q <= p; ++q)
                        update_min(dp[i][x][y], dp[i - 1][make(y - p)][make(b[i - 2] - q)] + k);
                }

                k = 10 - k;
                for(int p = 0; p <= k; ++p) {
                    for(int q = 0; q <= p; ++q)
                        update_min(dp[i][x][y], dp[i - 1][make(y + p)][make(b[i - 2] + q)] + k);
                }
            }
        }
    }
    return dp[n][b[n]][b[n - 1]];
}

int main() {
    while(scanf("%s", s) != EOF) {
        n = strlen(s);
        for(int i = 0; i < n; ++i) a[i + 1] = s[i] - '0';
        scanf("%s", s);
        for(int i = 0; i < n; ++i) b[i + 1] = s[i] - '0';
        printf("%d\n", solve());
    }
}
