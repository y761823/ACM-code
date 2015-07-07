////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-23 23:26:48
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3687
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 59;

int n, m, T;
int a[MAXN][MAXN];
int change[210];

int solve() {
    memset(change, 0, sizeof(change));
    int inc = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j)
            if(a[i][j] - j + 2 > 1) ++change[a[i][j] - j + 2];
            else ++inc;
    }
    int now = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) now += abs(a[i][j] - j);
    int ret = now;
    for(int i = 2; i <= m - n + 1; ++i) {
        inc += change[i];
        now += 2 * inc - n * n;
        ret = min(ret, now);
    }
    return ret;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; ++i) a[i][0] = 0;
        for(int i = 0, ed = n * n, x, y; i != ed; ++i) {
            scanf("%d%d", &x, &y);
            a[x][++a[x][0]] = y;
        }
        for(int i = 1; i <= n; ++i)
            sort(a[i] + 1, a[i] + 1 + n);
        printf("%d\n", solve());
    }
}
