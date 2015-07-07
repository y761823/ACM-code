////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-07 19:09:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4815
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:3460KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 400010;

LL dp[MAXN];
int a[44];
int n, m, T;
double p;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%lf", &n, &p);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        memset(dp, 0, sizeof(dp));
        int sum = accumulate(a, a + n, 0);
        dp[0] = 1;
        for(int i = 0; i < n; ++i)
            for(int j = sum; j >= a[i]; --j)
                dp[j] += dp[j - a[i]];
        for(int i = 1; i <= sum; ++i) dp[i] += dp[i - 1];
        LL k = ceil((1LL << n) * p - 1e-10);
        LL ans = lower_bound(dp, dp + sum + 1, k) - dp;
        printf("%I64d\n", ans);
    }
}
