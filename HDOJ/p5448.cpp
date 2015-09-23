#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <complex>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MOD = 1e9 + 7;

int inv(int a) {
    if(a == 1) return 1;
    return LL(MOD - MOD / a) * inv(MOD % a) % MOD;
}

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    Point operator + (const Point &rhs) const {
        return Point((x + rhs.x) % MOD, (y + rhs.y) % MOD);
    }
    Point operator * (LL r) {
        return Point(x * r % MOD, y * r % MOD);
    }
    void read() {
        scanf("%d%d", &x, &y);
    }
};
int cross(const Point &a, const Point &b) {
    LL res = (LL)a.x * b.y - (LL)a.y * b.x;
    return (res % MOD + MOD) % MOD;
}

Point p[MAXN];
int pow2[MAXN], powi[MAXN];
int T, n;

void init() {
    LL a = 2, b = inv(2);
    pow2[0] = powi[0] = 1;
    for(int i = 1; i < MAXN; ++i) {
        pow2[i] = pow2[i - 1] * a % MOD;
        powi[i] = powi[i - 1] * b % MOD;
    }
}

int solve() {
    int res = 0;

    Point a(0, 0);
    for(int i = 1; i <= n; ++i) {
        res = (res + cross(p[i] * pow2[i - 1], a)) % MOD;
        a = a + p[i] * powi[i];
    }

    Point b(0, 0);
    for(int i = 1; i <= n; ++i) {
        res = (res + cross(b, p[i] * (i == n ? powi[1] : pow2[n - i - 1]))) % MOD;
        b = b + p[i] * pow2[i];
    }

    return res;
}

int main() {
    init();

    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            p[i].read();
        printf("%d\n", solve());
    }
}
