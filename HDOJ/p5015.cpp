////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-14 18:36:01
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5015
////Problem Title: 
////Run result: Accept
////Run time:1171MS
////Run memory:312KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 14;
const int MOD = 10000007;

inline void update_add(int &a, LL b) {
    a += (b % MOD);
    if(a >= MOD) a -= MOD;
}

int T, n, m;

#define FOR(i, n) for(int i = 0; i <= n + 1; ++i)

struct Mat {
    int mat[MAXN][MAXN];
    void init() {
        clear();
        for(int i = 0; i <= n; ++i) mat[0][i] = 10;
        for(int i = 0; i <= n + 1; ++i) mat[n + 1][i] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = i; j <= n; ++j) mat[i][j] = 1;
    }
    void clear() {
        FOR(i, n) FOR(j, n) mat[i][j] = 0;
    }
    void one() {
        FOR(i, n) FOR(j, n) mat[i][j] = (i == j);
    }
    Mat operator * (const Mat &rhs) const {
        Mat res; res.clear();
        FOR(i, n) FOR(k, n) {
            FOR(j, n) update_add(res.mat[i][j], (LL)mat[i][k] * rhs.mat[k][j]);
        }
        return res;
    }
    void print() {
        FOR(i, n) {
            FOR(j, n) printf("%8d", mat[i][j]);
            puts("");
        }
    }
};

Mat power(Mat x, int p) {
    Mat res; res.one();
    while(p) {
        if(p & 1) res = res * x;
        x = x * x;
        p >>= 1;
    }
    return res;
}

int a[MAXN];
Mat res;

int solve() {
    a[0] = 23; a[n + 1] = 3;
    res.init();
    res = power(res, m);
    int ans = 0;
    FOR(i, n) {
        update_add(ans, (LL)a[i] * res.mat[i][n]);
    }
    return ans;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
}