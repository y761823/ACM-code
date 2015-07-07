////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-13 20:48:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5001
////Problem Title: 
////Run result: Accept
////Run time:1125MS
////Run memory:3772KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXV = 55;
const int MAXE = MAXV * MAXV;
const int MAXD = 10010;

int head[MAXV], outdeg[MAXV], ecnt;
int to[MAXE], next[MAXE];
int n, m, T, d;

void init() {
    memset(head + 1, -1, n * sizeof(int));
    memset(outdeg + 1, 0, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v) {
    outdeg[u]++;
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
    outdeg[v]++;
    to[ecnt] = u; next[ecnt] = head[v]; head[v] = ecnt++;
}

double dp[MAXD][MAXV];

double solve(int fail) {
    for(int i = 1; i <= n; ++i)
        dp[0][i] = 1.0 / n;
    for(int t = 0; t < d; ++t) {
        for(int u = 1; u <= n; ++u) dp[t + 1][u] = 0;
        for(int u = 1; u <= n; ++u) if(u != fail) {
            double tmp = dp[t][u] / outdeg[u];
            for(int p = head[u]; ~p; p = next[p]) {
                int v = to[p];
                dp[t + 1][v] += tmp;
            }
        }
    }
    double res = 0;
    for(int i = 1; i <= n; ++i) if(i != fail) {
        res += dp[d][i];
    }
    return res;
}

void solve() {
    for(int i = 1; i <= n; ++i) {
        printf("%.10f\n", solve(i));
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &d);
        init();
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        solve();
    }
}