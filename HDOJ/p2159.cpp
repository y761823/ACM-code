////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:07:27
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2159
////Problem Title: 
////Run result: Accept
////Run time:921MS
////Run memory:21252KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 2310;

int cost[MAXN], v[MAXN];
int d[MAXN][MAXN], w[MAXN], c[MAXN], val[MAXN];
int n, m, k, s, exp;
int N, ans;

void init() {
    n = 0;
    for(int i = 0; i < N; ++i) {
        int cnt = s;
        for(int j = 1; j <= cnt; j <<= 1) {
            w[++n] = cost[i] * j;
            val[n] = v[i] * j;
            c[n] = j;
            cnt -= j;
        }
        if(cnt == 0) continue;
        w[++n] = cost[i] * cnt;
        val[n] = v[i] * cnt;
        c[n] = cnt;
    }
}

void dp() {
    memset(d, 0, sizeof(d));
    ans = -1;
    for(int i = 1; i <= n; ++i) {
        for(int j = s; j >= 1; --j) {
            for(int k = m; k >= w[i]; --k) {
                if(c[i] > j) continue;
                if(d[k][j] < d[k - w[i]][j - c[i]] + val[i]) {
                    d[k][j] = d[k - w[i]][j - c[i]] + val[i];
                    if(d[k][j] >= exp && m - k > ans) {
                        ans = m - k;
                        //printf("%d %d %d %d %d\n", ans, d[k][j], k, j, i);
                    }
                }
            }
        }
    }
}

int main() {
    while(scanf("%d%d%d%d", &exp, &m, &N, &s) != EOF) {
        for(int i = 0; i < N; ++i) scanf("%d%d", &v[i], &cost[i]);
        init();
        dp();
        printf("%d\n", ans);
    }
}