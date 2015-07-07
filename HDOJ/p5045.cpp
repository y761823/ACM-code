////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-27 23:34:57
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5045
////Problem Title: 
////Run result: Accept
////Run time:78MS
////Run memory:8400KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 12;
const int MAXS = 1024;
const int MAXM = 1024;

double p[MAXN][MAXM];
double dp[MAXS][MAXM];
int T, n, m;

void update_max(double &a, double b) {
    if(a < b) a = b;
}

double solve() {
    int sum = 1 << n;
    for(int i = 0; i <= m; ++i)
        for(int st = 0; st < sum; ++st) dp[i][st] = -1;
    dp[0][0] = 0;
    for(int i = 0; i < m; ++i) {
        for(int st = 0; st < sum; ++st) {
            if(dp[i][st] == -1) continue;
            int new_st = (st == sum - 1) ? 0 : st;
            for(int t = 0; t < n; ++t) {
                if((new_st >> t) & 1) continue;
                update_max(dp[i + 1][new_st | (1 << t)], dp[i][st] + p[t][i + 1]);
            }
        }
    }
    double ans = 0;
    for(int st = 0; st < sum; ++st)
        update_max(ans, dp[m][st]);
    return ans;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%lf", &p[i][j]);
        printf("Case #%d: %.5f\n", t, solve());
    }
}