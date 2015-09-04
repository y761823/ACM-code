#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n + 2; ++i)

const int MAXN = 55;
const int MOD = 2015;

int T, n, m;

struct Mat {
    int a[MAXN][MAXN];
    void One() {
        REP(i, n) REP(j, n) a[i][j] = (i == j);
    }
    void Zero() {
        REP(i, n) REP(j, n) a[i][j] = 0;
    }
    Mat operator * (const Mat &rhs) const {
        Mat res; res.Zero();
        REP(k, n) {
            REP(i, n) REP(j, n)
                res.a[i][j] = (res.a[i][j] + a[i][k] * rhs.a[k][j]) % MOD;
        }
        return res;
    }
};

Mat power(Mat x, int p) {
    Mat res; res.One();
    while(p) {
        if(p & 1) res = res * x;
        x = x * x;
        p >>= 1;
    }
    return res;
}

Mat src;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        src.Zero();
        src.a[0][n + 1] = 1;
        for(int i = 1, k, t; i <= n; ++i) {
            scanf("%d", &k);
            while(k--) {
                scanf("%d", &t);
                src.a[i][t] = 1;
            }
            src.a[0][i] = 1;
            src.a[i][n + 1] = 1;
        }
        src.a[n + 1][n + 1] = 1;
        src = power(src, m);
        printf("%d\n", accumulate(src.a[0], src.a[0] + n + 2, 0) % MOD);
    }
}
