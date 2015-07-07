////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-25 20:05:17
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4832
////Problem Title: 
////Run result: Accept
////Run time:750MS
////Run memory:12252KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int MOD = 9999991;
const int MAXN = 1010;

int f[] = {-2, -1, 1, 2};

int n, m, k, x0, y0, T;
int dpx[MAXN][MAXN], dpy[MAXN][MAXN];
int sumx[MAXN], sumy[MAXN];
int c[MAXN][MAXN];

void initc() {
    int n = 1000;
    c[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        c[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
}

bool check(int x, int n) {
    return 1 <= x && x <= n;
}

int solve() {
    memset(dpx, 0, sizeof(dpx));
    dpx[0][x0] = 1;
    for(int p = 1; p <= k; ++p) {
        for(int i = 1; i <= n; ++i) {
            for(int v = 0; v < 4; ++v) {
                int t = i + f[v];
                if(check(t, n)) dpx[p][t] = (dpx[p][t] + dpx[p - 1][i]) % MOD;
            }
        }
    }

    memset(sumx, 0, sizeof(sumx));
    for(int i = 0; i <= k; ++i) {
        for(int j = 1; j <= n; ++j) sumx[i] = (sumx[i] + dpx[i][j]) % MOD;
    }

    memset(dpy, 0, sizeof(dpy));
    dpy[0][y0] = 1;
    for(int p = 1; p <= k; ++p) {
        for(int i = 1; i <= m; ++i) {
            for(int v = 0; v < 4; ++v) {
                int t = i + f[v];
                if(check(t, m)) dpy[p][t] = (dpy[p][t] + dpy[p - 1][i]) % MOD;
            }
        }
    }

    memset(sumy, 0, sizeof(sumy));
    for(int i = 0; i <= k; ++i) {
        for(int j = 1; j <= m; ++j) sumy[i] = (sumy[i] + dpy[i][j]) % MOD;
    }

    LL ans = 0;
    for(int i = 0; i <= k; ++i)
        ans = (ans + LL(c[k][i]) * sumx[i] % MOD * sumy[k - i]) % MOD;

    return (int)ans;
}

int main() {
    initc();
    //cout<<c[1000][1000]<<endl;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d%d", &n, &m, &k, &x0, &y0);
        printf("Case #%d:\n", t);
        printf("%d\n", solve());
    }
}
