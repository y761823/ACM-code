#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100010;

int T, n, m, k;

double sqr(double x) {
    return x * x;
}

double calc(int i, int j) {
    double a = sqr((i - 1) * m) + sqr((n - i) * m) + sqr(n * (j - 1)) + sqr(n * (m - j));
    double b = sqr((i - 1) * (j - 1)) + sqr((i - 1) * (m - j)) + sqr((n - i) * (j - 1)) + sqr((n - i) * (m - j));
    return a - b;
}

double power(double x, int p) {
    double res = 1;
    while(p--) res *= x;
    return res;
}

double solve() {
    double res = 0, tmp = sqr(n * m);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            res += 1 - power(calc(i, j) / tmp, k);
        }
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &k);
        printf("Case #%d: %.0f\n", t, solve());
    }
}
