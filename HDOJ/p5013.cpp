////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-14 11:44:33
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5013
////Problem Title: 
////Run result: Accept
////Run time:2796MS
////Run memory:9112KB
//////////////////System Comment End//////////////////
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 17;

double dp[MAXV][1 << MAXV];
double p[MAXV][MAXV];
int h[MAXV][MAXV];
int n, m;

double solve() {
    double res = 0, tmp1, tmp2;
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j) res += p[i][j] * h[i][j];
    for(int j = 0, ed = (1 << m); j < n - 1; ++j) {
        for(int s = 1; s < ed; ++s) {
            tmp1 = 1, tmp2 = 0;
            for(int i = 0; i < m; ++i)
                if((s >> i) & 1) tmp1 *= p[i][1], tmp2 += h[i][j + 1];
                else tmp1 *= (1 - p[i][1]);
            dp[0][s] = tmp1 * __builtin_popcount(s) * tmp2;
        }

        for(int k = 1; k <= m; ++k) {
            for(int s = 1; s < (1 << m); ++s) {
                dp[k][s] = dp[k - 1][s];
                if((s >> (k - 1)) & 1) dp[k][s] += dp[k - 1][s - (1 << (k - 1))];
            }
        }

        for(int s = 1; s < ed; ++s) {
            tmp1 = tmp2 = 1;
            for(int i = 0; i < m; ++i) {
                if((s >> i) & 1) tmp1 *= p[i][j];
                else tmp1 *= (1 - p[i][j]), tmp2 *= (1 - p[i][1]);
            }
            if(tmp2 > 1e-20) res += dp[m][s] / tmp2 / __builtin_popcount(s) * tmp1;
        }
    }
    return res;
}

int main() {
    while(scanf("%d%d", &m, &n) != EOF) {
        for(int i = 0; i < m; ++i) scanf("%lf", &p[i][1]);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) scanf("%d", &h[i][j]);
        for(int i = 0; i < m; ++i) {
            p[i][0] = 1;
            for(int j = 2; j <= n; ++j) p[i][j] = p[i][j - 1] * p[i][1];
        }
        printf("%.10f\n", solve());
    }
}
