#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 1010;

struct Mat {
    int c, r;
    int mat[MAXN][MAXN];
    void set(int rr, int cc) {
        r = rr;
        c = cc;
    }
    void read() {
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) scanf("%d", &mat[i][j]);
    }
};

int mul(const Mat &a, const Mat &b, int r, int c) {
    int ret = 0;
    for(int i = 0; i < a.c; ++i) ret += a.mat[r][i] * b.mat[i][c];
    return ret;
}

int n, p, m;
int ansr, ansc, ans;
LL sum[MAXN];
Mat a, b, c;

bool check() {
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < p; ++j) sum[i] += b.mat[i][j];
    for(int i = 0; i < n; ++i) {
        LL t1 = 0, t2 = 0;
        for(int j = 0; j < m; ++j) t1 += c.mat[i][j];
        for(int j = 0; j < m; ++j) t2 += a.mat[i][j] * sum[j];
        if(t1 != t2) {
            for(int j = 0; j < m; ++j) {
                int t = mul(a, b, i, j);
                if(t != c.mat[i][j]) {
                    ansr = i + 1; ansc = j + 1; ans = t;
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d%d", &n, &p, &m);
    a.set(n, p); b.set(p, m); c.set(n, m);
    a.read(); b.read(); c.read();
    if(check()) puts("Yes");
    else printf("No\n%d %d\n%d\n", ansr, ansc, ans);
}
