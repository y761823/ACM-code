////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-25 18:44:12
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4034
////Problem Title: 
////Run result: Accept
////Run time:218MS
////Run memory:412KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXV = 110;
const int MAXE = MAXV * MAXV;
const int INF = 0x3f3f3f3f;

int mat[MAXV][MAXV], dis[MAXV][MAXV];
int n, cnt, T;

#define REP(i, n) for(int i = 1; i <= n; ++i)
void floyd() {
    REP(k, n) REP(i, n) REP(j, n)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

int solve() {
    floyd();
    int ans = 0;
    REP(i, n) REP(j, n) {
        if(mat[i][j] > dis[i][j]) return -1;
        bool flag = false;
        REP(k, n) if(i != k && k != j) {
            if(dis[i][k] + dis[k][j] == dis[i][j]) flag = true;
        }
        ans += flag;
    }
    return n * n - n - ans;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        cnt = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &mat[i][j]);
                dis[i][j] = mat[i][j];
            }
        }
        printf("Case %d: ", t);
        int res = solve();
        if(res == -1) puts("impossible");
        else printf("%d\n", res);
    }
}